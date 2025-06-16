from pwn import xor
from Crypto.Cipher import AES
import binascii

plaintext = b"A" * 16
leak = b"mynamesuperadmin" 

print(plaintext)

IV = bytes.fromhex("9fde5ab3bf7bdc3b9db87493ecad3794")  
ciphertext = bytes.fromhex("be79209c17842d870852a2fae7cef39a")  

aes_dec_c = xor(plaintext, IV)

IV_new = xor(aes_dec_c, leak)

print("Ciphertext:", ciphertext.hex())
print("IV:", IV_new.hex())
