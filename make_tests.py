#!/bin/env python3
from field import FieldValue
from random import randint, choice
import math

prime = 2**31 -1
n = math.ceil(math.log2(prime) / 8)
F = lambda i: FieldValue(i, prime)
h = lambda i: hex(i)[2:]

def random():
    """ Generates a number with a uniformly random number of digits. """
    length = randint(1, math.ceil(math.log(prime, 16)))
    str = ''.join(choice('0123456789ABCDEF') for i in range(length))
    return F(int(str, 16))

print("""
#include "ecc.c"

int main() {
""")
print('\tNumber p = parse("{}", {});'.format(h(prime), n))
print('\tNumber result = new_number({});'.format(n))
print()

def make_test(a, b, expected, op):
    print('\t{}(parse("{}", {}), parse("{}", {}), p, result);'.format(op, h(a), n, h(b), n))
    print('\tprint(result);')
    print('\tassertEquals(result, parse("{}", {}));'.format(h(expected), n))
    print()

make_test(F(0), F(0), F(0), 'addm')
make_test(F(0), F(1), F(1), 'addm')
make_test(F(1), F(0), F(1), 'addm')
make_test(F(1), F(1), F(2), 'addm')

make_test(F(0), F(0), F(0), 'mulm')
make_test(F(0), F(1), F(0), 'mulm')
make_test(F(1), F(0), F(0), 'mulm')
make_test(F(1), F(1), F(1), 'mulm')

def make_op_test(n, function, name, b_can_be_zero=True):
    for i in range(n):
        a = random()
        while True:
            b = random()
            if b or b_can_be_zero:
                break
        make_test(a, b, function(a, b), name)

make_op_test(1000, lambda a, b: a + b, 'addm')
make_op_test(1000, lambda a, b: a - b, 'subm')
make_op_test(1000, lambda a, b: a * b, 'mulm')
make_op_test(1000, lambda a, b: a / b, 'divm', False)

print('}')
