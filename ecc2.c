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

#define print(n) print_with_label(__func__, #n, __LINE__, n)
void print_with_label(const char* func, const char* label, int line, Number n) {
    printf("%s (%s:%d): ", label, func, line);
    FOR(i, n) {
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

void cp(Number src, Number dst) {
    Number smallest;
    if (src.length < dst.length) {
        smallest = src;
    } else {
        smallest = dst;
    }
    RFOR(i, smallest) {
        dst.v[dst.length - i - 1] = src.v[src.length - i - 1];
    }
}

int cmp(Number a, Number b) {
    if (a.length < b.length) {
        return -cmp(b, a);
    }

    int size_dif = a.length - b.length;
    for (int i = 0; i < size_dif; i++) {
        if (a.v[i] > 0) {
            return 1;
        }
    }

    for (int i = b.length - 1; i >= 0; i--) {
        if (a.v[i + size_dif] > b.v[i]) {
            return 1;
        } else if (a.v[i + size_dif] < b.v[i]) {
            return -1;
        }
    }
    return 0;
}

Number to_number(chunk least, long size) {
    Number n = new_number(size);
    FOR(i, n) {
        n.v[i] = 0x00;
    }
    n.v[size-1] = least;
    return n;
}

Number parse(char* text) {
    int length = strlen(text) / sizeof(chunk);
    Number b = new_number(length);
    FOR(i, b) {
        sscanf(text + i * 2, "%02hhx", &b.v[length-i-1]);
    }
    return b;
}

void add(Number a, Number b, Number result) {
    assert(a.length == b.length);
    assert(result.length >= a.length);

    chunk carry = 0;
    chunk sum;
    RFOR(i, a) {
        sum = a.v[i] + b.v[i] + carry;
        carry = sum < a.v[i] || (sum == a.v[i] && b.v[i] != 0);
        result.v[i] = sum;
    }

    assert(carry == 0);
}

void sub(Number a, Number b, Number result) {
    assert(a.length == b.length);
    assert(result.length >= a.length);

    chunk carry = 0;
    chunk dif;
    RFOR(i, a) {
        dif = a.v[i] - b.v[i] - carry;
        carry = a.v[i] < b.v[i] || dif > a.v[i];
        result.v[i] = dif;
    }
}

void mul(Number a, Number b, Number result) {
    assert(a.v != result.v);
    assert(b.v != result.v);
    assert(a.length == b.length);
    assert(result.length >= 2 * a.length);

    int k = 0;
    chunk carry = 0;
    unsigned long n;

    zero(result);

    FOR(i, a) {
        FOR(j, a) {
            k = i + j + 1;
            n = a.v[i] * b.v[j] + result.v[k] + carry;
            carry = n / 0xFF;
            result.v[k] = n & 0xFF;
        }
        result.v[k] += carry;
        carry = 0;
    }
}

int main() {
    assert(cmp(to_number(1, 4), to_number(1, 5)) == 0);
    assert(cmp(to_number(2, 4), to_number(1, 5)) == 1);
    assert(cmp(to_number(1, 4), to_number(2, 5)) == -1);

    Number _0 = to_number(0, 4);
    Number _1 = to_number(1, 4);
    Number _2 = to_number(2, 4);
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
}
