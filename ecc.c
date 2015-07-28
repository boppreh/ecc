#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

// Chunk of a finite field element.
typedef unsigned char chunk;

// A finite field element.
typedef struct {
    chunk* v;
    long length; 
} Number;

#define FOR(i, n) for (int i = 0; i < n.length; i++)
#define RFOR(i, n) for (int i = n.length - 1; i >= 0; i--)
#define FOR2(i, a, b) for (int i = 0; i < smallest(a, b).length; i++)
#define RFOR2(i, a, b) for (int i = smallest(a, b).length - 1; i >= 0; i--)

#define print(n) print_with_label(__func__, #n, __LINE__, n)
void print_with_label(const char* func, const char* label, int line, Number n) {
    printf("%s (%s:%d): ", label, func, line);
    RFOR(i, n) {
        printf("%02hhx", n.v[i]);
    } 
    printf("\n");
}

void zero(Number dst) {
    FOR(i, dst) {
        dst.v[i] = 0;
    }
}

Number new_number(long size) {
    Number n = {malloc(sizeof(chunk) * size), size};
    zero(n);
    return n;
}

int iszero(Number a) {
    FOR(i, a) {
        if (a.v[i] != 0) {
            return 0;
        }
    }
    return 1;
}

int ismax(Number a) {
    FOR(i, a) {
        if (a.v[i] != 0xFF) {
            return 0;
        }
    }
    return 1;
}

Number smallest(Number a, Number b) {
    if (a.length < b.length) {
        return a;
    } else {
        return b;
    }
}

void cp(Number src, Number dst) {
    zero(dst);
    FOR2(i, src, dst) {
        dst.v[i] = src.v[i];
    }
}

Number clone(Number src) {
    Number c = new_number(src.length);
    cp(src, c);
    return c;
}

int cmp(Number a, Number b) {
    if (a.length < b.length) {
        return -cmp(b, a);
    }

    for (int i = b.length; i < a.length; i++) {
        if (a.v[i] > 0) {
            return 1;
        }
    }

    RFOR(i, b) {
        if (a.v[i] > b.v[i]) {
            return 1;
        } else if (a.v[i] < b.v[i]) {
            return -1;
        }
    }
    return 0;
}

Number to_number(chunk least, long size) {
    Number n = new_number(size);
    RFOR(i, n) {
        n.v[i] = 0x00;
    }
    n.v[0] = least;
    return n;
}

Number parse(const char* text, int length) {
    // Assumes chunk = byte/char.
    int textLength = (strlen(text) + 1) / (2 * sizeof(chunk));

    assert(length >= textLength);

    Number b = new_number(length);

    int i = textLength - 1;

    // If 'text' has an odd number of digits we need special considerations.
    if (strlen(text) % 2 == 1) {
        sscanf(text, "%1hhx", &b.v[i]);
        text++;
        i--;
    }

    for (; i >= 0; i--) {
        sscanf(text, "%02hhx", &b.v[i]);
        text += 2;
    }
    return b;
}

void add(Number a, Number b, Number output) {
    assert(output.length >= a.length && output.length >= b.length);

    Number result = new_number(output.length);

    chunk carry = 0;
    chunk sum;
    FOR2(i, a, b) {
        sum = a.v[i] + b.v[i] + carry;
        carry = sum < a.v[i] || (sum == a.v[i] && b.v[i] != 0);
        result.v[i] = sum;
    }

    // This is necessary if the user does sub(a, b, a) and b << a. In
    // this case the algorithm won't write over every chunk of a,
    // and there will be leftover values.
    cp(result, output);
    free(result.v);
    assert(carry == 0);
}

void sub(Number a, Number b, Number output) {
    Number result = new_number(output.length);

    chunk carry = 0;
    chunk dif;
    FOR2(i, a, b) {
        dif = a.v[i] - b.v[i] - carry;
        carry = a.v[i] < b.v[i] || dif > a.v[i];
        result.v[i] = dif;
    }

    cp(result, output);
    free(result.v);
}

