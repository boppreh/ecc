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

number new_number() {
    number n = malloc(sizeof(chunk) * N);
    FOR(i) {
        n[i] = 0x00;
    }
    return n;
}

void add(number a, number b, number result) {
    chunk carry = 0;
    chunk sum;
    FOR(i) {
        sum = a[i] + b[i] + carry;
        carry = sum < a[i] || (sum == a[i] && b[i] != 0);
        result[i] = sum;
    }
}

void sub(number a, number b, number result) {
    chunk carry = 0;
    chunk sum;
    FOR(i) {
        sum = a[i] - b[i] - carry;
        carry = a[i] < b[i] || sum > a[i];
        result[i] = sum;
    }
}

int eq(number a, number b) {
    FOR(i) {
        if (a[i] != b[i]) {
            return 0;
        }
    }
    return 1;
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
    if (!eq(a, b)) {
        print("Expected ", b);
        print("got ", a);
    }
}

int main() {
    number a = parse("00000000000000000001");
    assert(eq(a, a));
    assertEquals(a, "00000000000000000001");

    number b = parse("0000000000000000FFFF");
    assertEquals(b, "0000000000000000FFFF");

    number c = new_number();
    add(a, b, c);
    assertEquals(c, "00000000000000010000");
    add(a, c, c);
    assertEquals(c, "00000000000000010001");
    add(b, c, c);
    assertEquals(c, "00000000000000020000");
    sub(c, b, c);
    assertEquals(c, "00000000000000010001");
    sub(c, b, c);
    assertEquals(c, "00000000000000000002");
    sub(c, a, c);
    sub(c, a, c);
    sub(c, a, c);
    assertEquals(c, "FFFFFFFFFFFFFFFFFFFF");
    add(c, a, c);
    assertEquals(c, "00000000000000000000");

    add(b, b, c);
    assertEquals(c, "0000000000000001FFFE");
}
