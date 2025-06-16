""" from Crypto.Util.number import bytes_to_long, getPrime, inverse
from secret import flag

p, q = getPrime(512), getPrime(512)
n = p * q
e = 65537
print(n)
m = bytes_to_long(flag.encode())
print(pow(m, e, n))

req = input()

if req[0] == "e":
    print(pow(int(req[1:]), e, n))
elif req[0] == "d":
    phi = (p - 1) * (q - 1)
    d = inverse(e, phi)
    dec = pow(int(req[1:]), d, n)
    assert dec != m
    print(dec) """

# I know n, e and c -> must get p and q
# e is too large
# multiply and then divide for a number s

import socket
from math import gcd
from Crypto.Util.number import inverse, long_to_bytes, bytes_to_long
import random

n = int(input("Enter n: "))
e = 65537
c = int(input("Enter c: "))

# choose a random s such that gcd(s, n) == 1
while True:
    s = random.randint(2, n - 1)
    if gcd(s, n) == 1:
        break

# compute modified ciphertext c'
c_p = (c * pow(s, e, n)) % n

print(f"c':{c_p}")
m_p = int(input("Enter m': "))

s_inv = inverse(s, n)
m = (m_p * s_inv) % n

flag = long_to_bytes(m).decode()
print(flag)
