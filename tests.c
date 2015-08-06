#include "ecc.c"

static Number* _0;
static Number* _1;
static Number* _2;
static Number* _3;
static Number* _128;
static Number* _255;

void setup() {
    _0 = to_number(0, 4);
    _1 = to_number(1, 4);
    _2 = to_number(2, 4);
    _3 = to_number(3, 4);
    _128 = to_number(128, 4);
    _255 = to_number(255, 4);
}

void testSanity() {
    assert(cmp(to_number(1, 4), to_number(1, 5)) == 0);
    assert(cmp(to_number(2, 4), to_number(1, 5)) == 1);
    assert(cmp(to_number(2, 4), to_number(1, 5)) == 1);

    assert(cmp(parse("0002", 2), to_number(2, 2)) == 0);
    assert(cmp(parse("00FF", 2), to_number(255, 2)) == 0);

    assert(cmp(parse("0002", 4), to_number(2, 2)) == 0);
    assert(cmp(parse("00FF", 4), to_number(255, 2)) == 0);
}

void testAddSub() {
    Number* a = new_number(4);
    add(_1, _0, a);
    assert(cmp(a, _1) == 0);
    add(_1, _1, a);
    assert(cmp(a, _2) == 0);
    add(_1, _255, a);
    sub(a, _255, a);
    assert(cmp(a, _1) == 0);
    sub(_2, _1, a);
    assert(cmp(a, _1) == 0);

    // Test with borrows that overflow.
    Number* result = new_number(4);
    sub(parse("7f310ffeac6", 8), parse("7f2fffff01a", 8), result);
	assertEquals(result, parse("10fffaac", 4));
}

void testMul() {
    Number* p = new_number(8);
    Number* q = new_number(16);
    mul(_0, _0, p);
    assert(cmp(p, _0) == 0);
    mul(_0, _1, p);
    assert(cmp(p, _0) == 0);
    mul(_1, _1, p);
    assert(cmp(p, _1) == 0);
    mul(_2, _2, p);
    mul(p, p, q);
    assert(cmp(q, to_number(16, 4)) == 0);

    mul(_255, _3, p);
    assert(cmp(p, parse("02FD", 4)) == 0);

    mul(parse("55", 4), _3, p);
    assert(cmp(p, _255) == 0);

    mul(_128, _3, p);
    assert(cmp(p, parse("0180", 8)) == 0);
}

void testDiv2() {
    Number* quotient = new_number(4);
    int remainder2;

    remainder2 = div2(_128, quotient);
    assert(cmp(quotient, parse("40", 4)) == 0);
    assert(remainder2 == 0);

    remainder2 = div2(parse("0FFF", 4), quotient);
    assert(cmp(quotient, parse("07FF", 4)) == 0);
    assert(remainder2 == 1);
}

void testDiv() {
    Number* quotient = new_number(4);
    Number* remainder = new_number(4);

    divmod(_1, _128, quotient, remainder);
    assert(cmp(quotient, _0) == 0);
    assert(cmp(remainder, _1) == 0);

    divmod(_255, _128, quotient, remainder);
    assert(cmp(quotient, _1) == 0);
    assert(cmp(remainder, parse("7F", 4)) == 0);

    divmod(_255, _3, quotient, remainder);
    assert(cmp(quotient, parse("55", 4)) == 0);
    assert(cmp(remainder, _0) == 0);

    divmod(_128, _2, quotient, remainder);
    assert(cmp(quotient, parse("40", 4)) == 0);
    assert(cmp(remainder, _0) == 0);

	Number* result = new_number(4);
    mod(parse("000002dc52211d19", 8), parse("7fffffff", 4), result);
	assert(cmp(result, parse("522122d1", 4)) == 0);
}

void testInverse() {
	Number* p = parse("7fffffff", 4);
	Number* result = new_number(4);
    inversem(parse("FF", 4), p, result);
	assertEquals(result, parse("1010101", 4));

    inversem(parse("ea0d", 4), p, result);
	assertEquals(result, parse("6b1b6ac8", 4));
}

int main(void) {
    //chunk arr[10];
    //Number n = {10, arr};
    //print(&n);
    //return 0;
    setup();
    testSanity();
    testAddSub();
    testMul();
    testDiv2();
    testDiv();
    testInverse();

    // Curve brainpoolP160r1 from https://tools.ietf.org/html/rfc5639#section-3.1
    Curve c  = {
        parse("E95E4A5F737059DC60DFC7AD95B3D8139515620F", 20),
        parse("340E7BE2A280EB74E2BE61BADA745D97E8F7C300", 20),
        parse("1E589A8595423412134FAA2DBDEC95C8D8675E58", 20),
        {
            parse("BED5AF16EA3F6A4F62938C4631EB5AF7BDBCDBC3", 20),
            parse("1667CB477A1A8EC338F94741669C976316DA6321", 20)
        },
        parse("E95E4A5F737059DC60DF5991D45029409E60FC09", 20),
    };
    Keypair kp = generate_keypair(c);
    print(kp.private.k);
    printp(kp.public.p);

    EncryptionData data = generate_encryption(kp.public);
    printp(data.secret);
    printp(data.hint);
    printp(generate_decryption(kp.private, data.hint));

    Number* hash = parse("1E589A8595423412134FAA2DBDEC95C8D8675E58", 20);
    Signature signature = sign(kp.private, hash);
    assert(verify(kp.public, hash, signature));

    return 0;
}
