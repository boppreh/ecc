"""
Based on http://www.johannes-bauer.com/compsci/ecc/
"""

from field import FieldValue
from random import randrange

# Curve parameters.

#prime = 263
#curve_a = 2
#curve_b = 3
#generator = (FieldValue(200, prime), FieldValue(39, prime))
#generator_order = 269 # + 1 at infinity

# Curve brainpoolP160r1 from https://tools.ietf.org/html/rfc5639#section-3.1
prime = 0xE95E4A5F737059DC60DFC7AD95B3D8139515620F
curve_a = 0x340E7BE2A280EB74E2BE61BADA745D97E8F7C300
curve_b = 0x1E589A8595423412134FAA2DBDEC95C8D8675E58
generator = (FieldValue(0xBED5AF16EA3F6A4F62938C4631EB5AF7BDBCDBC3, prime),
             FieldValue(0x1667CB477A1A8EC338F94741669C976316DA6321, prime))
generator_order = 0xE95E4A5F737059DC60DF5991D45029409E60FC09

F = lambda n: FieldValue(n, generator_order)
rand = lambda: F(randrange(1, generator_order))

def add(p, q):
    """ Given two points, return their addition. """
    # Testing if p or q are at infinity.
    if p == (None, None): return q
    if q == (None, None): return p

    px, py = p
    qx, qy = q
    # Test if p and q are mirrored points on the same x.
    if px == qx and py == -qy: return (None, None)

    if p == q:
        # Point doubling.
        s = (3 * px**2 + curve_a) / (2 * py)
        rx = s**2 - 2 * px
        ry = s * (px - rx) - py
        return (rx, ry)
    else:
        # Regular addition.
        s = (py - qy) / (px - qx)
        rx = s**2 - px - qx
        ry = s * (px - rx) - py
        return (rx, ry)

def mult(p, k):
    """
    Given a point and a scalar, return the point multiplied by the scalar.
    """
    n = p
    r = (None, None)
    while k:
        if k % 2 == 1:
            r = add(r, n)
        n = add(n, n)
        k //= 2

    return r


def generate_keypair():
    """
    Generates a private scalar and a public point to be used as keypair in
    signature and encryption.
    """
    # 1 <= da < generator_order
    da = rand()
    qa = mult(generator, da)
    return (da, qa)

def generate_encryption_keypair(public_key):
    """
    Generates a private point S, from which the symmetric encryption key is
    derived, and a public point R to be transmitted to the recipient along with
    the message.
    """
    # 1 <= r < generator_order
    scalar_r = rand()
    point_r = mult(generator, scalar_r)
    return (mult(public_key, scalar_r), point_r)

def generate_decryption_key(private_key, point_r):
    """
    Given the private and public encryption parameter R, generates the same
    private point S used to derive the symmetric encryption key.
    """
    return mult(point_r, private_key)


def sign(private_key, hash_value, k=None):
    """
    Given a private key and a message hash, return the ephemeral keypair (r, s)
    to be published as signature.

    The nonce `k` can be specified through the last optional parameter for
    security testing (e.g. reusing nonces).
    """
    while True:
        # 0 < k < generator_order
        k = k or rand()
        r = mult(generator, k)[0]
        if r == 0:
            print('Unlucky r', k)
            continue
        s = F(hash_value + private_key * r) / k
        if s == 0:
            print('Unlucky s', k)
            continue
        else:
            break
    return (r, s)

def verify(public_key, hash_value, signature):
    """
    Given the signer's public key, the message hash_value and the ephemeral
    keypair used as signature, returns True or False depending if the signature
    is correct or not.
    """
    r, s = map(F, signature)
    w = 1 / s
    u1 = hash_value * w
    u2 = r * w
    p = add(mult(generator, u1), mult(public_key, u2))
    return int(p[0]) % generator_order == r

def factor_signatures(hash_value1, signature1, hash_value2, signature2):
    """
    Given two hashes and their signatures that used the same random nonce `k`,
    return the signer's private key. That's why randomness is important, folks.
    """
    r1, s1 = signature1
    r2, s2 = signature2
    assert r1 == r2 # Did they really reuse the nonce?
    r = int(r1)
    return (s2 * hash_value1 - s1 * hash_value2) / (r * (s1 - s2))

def compress(p):
    """
    Compresses a point by reducing p_y to its least significant bit. This
    operation is surprisingly reversible.
    """
    # TODO
    pass

if __name__ == '__main__':
    sk, pk = generate_keypair()
    print('Keypair:', sk, pk)

    s, r = generate_encryption_keypair(pk)
    assert s == generate_decryption_key(sk, r)

    signature = sign(sk, 10)
    print('Signature:', signature)
    assert verify(pk, 10, signature)

    signature1 = sign(sk, 10, 100)
    signature2 = sign(sk, 11, 100)
    print('Weak signatures:', signature1, signature2)
    broken_sk = factor_signatures(10, signature1, 11, signature2)
    assert broken_sk == sk

