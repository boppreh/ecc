#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <fcntl.h>
#include <unistd.h>

// Chunk of a finite field element.
typedef unsigned char chunk;

// A finite field element.
typedef struct {
    int length; 
    chunk v[];
} Number;

#define FOR(i, n) for (int i = 0; i < n; i++)
#define RFOR(i, n) for (int i = n - 1; i >= 0; i--)
#define MIN(x, y) (x < y ? x : y)
#define FOR2(i, a, b) for (int i = 0; i < MIN(a, b); i++)

#define assertEquals(A, B) if (cmp(A, B) != 0) { printf("---\nASSERTION ERROR at %s:%d\n%s (%s)\n!=\n%s (%s)\n---\n", __func__, __LINE__, to_string(A), #A, to_string(B), #B); assert(cmp(A, B) == 0); }

const char * to_string(Number* n) {
    int chunk_length = 2 * sizeof(chunk);
    int length = chunk_length * n->length + 1;
    char* str = malloc(length);
    char* result = str;
    RFOR(i, n->length) {
        sprintf(str, "%02hhx", n->v[i]);
        str += chunk_length;
    } 
    return result;
}

#define print(n) printf("%s (%s:%d):\t%s\n", #n, __func__, __LINE__, to_string(n));

void zero(Number* dst) {
    memset(dst->v, 0x00, sizeof(chunk) * dst->length);
}

int effective_length(Number* a) {
    RFOR(i, a->length) {
        if (a->v[i] != 0) {
            return i + 1;
        }
    }
    return 0;
}

int iszero(Number* a) {
    return effective_length(a) == 0;
}

int cmp(Number* a, Number* b) {
    if (a->length < b->length) {
        return -cmp(b, a);
    }

    for (int i = b->length; i < a->length; i++) {
        if (a->v[i] > 0) {
            return 1;
        }
    }

    RFOR(i, b->length) {
        if (a->v[i] > b->v[i]) {
            return 1;
        } else if (a->v[i] < b->v[i]) {
            return -1;
        }
    }
    return 0;
}

void rand_number(Number* dst, Number* max) {
    int urandom = open("/dev/urandom", O_RDONLY);
    assert(urandom != -1);
    int target_nbytes = sizeof(chunk) * effective_length(max);
    while (1) {
        ssize_t nbytes = read(urandom, dst->v, target_nbytes);
        if (nbytes != target_nbytes || cmp(dst, max) >= 1 || iszero(dst)) {
            printf("Random number generation failed. Trying again...\n");
            print(dst);
            continue;
        } else {
            break;
        }
    }
    close(urandom);
}

Number* new_number(long length) {
    Number* n = malloc(sizeof(chunk) * length + sizeof(long));
    n->length = length;
    zero(n);
    return n;
}

int ismax(Number* a) {
    FOR(i, a->length) {
        if (a->v[i] != 0xFF) {
            return 0;
        }
    }
    return 1;
}

void cp(Number* src, Number* dst) {
    if (src == dst) {
        return;
    } else {
        // In case dst is bigger than src.
        zero(dst);
        memcpy(dst->v, src->v, sizeof(chunk) * MIN(src->length, dst->length));
    }
}

Number* clone(Number* src) {
    Number* c = new_number(src->length);
    cp(src, c);
    return c;
}

Number* to_number(chunk least, long size) {
    Number* n = new_number(size);
    RFOR(i, n->length) {
        n->v[i] = 0x00;
    }
    n->v[0] = least;
    return n;
}

Number* parse(const char* text, int length) {
    // Assumes chunk = byte/char.
    int textLength = (strlen(text) + 1) / (2 * sizeof(chunk));

    assert(length >= textLength);

    Number* b = new_number(length);

    int i = textLength - 1;

    // If 'text' has an odd number of digits we need special considerations.
    if (strlen(text) % 2 == 1) {
        sscanf(text, "%1hhx", &b->v[i]);
        text++;
        i--;
    }

    for (; i >= 0; i--) {
        sscanf(text, "%02hhx", &b->v[i]);
        text += 2;
    }
    return b;
}

void add(Number* a, Number* b, Number* output) {
    assert(output->length >= a->length && output->length >= b->length);

    Number* result = new_number(output->length);

    chunk carry = 0;
    chunk sum;
    FOR2(i, a->length, b->length) {
        sum = a->v[i] + b->v[i] + carry;
        carry = sum < a->v[i] || (sum == a->v[i] && b->v[i] != 0);
        result->v[i] = sum;
    }

    // This is necessary if the user does sub(a, b, a) and b << a. In
    // this case the algorithm won't write over every chunk of a,
    // and there will be leftover values.
    cp(result, output);
    free(result);
    output->v[MIN(a->length, b->length)] = carry;
}

