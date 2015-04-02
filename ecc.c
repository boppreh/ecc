#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

// Chunk of a finite field element.
typedef unsigned char chunk;
// Number of chunks per element.
#define N 10
// A finite field element.
typedef chunk* number;
// Helper macro.
#define FOR(i) for (int i = 0; i < N; i++)
#define RFOR(i) for (int i = N - 1; i >= 0; i--)
#define ZERO new_number()
#define MAX make_max()

number new_number();
int cmp(number a, number b);
void add(number a, number b, number p, number result);
void sub(number a, number b, number p, number result);

number new_number() {
    number n = malloc(sizeof(chunk) * N);
    FOR(i) {
        n[i] = 0x00;
    }
    return n;
}

void cp(number src, number dst) {
    FOR(i) {
        dst[i] = src[i];
    }
}

number make_max() {
    number n = malloc(sizeof(chunk) * N);
    FOR(i) {
        n[i] = 0xFF;
    }
    return n;
}

void add(number a, number b, number p, number result) {
    chunk carry = 0;
    chunk sum;
    FOR(i) {
        sum = a[i] + b[i] + carry;
        carry = sum < a[i] || (sum == a[i] && b[i] != 0);
        result[i] = sum;
    }
    
    if (cmp(result, p) == 1) {
        sub(result, p, MAX, result);
    }
}

void sub(number a, number b, number p, number result) {
    if (cmp(a, b) == -1) {
        cp(a, result);   
        a = result;
        add(a, p, MAX, a);
    }

    chunk carry = 0;
    chunk sum;
    FOR(i) {
        sum = a[i] - b[i] - carry;
        carry = a[i] < b[i] || sum > a[i];
        result[i] = sum;
    }
}

void mul(number a, number b, number p, number result) {
    chunk k = 0;
    chunk carry = 0;
    unsigned long n;

    cp(ZERO, result);

    for (int i = N/2 - 1; i >= 0; i--) {
		for (int j = N/2 - 1, k = i + j, carry = 0; j >= 0; j--, k--) {
            n = a[i] * b[j] + result[k] + carry;
            carry = n / 0xFF;
            result[k] = n & 0xFF;
        }
        result[k] += carry;
    }
}

void karatsuba(number a, number b, number p, number result) {

}

int cmp(number a, number b) {
    RFOR(i) {
        if (a[i] > b[i]) {
            return 1;
        } else if (a[i] < b[i]) {
            return -1;
        }
    }
    return 0;
}


//////////////////////
// Testing function //
//////////////////////

number parse(char* text) {
    number b = new_number();
    FOR(i) {
        sscanf(text + i * 2, "%02hhx", &b[N-i-1]);
    }
    return b;
}

void print(char* label, number n) {
    printf("%s: ", label);
    for (int i = N - 1; i >= 0; i--) {
        printf("%02hhx", n[i]);
    } 
    printf("\n");
}

void assertEquals(number a, char* text) {
    number b = parse(text);
    if (cmp(a, b) != 0) {
        print("Expected ", b);
        print("got ", a);
    }
}

int main() {
    number ONE = parse("00000000000000000001");
    number TWO = parse("00000000000000000002");

    number a = ONE;
    assert(cmp(a, a) == 0);
    assertEquals(a, "00000000000000000001");

    number b = parse("0000000000000000FFFF");
    assertEquals(b, "0000000000000000FFFF");
    assert(cmp(a, b) == -1);

    number c = new_number();
    add(a, b, MAX, c);
    assertEquals(c, "00000000000000010000");
    add(a, c, MAX, c);
    assertEquals(c, "00000000000000010001");
    add(b, c, MAX, c);
    assertEquals(c, "00000000000000020000");
    sub(c, b, MAX, c);
    assertEquals(c, "00000000000000010001");
    sub(c, b, MAX, c);
    assertEquals(c, "00000000000000000002");
    sub(c, a, MAX, c);
    sub(c, a, MAX, c);
    sub(c, a, MAX, c);

    add(b, b, MAX, c);
    assertEquals(c, "0000000000000001FFFE");

    mul(ONE, ZERO, MAX, c);
    assertEquals(c, "00000000000000000000");
    mul(ZERO, ONE, MAX, c);
    assertEquals(c, "00000000000000000000");
    mul(ZERO, ZERO, MAX, c);
    assertEquals(c, "00000000000000000000");
    mul(ONE, ONE, MAX, c);
    assertEquals(c, "00000000000000000001");
    mul(TWO, TWO, MAX, c);
    assertEquals(c, "00000000000000000004");

    // TODO: fix multiplication when result is one of the operands.
    // mul(c, c, MAX, c);
    //assertEquals(c, "00000000000000000010");
}
