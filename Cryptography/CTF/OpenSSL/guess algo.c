#include <openssl/bio.h>
#include <openssl/buffer.h>
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

int base64_decode(const char *input, unsigned char *output) {
  BIO *b64 = BIO_new(BIO_f_base64());
  BIO *bio = BIO_new_mem_buf(input, -1);
  bio = BIO_push(b64, bio);
  BIO_set_flags(bio, BIO_FLAGS_BASE64_NO_NL);
  int length = BIO_read(bio, output, MAX_BUFFER);
  BIO_free_all(bio);
  return length;
}

int main() {
  const unsigned char key[] = "0123456789ABCDEF";
  const unsigned char iv[] = "0123456789ABCDEF";
  const char *ciphertext_b64 = "ZZJ+BKJNdpXA2jaX8Zg5ItRola18hi95MG8fA/9RPvg=";

  // Decode base64 ciphertext
  unsigned char ciphertext[MAX_BUFFER];
  int cipher_len = base64_decode(ciphertext_b64, ciphertext);

  const EVP_CIPHER *algorithms[] = {EVP_aes_128_cbc(), EVP_aes_128_ecb(),
                                    EVP_aes_128_cfb(), EVP_aes_128_ofb(),
                                    EVP_chacha20()};
  const char *algorithm_names[] = {"AES-128-CBC", "AES-128-ECB", "AES-128-CFB",
                                   "AES-128-OFB", "ChaCha20"};

  for (int i = 0; i < sizeof(algorithms) / sizeof(algorithms[0]); i++) {
    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
    if (!ctx)
      handle_errors();

    if (!EVP_CipherInit_ex(ctx, algorithms[i], NULL, key, iv, 0)) {
      EVP_CIPHER_CTX_free(ctx);
      continue; // Try next algorithm
    }

    unsigned char plaintext[MAX_BUFFER];
    int len, plaintext_len;
    if (!EVP_CipherUpdate(ctx, plaintext, &len, ciphertext, cipher_len)) {
      EVP_CIPHER_CTX_free(ctx);
      continue; // Try next algorithm
    }
    plaintext_len = len;

    if (!EVP_CipherFinal_ex(ctx, plaintext + len, &len)) {
      EVP_CIPHER_CTX_free(ctx);
      continue; // Try next algorithm
    }
    plaintext_len += len;

    EVP_CIPHER_CTX_free(ctx);

    plaintext[plaintext_len] = '\0';
    printf("Decryption successful! Algorithm: %s\n", algorithm_names[i]);
    for (int i = 0; i < plaintext_len; i++)
      printf("%2x", plaintext[i]);
    printf("\n");
    for (int i = 0; i < plaintext_len; i++)
      printf("%c", plaintext[i]);
    printf("\n");
    return 0;
  }

  printf("Decryption failed with all tested algorithms.\n");
  return 1;
}