void sub(Number* a, Number* b, Number* output) {
    Number* result = new_number(output->length);

    unsigned long carry = 0;
    unsigned long dif;
    FOR2(i, a->length, b->length) {
        dif = a->v[i] - b->v[i] - carry;
        carry = a->v[i] < b->v[i] || dif > a->v[i];
        result->v[i] = dif;
    }

    cp(result, output);
    free(result);
}

void mul(Number* a, Number* b, Number* result) {
    assert(a->v != result->v);
    assert(b->v != result->v);
    assert(result->length >= 2 * a->length);

    int k = 0;
    chunk carry = 0;
    unsigned long n;

    zero(result);

    FOR2(i, a->length, b->length) {
        FOR2(j, a->length, b->length) {
            k = i + j;
            n = a->v[i] * b->v[j] + result->v[k] + carry;
            carry = n / 0x100;
            result->v[k] = n & 0xFF;
        }
        result->v[k+1] += carry;
        carry = 0;
    }
}

int div2(Number* a, Number* quotient) {
    int remainder = a->v[0] & 1;
    FOR(i, a->length) {
        quotient->v[i] = a->v[i] >> 1;
        if (i + 1 < a->length) {
            quotient->v[i] |= (a->v[i+1] & 1) << (8 * sizeof(chunk) - 1);
        }
    } 
    return remainder;
}

