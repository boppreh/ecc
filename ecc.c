#include <stdio.h>
#include <stdlib.h>

// Chunk of a finite field element.
typedef unsigned char chunk;
// Number of chunks per element.
#define N 10
// A finite field element.
typedef struct { chunk v[N]; }* number;
// Helper macro.
#define FOR(i) for (int i = 0; i < N; i++)

number new_number() {
    number n = malloc(sizeof(number));
    FOR(i) {
        n->v[i] = 0x00;
    }
    return n;
}

void print(char* label, number n) {
    printf("%s: ", label);
    for (int i = N - 1; i >= 0; i--) {
        printf("%02x", n->v[i]);
    } 
    printf("\n");
}

void add(number a, number b, number result) {
    chunk carry = 0;
    chunk sum;
    FOR(i) {
        sum = a->v[i] + b->v[i] + carry;
        carry = sum < a->v[i] || (sum == a->v[i] && b->v[i] != 0);
        result->v[i] = sum;
    }
}

void sub(number a, number b, number result) {
    chunk carry = 0;
    chunk sum;
    FOR(i) {
        sum = a->v[i] - b->v[i] - carry;
        carry = a->v[i] < b->v[i] || sum > a->v[i];
        result->v[i] = sum;
    }
}

int main() {
    number a = new_number();
    a->v[0] = 0x01;
    number b = new_number();
    b->v[0] = 0xFF;
    b->v[1] = 0xFF;
    number c = new_number();
    print("a", a);
    print("b", b);
    add(a, b, c);
    print("a+b", c);
    sub(c, b, c);
    print("a+b-b", c);
    c->v[0] = 0x00;
    print("c", c);
    sub(c, a, c);
    print("-a", c);
}
