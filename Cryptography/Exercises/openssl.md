# OpenSSL

C and C++ library containing implementations of various cryptographic functions.

## OpenSSL flow

1. Include OpenSSL libraries (such as `openssl/evp.h`, `openssl/rand.h`)
2. Load OpenSSL facilities (such as `OpenSSL_add_all_algorithms();`)
3. Create context by selecting a crypto tool
4. Initialize context by adding implementation specific details
5. Operate on the context by passing data to the algorithm
6. Finalize the context by extracting data from the algorithm
7. Destroy the context to free memory
8. Free OpenSSL facilies data

In OpenSSL:

- Algorithms are cryptographic primitives
- Operations are groups of "homogeneous" algorithms
- Providers are components that expose algorithm implementations

## Random numbers with OpenSSL

OpenSSL RAND provides a cryptographically secure Pseudo-Random Number Generator (PRNG), which needs a seed to be properly initialized.

OpenSSL provides three PRNGs:

- public PRNG, tha main one
- private PRNG, used to generate numbers visible only within a program
- primary PRNG, only used to seed the public and private ones

### RAND functions

- `int RAND_bytes(unsigned char *buf, int num);`: generates num random bytes and stores them in the buffer pointed by buf
- `int RAND_priv_bytes(unsigned char *buf, int num);`: for private numbers
- `RAND_load_file`: load entropy source (e.g. /dev/random)

## Symmetric encryption

OpenSSL implements symmetric encryption with incremental functions, through the EVP API. The EVP API provides a context, `EVP_CIPHER_CTX`, and functions for:

- context creation/destruction: `EVP_CIPHER_CTX_new` / `EVP_CIPHER_CTX_cleanup` / …
- context initialization: e.g., (`EVP_EncryptInit` / `EVP_DecryptInit`) or `EVP_CipherInit`
- encryption/decryption: `EVP_EncryptUpdate` or `EVP_CipherUpdate`
- finalization: `EVP_EncryptFinal` or `EVP_CipherFinal`

### Encryption

```c
ctx = context_initialize(encrypt, cipher, mode, key, iv, …);
cycle:
ciphertext_fragment = encrypt_update(ctx, plaintext_fragment);
end:
ciphertext_fragment = encrypt_finalize(ctx);
```

### Decryption

```c
ctx = context_initialize(decrypt, cipher, mode, key, iv, …);
cycle:
plaintext_fragment = decrypt_update(ctx, ciphertext_fragment);
end:
plaintext_fragment = decrypt_finalize(ctx);
```

## Digests and MACs