void mul(Number a, Number b, Number result) {
    assert(a.v != result.v);
    assert(b.v != result.v);
    assert(result.length >= 2 * a.length);

    int k = 0;
    chunk carry = 0;
    unsigned long n;

    zero(result);

    RFOR2(i, a, b) {
        RFOR2(j, a, b) {
            k = i + j;
            n = a.v[i] * b.v[j] + result.v[k] + carry;
            carry = n / 0x100;
            result.v[k] = n & 0xFF;
        }
        result.v[k+1] += carry;
        carry = 0;
    }
}

int div2(Number a, Number quotient) {
    int remainder = a.v[0] & 1;
    FOR(i, a) {
        quotient.v[i] = a.v[i] >> 1;
        if (i + 1 < a.length) {
            quotient.v[i] |= (a.v[i+1] & 1) << (8 * sizeof(chunk) - 1);
        }
    } 
    return remainder;
}

void divmod(Number a, Number b, Number quotient, Number remainder) {
    // Shortcut for most finite field operations.
    if (cmp(a, b) == -1) {
        zero(quotient);
        cp(a, remainder);
        return;
    }

    zero(remainder);
    // Assumes a < b^2 (i.e. no more than one multiplication was performed).
    cp(b, quotient);

    Number distance = new_number(a.length);
    div2(quotient, distance);
    Number total = new_number(a.length * 2);
    Number _1 = to_number(1, a.length);

    int count = 0;
    while (!iszero(distance) && count++ < 100) {
        mul(b, quotient, total);
        int comparison = cmp(total, a);
        if (comparison == 0) {
            zero(remainder);
            break;
        } else if (comparison > 0) {
            sub(quotient, distance, quotient);
        } else if (comparison < 0) {
            sub(a, total, remainder);
            if (cmp(b, remainder) > 0) {
                break;
            }
            add(quotient, distance, quotient);
        }

        if (div2(distance, distance)) {
            add(distance, _1, distance);
        }
    }
    free(distance.v);
    free(total.v);
}

void divfloor(Number a, Number b, Number result) {
    Number remainder = new_number(a.length);
    divmod(a, b, result, remainder);
    free(remainder.v);
}

void mod(Number a, Number p, Number result) {
    Number quotient = new_number(a.length);
    // Clone in case of a == result.
    Number temp = clone(a);
    divmod(temp, p, quotient, result);
    free(quotient.v);
    free(temp.v);
}

void addm(Number a, Number b, Number p, Number result) {
    add(a, b, result);
    mod(result, p, result);
}

void subm(Number a, Number b, Number p, Number result) {
    if (cmp(a, b) == -1) {
        cp(a, result);
        add(result, p, result);
        a = result;
    }
    sub(a, b, result);
}

void mulm(Number a, Number b, Number p, Number result) {
    mul(a, b, result);
    mod(result, p, result);
}

void inversem(Number a, Number p, Number result) {
    int l = a.length;

    a = clone(a);
    Number b = clone(p);

    Number x = to_number(0, l);
    Number y = to_number(1, l);
    Number u = to_number(1, l);
    Number v = to_number(0, l);
    Number q = new_number(l);
    Number r = new_number(l);
    Number m = new_number(l * 2);
    Number n = new_number(l * 2);
    while (!iszero(a)) {
        divfloor(b, a, q);
        mod(b, a, r);

        // m = x-u*q
        mul(u, q, m);
        sub(x, m, m);

        // n = y-v*q
        mul(v, q, n);
        sub(y, n, n);
        
        cp(a, b);
        cp(r, a);
        cp(u, x);
        cp(v, y);
        cp(m, u);
        cp(n, v);
    }
    cp(x, result);
    free(a.v);
    free(b.v);
    free(x.v);
    free(y.v);
    free(u.v);
    free(v.v);
    free(q.v);
    free(r.v);
    free(m.v);
    free(n.v);
}

void divm(Number a, Number b, Number p, Number result) {
    Number inverse = new_number(p.length);
    inversem(b, p, inverse);
    mul(a, inverse, result);
    free(inverse.v);
}

typedef struct {
    Number prime;
    Number a;
    Number b;
    Number generator;
    Number generator_order;
} Curve;

typedef struct {
    Number x;
    Number y;
    Curve* c;
} Point;
