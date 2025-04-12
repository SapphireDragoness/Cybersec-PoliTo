from Crypto.Cipher import ChaCha20
from Crypto.Random import get_random_bytes
import base64
import json

if __name__ == '__main__':

    ciphertext_base64 = input("Enter ciphertext in base64: ")
    ciphertext = base64.b64decode(ciphertext_base64)
    print(ciphertext)

    username = '{"username": "1234567890123"}'
    new_username = '{"username": "a", "admin": 1}'

    edt_ciphertext = bytearray(ciphertext)

    for i in range(len(new_username)):
        new_value = bytes(new_username[i].encode())
        new_int = ord(new_value) # ASCII code

        mask = ord(username[i]) ^ new_int
        edt_ciphertext[i] = ciphertext[i] ^ mask

    print(f'{base64.b64encode(edt_ciphertext).decode()}')

    user = json.loads('{"username": "a", "admin": 1}')


# a, "admin": True  i want to encrypt this
# 1234567890123456  this is my username
# {"username": "1234567890123456"}  this is what's being encrypted

# 1. decode ciphertext from base 64
# 2. turn ciphertext to bytearray
# 3. edt_ciphertext[index] = ciphertext[index] ^ mask
# 4. send