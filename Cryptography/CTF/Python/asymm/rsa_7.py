""" from Crypto.Util.number import bytes_to_long, getPrime, inverse
from secret import flag

p, q = getPrime(512), getPrime(512)
n = p*q
e = 65537
print(n)
m = bytes_to_long(flag.encode())
print(pow(m, e, n))
phi = (p-1)*(q-1)
d = inverse(e, phi)

while True:
    req = input()
    dec = pow(int(req), d, n)
    print(dec % 2) """

import socket
from Crypto.Util.number import long_to_bytes
from fractions import Fraction

HOST = "130.192.5.212"
PORT = 6647
e = 65537

with socket.create_connection((HOST, PORT)) as sock:
    f = sock.makefile()  # wrap socket for readline()

    n = int(f.readline())
    c = int(f.readline())

    UL = Fraction(n)
    LL = Fraction(0)

    for i in range(1, 1025):
        s = c * pow(2**i, e, n) % n
        sock.sendall(str(s).encode() + b"\n")
        res = int(f.readline())  # read full response
        if res == 0:
            UL = (UL + LL) / 2
        elif res == 1:
            LL = (UL + LL) / 2

        if UL - LL < 1:
            break

    recovered_m = int(UL)
    print(long_to_bytes(recovered_m))
