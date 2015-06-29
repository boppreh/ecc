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
    FOR(i, src) {
        dst.v[i] = src.v[i];
    }
}

int cmp(Number a, Number b) {
    RFOR(i, a) {
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

#define print(n) print_with_label(__func__, #n, n)
void print_with_label(const char* func, const char* label, Number n) {
    printf("%s (%s): ", label, func);
    FOR(i, n) {
        printf("%02hhx", n.v[i]);
    } 
    printf("\n");
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
    assert(result.length >= a.length);

    chunk k = 0;
    chunk carry = 0;
    unsigned long n;

    zero(result);

    for (int i = a.length/2 - 1; i >= 0; i--) {
		for (int j = a.length/2 - 1, k = i + j, carry = 0; j >= 0; j--, k--) {
            n = a.v[i] * b.v[j] + result.v[k] + carry;
            carry = n / 0xFF;
            result.v[k] = n & 0xFF;
        }
        result.v[k] += carry;
    }
}

int main() {
    Number _0 = to_number(0, 32);
    Number _1 = to_number(1, 32);
    Number _2 = to_number(2, 32);
    Number _255 = to_number(255, 32);

    Number a = new_number(32);

    add(_1, _0, a);
    assert(cmp(a, _1) == 0);
    add(_1, _1, a);
    assert(cmp(a, _2) == 0);
    add(_1, _255, a);
    sub(a, _255, a);
    assert(cmp(a, _1) == 0);
    sub(_2, _1, a);
    assert(cmp(a, _1) == 0);
}
