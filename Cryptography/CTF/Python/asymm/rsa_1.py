from Crypto.Util.number import long_to_bytes

# from secret import flag
from math import gcd

""" p, q = getPrime(64), getPrime(64)
n = p * q  # modulus
e = 65537  # exponent
print(n)  # 176278749487742942508568320862050211633
m = bytes_to_long(flag)  # base
print(pow(m, e, n))  # 46228309104141229075992607107041922411 """


p = 12271643243945501447
q = 14364722473065221639
e = 65537


c = 46228309104141229075992607107041922411
n = 176278749487742942508568320862050211633

phi = (p - 1) * (q - 1)
d = pow(e, -1, phi)
m = pow(c, d, n)
print(long_to_bytes(m))
