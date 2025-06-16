#include <openssl/err.h>
#include <openssl/evp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BUFFER 1024

void handle_errors() {
  ERR_print_errors_fp(stderr);
  abort();
}

void hex_to_bytes(const char *hex, unsigned char *bytes, size_t len) {
  for (size_t i = 0; i < len; i++) {
    sscanf(&hex[i * 2], "%2hhx", &bytes[i]);
  }
}

int main() {
  const char *key_hex =
      "0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF";
  const char *iv_hex = "11111111111111112222222222222222";
  const char *ciphertext_b64 = "jyS3NIBqenyCWpDI2jkSu+z93NkDbWkUMitg2Q==";

  unsigned char key[32];
  unsigned char iv[16];
  hex_to_bytes(key_hex, key, 32);
  hex_to_bytes(iv_hex, iv, 16);

  // Decode base64 ciphertext
  unsigned char ciphertext[MAX_BUFFER];
  int cipher_len = EVP_DecodeBlock(ciphertext, (unsigned char *)ciphertext_b64,
                                   strlen(ciphertext_b64));

  EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
  if (!ctx)
    handle_errors();

  if (!EVP_CipherInit_ex(ctx, EVP_chacha20(), NULL, key, iv, 0))
    handle_errors();

  unsigned char plaintext[MAX_BUFFER];
  int len, plaintext_len;
  if (!EVP_CipherUpdate(ctx, plaintext, &len, ciphertext, cipher_len))
    handle_errors();
  plaintext_len = len;

  if (!EVP_CipherFinal_ex(ctx, plaintext + len, &len))
    handle_errors();
  plaintext_len += len;

  EVP_CIPHER_CTX_free(ctx);

  printf("Decrypted text: %.*s\n", plaintext_len, plaintext);
  return 0;
}
