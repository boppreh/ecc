#!/bin/env python3
from field import FieldValue
from random import randint, choice
import math

def make_c_source(prime=2**31-1):
    n = math.ceil(math.log2(prime) / 8) + 1
    F = lambda i: FieldValue(i, prime)
    h = lambda i: hex(i)[2:]

    def random():
        """ Generates a number with a uniformly random number of digits. """
        length = randint(1, math.ceil(math.log(prime, 16)))
        str = ''.join(choice('0123456789ABCDEF') for i in range(length))
        return F(int(str, 16))

    yield """
    #include "ecc.c"

    int main() {
    """
    yield '\tNumber* p = parse("{}", {});'.format(h(prime), n)
    yield '\tNumber* result = new_number({});'.format(n)
    yield ''

    def make_test(a, b, expected, op):
        yield '\t{}(parse("{}", {}), parse("{}", {}), p, result);'.format(op, h(a), n, h(b), n)
        yield '\tassertEquals(result, parse("{}", {}));'.format(h(expected), n)
        yield ''

    yield from make_test(F(0), F(0), F(0), 'addm')
    yield from make_test(F(0), F(1), F(1), 'addm')
    yield from make_test(F(1), F(0), F(1), 'addm')
    yield from make_test(F(1), F(1), F(2), 'addm')

    yield from make_test(F(0), F(0), F(0), 'mulm')
    yield from make_test(F(0), F(1), F(0), 'mulm')
    yield from make_test(F(1), F(0), F(0), 'mulm')
    yield from make_test(F(1), F(1), F(1), 'mulm')

    def make_op_test(n, function, name, b_can_be_zero=True):
        yield 'printf("Starting {} tests.\\n");'.format(name)
        for i in range(n):
            a = random()
            while True:
                b = random()
                if b or b_can_be_zero:
                    break
            yield from make_test(a, b, function(a, b), name)
        yield 'printf("Finished {} tests.\\n");'.format(name)

    yield from make_op_test(200, lambda a, b: a + b, 'addm')
    yield from make_op_test(200, lambda a, b: a - b, 'subm')
    yield from make_op_test(200, lambda a, b: a * b, 'mulm')
    yield from make_op_test(200, lambda a, b: a / b, 'divm', False)

    yield '}'

import os

for prime in [2**31-1, 2147483659, 4294967311, 4294967357, 3221225473]:
    with open('automated_tests.c', 'w') as f:
        for line in make_c_source(prime):
            f.write(line + '\n')

    print('Testing prime {}...'.format(prime))

    os.system('clang -pg -O3 -Wall automated_tests.c -o automated_tests && ./automated_tests && rm automated_tests automated_tests.c')
    input('Finished test. Press enter to run next.')
