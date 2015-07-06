#include "ecc.c"

int main(void) {
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
    mod(p, _128, p);
    add(_1, p, p);
    assert(cmp(p, _128) == 0);

    return 0;
}
