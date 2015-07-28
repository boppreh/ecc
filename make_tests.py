#!/bin/env python3
from field import FieldValue
from random import randint
import math

prime = 2**31 -1
n_chunks = math.ceil(math.log2(prime) / 2)
F = lambda i: FieldValue(i, prime)
h = lambda i: hex(i)[2:]

print("""
#include "ecc.c"

int main() {
""")
print('\tNumber p = parse("{}");'.format(h(prime)))
print('\tNumber a = new_number({});'.format(n_chunks))
print('\tNumber b = new_number({});'.format(n_chunks))
print('\tNumber result = new_number(2*{});'.format(n_chunks))

def make_test(a, b, expected, op):
    print()
    print('\ta = parse("{}");'.format(h(a)))
    print('\tb = parse("{}");'.format(h(b)))
    print('\t{}(a, b, p, result);'.format(op))
    print('\tassert(cmp(result, parse("{}")) == 0);'.format(h(expected)))

make_test(F(0), F(0), F(0), 'addm')
make_test(F(0), F(1), F(1), 'addm')
make_test(F(1), F(0), F(1), 'addm')
make_test(F(1), F(1), F(2), 'addm')

make_test(F(0), F(0), F(0), 'mulm')
make_test(F(0), F(1), F(0), 'mulm')
make_test(F(1), F(0), F(0), 'mulm')
make_test(F(1), F(1), F(1), 'mulm')

def make_op_test(n, function, name):
    for i in range(n):
        a = F(randint(0, prime))
        b = F(randint(0, prime))
        make_test(a, b, function(a, b), name)

make_op_test(100, lambda a, b: a + b, 'addm')
make_op_test(100, lambda a, b: a + b, 'subm')
make_op_test(100, lambda a, b: a + b, 'mulm')
make_op_test(100, lambda a, b: a + b, 'divm')

print('}')
