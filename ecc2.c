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

Number new_number(long size) {
    Number n = {malloc(sizeof(chunk) * size), size};
    return n;
}

void zero(Number dst) {
    FOR(i, dst) {
        dst.v[i] = 0;
    }
}

Number smallest(Number a, Number b) {
    if (a.length < b.length) {
        return a;
    } else {
        return b;
    }
}

void cp(Number src, Number dst) {
    FOR2(i, src, dst) {
        dst.v[i] = src.v[i];
    }
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

Number parse(const char* text) {
    assert(strlen(text) % 2 == 0);
    // Ceiling division.
    int length = strlen(text) / (2 * sizeof(chunk));
    Number b = new_number(length);
    RFOR(i, b) {
        sscanf(text, "%02hhx", &b.v[i]);
        text += 2;
    }
    return b;
}

void add(Number a, Number b, Number result) {
    assert(result.length >= a.length && result.length >= b.length);

    chunk carry = 0;
    chunk sum;
    FOR2(i, a, b) {
        sum = a.v[i] + b.v[i] + carry;
        carry = sum < a.v[i] || (sum == a.v[i] && b.v[i] != 0);
        result.v[i] = sum;
    }

    assert(carry == 0);
}

void sub(Number a, Number b, Number result) {
    assert(result.length >= a.length && result.length >= b.length);

    chunk carry = 0;
    chunk dif;
    FOR2(i, a, b) {
        dif = a.v[i] - b.v[i] - carry;
        carry = a.v[i] < b.v[i] || dif > a.v[i];
        result.v[i] = dif;
    }
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
            carry = n / 0xFF;
            result.v[k] = n & 0xFF;
        }
        result.v[k+1] += carry;
        carry = 0;
    }
}

void mod(Number a, Number p) {
    if (cmp(a, p) == -1) {
        return;
    }
    while (cmp(a, p) != -1) {
        sub(a, p, a);
    }
}

void addm(Number a, Number b, Number p, Number result) {
    add(a, b, result);
    mod(result, p);
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
    mod(result, p);
}

int main() {
    assert(cmp(to_number(1, 4), to_number(1, 5)) == 0);
    assert(cmp(to_number(2, 4), to_number(1, 5)) == 1);
    assert(cmp(to_number(2, 4), to_number(1, 5)) == 1);

    assert(cmp(parse("0002"), to_number(2, 2)) == 0);
    assert(cmp(parse("00FF"), to_number(255, 2)) == 0);

    Number _0 = to_number(0, 4);
    Number _1 = to_number(1, 4);
    Number _2 = to_number(2, 4);
    Number _3 = to_number(3, 4);
    Number _128 = to_number(128, 4);
    Number _255 = to_number(255, 4);

    Number a = new_number(4);

    add(_1, _0, a);
    assert(cmp(a, _1) == 0);
    add(_1, _1, a);
    assert(cmp(a, _2) == 0);
    add(_1, _255, a);
    sub(a, _255, a);
    assert(cmp(a, _1) == 0);
    sub(_2, _1, a);
    assert(cmp(a, _1) == 0);

    Number p = new_number(8);
    Number q = new_number(16);
    mul(_0, _0, p);
    assert(cmp(p, _0) == 0);
    mul(_0, _1, p);
    assert(cmp(p, _0) == 0);
    mul(_1, _1, p);
    assert(cmp(p, _1) == 0);
    mul(_2, _2, p);
    mul(p, p, q);
    assert(cmp(q, to_number(16, 4)) == 0);

    mul(_128, _3, p);
    assert(cmp(p, parse("0180")) == 0);

    cp(_255, p);
    mod(p, _128);
    add(_1, p, p);
    assert(cmp(p, _128) == 0);
}