void divmod_binarysearch(Number* a, Number* b, Number* quotient, Number* out_remainder) {
    Number* remainder = new_number(b->length * 2);

    Number* distance = new_number(b->length);
    distance->v[b->length-1] = 0x40;
    zero(quotient);
    quotient->v[b->length-1] = 0x80;
    zero(remainder);

    Number* total = new_number(a->length * 2);
    Number* _1 = to_number(1, b->length);

    while (!iszero(distance)) {
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
    cp(remainder, out_remainder);
    free(distance);
    free(total);
    free(remainder);
    free(_1);
}

void divmod(Number* a, Number* b, Number* quotient, Number* out_remainder) {
    // Shortcut for most finite field operations.
    if (cmp(a, b) == -1) {
        zero(quotient);
        cp(a, out_remainder);
        return;
    }

    divmod_binarysearch(a, b, quotient, out_remainder);
}

void divfloor(Number* a, Number* b, Number* result) {
    Number* remainder = new_number(a->length);
    divmod(a, b, result, remainder);
    free(remainder);
}

void mod_divmod(Number* a, Number* p, Number* result) {
    Number* quotient = new_number(a->length);
    // Clone in case of a == result.
    Number* temp = clone(a);
    divmod(temp, p, quotient, result);
    free(quotient);
    free(temp);
}

static Number* specialP;

void mod(Number* a, Number* p, Number* output) {
    if (cmp(p, parse("fffffffffffffffffffffffffffffffeffffffffffffffff", 24)) == 0) {
        Number* c5 = new_number(6);
        memcpy(c5->v, a->v + 6 * 5, 6);

        Number* c4 = new_number(6);
        memcpy(c4->v, a->v + 6 * 4, 6);

        Number* c3 = new_number(6);
        memcpy(c3->v, a->v + 6 * 3, 6);

        Number* c2 = new_number(6);
        memcpy(c2->v, a->v + 6 * 2, 6);

        Number* c1 = new_number(6);
        memcpy(c1->v, a->v + 6 * 1, 6);

        Number* c0 = new_number(6);
        memcpy(c0->v, a->v + 6 * 0, 6);

        Number* s1 = new_number(24);
        memcpy(s1->v + 6 * 0, c0->v, 6);
        memcpy(s1->v + 6 * 1, c1->v, 6);
        memcpy(s1->v + 6 * 2, c2->v, 6);

        Number* s2 = new_number(24);
        memcpy(s2->v + 6 * 0, c3->v, 6);
        memcpy(s2->v + 6 * 1, c3->v, 6);
        //memcpy(s2->v + 6 * 2, _0->v, 6);

        Number* s3 = new_number(24);
        //memcpy(s3->v + 6 * 0, _0->v, 6);
        memcpy(s3->v + 6 * 1, c4->v, 6);
        memcpy(s3->v + 6 * 2, c4->v, 6);

        Number* s4 = new_number(24);
        memcpy(s4->v + 6 * 0, c5->v, 6);
        memcpy(s4->v + 6 * 1, c5->v, 6);
        memcpy(s4->v + 6 * 2, c5->v, 6);

        Number* result = new_number(24);
        add(s1, s2, result);
        add(result, s3, result);
        add(result, s4, result);

        //print(result);
        //print(p);
        assert(cmp(result, p) == -1);

        cp(result, output);

        free(c5);
        free(c4);
        free(c3);
        free(c2);
        free(c0);
        free(s1);
        free(s2);
        free(s3);
        free(s4);
        free(result);
        return;
    }

    mod_divmod(a, p, output);
}

void addm(Number* a, Number* b, Number* p, Number* result) {
    Number* tempResult = new_number(2 * p->length);
    add(a, b, tempResult);
    if (cmp(tempResult, p) >= 0) {
        sub(result, result, result);
    }
    free(tempResult);
}

void subm(Number* a, Number* b, Number* p, Number* result) {
    if (cmp(a, b) == -1) {
        Number* tempA = new_number(p->length + 1);
        add(a, p, tempA);
        sub(tempA, b, result);
        free(tempA);
    } else {
        sub(a, b, result);
    }
}

void mulm(Number* a, Number* b, Number* p, Number* result) {
    Number* tempResult = new_number(2 * p->length);
    mul(a, b, tempResult);
    mod(tempResult, p, result);
    free(tempResult);
}

void inversem(Number* a, Number* p, Number* result) {
    int l = a->length;

    a = clone(a);
    Number* b = clone(p);

    Number* x = to_number(0, l);
    Number* y = to_number(1, l);
    Number* u = to_number(1, l);
    Number* v = to_number(0, l);
    Number* q = new_number(l);
    Number* r = new_number(l);
    Number* m = new_number(l * 2);
    Number* n = new_number(l * 2);
    while (!iszero(a)) {
        divfloor(b, a, q);
        mod(b, a, r);

        // m = x-u*q
        mulm(u, q, p, m);
        subm(x, m, p, m);

        // n = y-v*q
        mulm(v, q, p, n);
        subm(y, n, p, n);
        
        cp(a, b);
        cp(r, a);
        cp(u, x);
        cp(v, y);
        cp(m, u);
        cp(n, v);
    }
    cp(x, result);

    free(a);
    free(b);
    free(x);
    free(y);
    free(u);
    free(v);
    free(q);
    free(r);
    free(m);
    free(n);
}

void divm(Number* a, Number* b, Number* p, Number* result) {
    Number* inverse = new_number(p->length);
    inversem(b, p, inverse);
    mulm(a, inverse, p, result);
    free(inverse);
}

typedef struct {
    Number* x;
    Number* y;
    int isinf;
} Point;

typedef struct {
    Number* p;
    Number* a;
    Number* b;
    Point* generator;
    Number* generator_order;
} Curve;

Point* new_point(int length) {
    Point* p = malloc(sizeof(Point));
    p->x = new_number(length);
    p->y = new_number(length);
    p->isinf = 1;
    return p;
}

Point* parse_point(const char* x, const char* y, int length) {
    Point* p = malloc(sizeof(Point));
    p->x = parse(x, length);
    p->y = parse(y, length);
    return p;
}

#define printp(p) if (p->isinf == 0) { printf("%s (%s:%d):\t(%s, %s)\n", #p, __func__, __LINE__, to_string(p->x), to_string(p->y)); } else { printf("%s (%s:%d):\tINF\n", #p, __func__, __LINE__); }

void cpp(Point* src, Point* dst) {
    dst->isinf = 0;
    cp(src->x, dst->x);
    cp(src->y, dst->y);
}

void doublep(Point* p, Curve c, Point* output) {
    if (p->isinf) {
        output->isinf = 1;
        return;
    }

    Number* s = new_number(c.p->length);
    Number* temp = new_number(c.p->length);
    Number* _2 = to_number(2, c.p->length);
    Number* _3 = to_number(3, c.p->length);

    Point* result = new_point(c.p->length);

    // s = (3 * p->x**2 + curve.a) / (2 * p->y)
    mulm(p->x, p->x, c.p, s);
    mulm(s, _3, c.p, s);
    addm(s, c.a, c.p, s);
    mulm(p->y, _2, c.p, temp);
    divm(s, temp, c.p, s);

    // s**2 - 2 * p->x
    mulm(s, s, c.p, result->x);
    mulm(p->x, _2, c.p, temp);
    subm(result->x, temp, c.p, result->x);

    // s * (p->x - r->x) - p->y
    subm(p->x, result->x, c.p, temp);
    mulm(s, temp, c.p, result->y);
    subm(result->y, p->y, c.p, result->y);

    free(s);
    free(temp);
    free(_2);
    free(_3);

    cpp(result, output);
    output->isinf = 0;
    free(result->x);
    free(result->y);
}

void addp(Point* p, Point* q, Curve c, Point* output) {
    if (p->isinf) {
        cpp(q, output);
        return;
    }
    if (q->isinf) {
        cpp(p, output);
        return;
    }

    Number* temp = new_number(c.p->length);
    sub(c.p, q->y, temp);
    if (cmp(p->x, q->x) == 0) {
        if (cmp(p->y, temp) == 0) {
            output->isinf = 1;
            free(temp);
            return;
        } else if (cmp(p->y, q->y) == 0) {
            doublep(p, c, output);
            free(temp);
            return;
        }
    }

    Number* s = new_number(c.p->length);
    Number* dx = new_number(c.p->length);
    Number* dy = new_number(c.p->length);
    Point* result = new_point(c.p->length);

    // s = (py - qy) / (px - qx)
    subm(p->x, q->x, c.p, dx);
    subm(p->y, q->y, c.p, dy);
    divm(dy, dx, c.p, s);

    // rx = s**2 - px - qx
    mulm(s, s, c.p, result->x);
    subm(result->x, p->x, c.p, result->x);
    subm(result->x, q->x, c.p, result->x);

    // ry = s * (px - rx) - py
    subm(p->x, result->x, c.p, result->y);
    mulm(s, result->y, c.p, result->y);
    subm(result->y, p->y, c.p, result->y);

    cpp(result, output);

    free(s);
    free(dx);
    free(dy);
    free(temp);
}

void mulp(Point* p, Number* a, Curve c, Point* result) {
    //printp(p);
    //print(a);

    Point* n = new_point(c.p->length);
    cpp(p, n);
    Number* k = new_number(c.p->length);
    cp(a, k);
    result->isinf = 1;
    while (!iszero(k)) {
        if (div2(k, k) == 1) {
            addp(result, n, c, result);
            //print(k);
            //printp(result);
            //printp(n);
        }
        doublep(n, c, n);
    }

    free(n->x);
    free(n->y);
}

typedef struct {
    Point* p;
    Curve c;
} PublicKey;

typedef struct {
    Number* k;
    Curve c;
} PrivateKey;

typedef struct {
    PublicKey public;
    PrivateKey private;
} Keypair;

Keypair generate_keypair(Curve c) {
    PublicKey public = {new_point(c.p->length), c};
    PrivateKey private = {new_number(c.p->length), c};
    rand_number(private.k, c.generator_order);
    mulp(c.generator, private.k, c, public.p);

    Keypair kp = {public, private};
    return kp;
}

typedef struct {
    Point* secret;
    Point* hint;
} EncryptionData;

EncryptionData generate_encryption(PublicKey public) {
    EncryptionData data = {new_point(public.c.p->length), new_point(public.c.p->length)};
    Number* secret = new_number(public.c.p->length);
    rand_number(secret, public.c.generator_order);
    mulp(public.p, secret, public.c, data.secret);
    mulp(public.c.generator, secret, public.c, data.hint);
    return data;
}

Point* generate_decryption(PrivateKey private, Point* hint) {
    Point* secret = new_point(private.c.p->length);
    mulp(hint, private.k, private.c, secret);
    return secret;
}

typedef struct {
    Number* r;
    Number* s; 
} Signature;

Signature sign(PrivateKey private, Number* hash) {
    Curve c = private.c;
    Number* nonce = new_number(c.p->length);
    Point* r = new_point(c.p->length);
    Number* s = new_number(c.p->length);
    while (1) {
        rand_number(nonce, c.generator_order);
        mulp(c.generator, nonce, c, r);
        if (iszero(r->x)) {
            // Unlucky r.
            continue;
        }
        mulm(private.k, r->x, c.generator_order, s);
        addm(s, hash, c.generator_order, s);
        divm(s, nonce, c.generator_order, s);
        if (iszero(s)) {
            // Unlucky s.
            continue;
        }

        break;
    }

    Signature signature = {new_number(c.p->length), s};
    cp(r->x, signature.r);

    free(r);
    free(nonce);

    return signature;
}

int verify(PublicKey public, Number* hash, Signature signature) {
    Curve c = public.c;
    Number* w = new_number(c.p->length);
    inversem(signature.s, c.generator_order, w);

    Number* u1 = new_number(c.p->length);
    mulm(hash, w, c.generator_order, u1);
    Number* u2 = new_number(c.p->length);
    mulm(signature.r, w, c.generator_order, u2);

    Point* p = new_point(c.p->length);
    Point* q = new_point(c.p->length);
    mulp(c.generator, u1, c, p);
    mulp(public.p, u2, c, q);
    addp(p, q, c, p);

    mod(p->x, c.generator_order, w);
    return cmp(w, signature.r) == 0;
}
