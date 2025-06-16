from pwn import xor
import binascii

# ChaCha20 uses XOR, nonce is reused (seed isn't important!)
ciphertext_flag = bytes.fromhex("f9595453999746660e0a88b190a3a64d599a50db37fb15be091cc472f59f563cb93bf4f4ca6bd8ad6b43757e4f89")

ciphertext_user = bytes.fromhex("fb4a4c428c993512347ea8c6e180d43d28f677ab4f8e79cb7e6bb41e8dea261fd51fd4d7bc4fa8d44e6104083db52bdfc874439358c37792d706554de001a4954ce1846f4d363fbbbf94be5cdb4e4b071d004ce1b32b50f5d3e08183")

known_msg = b"A" * len(ciphertext_flag)

xored = xor(ciphertext_flag, ciphertext_user)
recovered_flag = xor(xored, known_msg)

print("Recovered flag:", recovered_flag)