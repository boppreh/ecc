from __future__ import division
try:
    from itertools import izip_longest as zip_longest
    base_value = long
except:
    from itertools import zip_longest
    base_value = int

from random import randint


class FieldValue(base_value):
    """
    Class for operating on finite fields with overloaded operators.
    The field modulus is replicated on each field value.

    **MOD MUST BE PRIME FOR CORRECT DIVISION**
    """
    def __new__(cls, value, mod):
        return base_value.__new__(cls, base_value(value % mod))

    def __init__(self, value, mod):
        self.mod = mod
        base_value.__init__(base_value(value))

    def __bool__(self):
        return base_value(self) != 0

    def __add__(self, other):
        return FieldValue(base_value.__add__(self, base_value(other)), self.mod)

    def __radd__(self, other):
        return FieldValue(base_value.__add__(self, base_value(other)), self.mod)

    def __sub__(self, other):
        result = base_value.__sub__(self, base_value(other))
        while result < 0:
            result += self.mod
        return FieldValue(result, self.mod)

    def __rsub__(self, other):
        result = base_value.__sub__(base_value(other), self)
        while result < 0:
            result += self.mod
        return FieldValue(result, self.mod)

    def __mul__(self, other):
        return FieldValue(base_value(self) * base_value(other % self.mod), self.mod)

    def __rmul__(self, other):
        return FieldValue(base_value(other % self.mod) * base_value(self), self.mod)

    def __div__(self, other):
        return self * FieldValue(other, self.mod).inverse()

    def __rdiv__(self, other):
        return other * self.inverse()

    def __truediv__(self, other):
        return self.__div__(other)

    def __rtruediv__(self, other):
        return self.__rdiv__(other)

    def __pow__(self, other):
        return FieldValue(pow(base_value(self), base_value(other), self.mod), self.mod)

    def __eq__(self, other):
        if other is None: return False
        return base_value(self) == base_value(other) % self.mod

    def inverse(self):
        """
        Returns the multiplicative inverse such that `a.inverse() * a == 1`.
        The modulus must be a prime for this to work.
        """
        a, n = base_value(self), self.mod
        t = 0
        newt = 1
        r = n
        newr = a
        while newr != 0:
            quotient = r // newr
            t, newt = newt, t - quotient * newt 
            r, newr = newr, r - quotient * newr
        if r > 1: raise ValueError('Not invertible {}'.format(self))
        if t < 0: t +=n
        return FieldValue(t, self.mod)

    def __repr__(self):
        return '{}(%{})'.format(int(self), self.mod)

    def __str__(self):
        return repr(self)

    def __hash__(self):
        return base_value(self)
