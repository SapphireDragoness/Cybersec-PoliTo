#include <stdio.h>
#include <string.h>

#include <openssl/evp.h>

#define ENCRYPT 1
#define DECRYPT 0

#define MAX_BUFFER 1024

int main() {
  const unsigned char key[] = "0123456789ABCDEF";
  const unsigned char iv[] = "0123456789ABCDEF";
  const char *ciphertext_hex =
      "65927e04a24d7695c0da3697f1983922d46895ad7c862f79306f1f03ff513ef8";

  EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
  EVP_CipherInit(ctx, EVP_aes_128_cbc(), key, iv, DECRYPT);

  EVP_CIPHER_CTX_set_padding(ctx, 0);

  // convert hexstring into bytes
  int ciphertext_len = strlen(ciphertext_hex) / 2;
  unsigned char ciphertext_binary[ciphertext_len];
  for (int i = 0; i < ciphertext_len; i++) {
    sscanf(&ciphertext_hex[2 * i], "%2hhx", &ciphertext_binary[i]);
  }
  printf("Binary ciphertext: ");
  for (int i = 0; i < ciphertext_len; i++)
    printf("%02x", ciphertext_binary[i]);
  printf("\n");

  unsigned char decrypted[ciphertext_len];

  int update_len, final_len;
  int decrypted_len = 0;
  EVP_CipherUpdate(ctx, decrypted, &update_len, ciphertext_binary,
                   ciphertext_len);
  decrypted_len += update_len;
  printf("update size: %d\n", decrypted_len);

  EVP_CipherFinal_ex(ctx, decrypted + decrypted_len, &final_len);
  decrypted_len += final_len;

  EVP_CIPHER_CTX_free(ctx);

  printf("Plaintext length = %d\n", decrypted_len);
  for (int i = 0; i < decrypted_len; i++)
    printf("%2x", decrypted[i]);
  printf("\n");
  printf("Decrypted content:");
  for (int i = 0; i < decrypted_len; i++)
    printf("%c", decrypted[i]);
  printf("\n");

  EVP_CIPHER_CTX *ctx2 = EVP_CIPHER_CTX_new();
  EVP_CipherInit(ctx2, EVP_aes_128_cbc(), key, iv, ENCRYPT);

  EVP_CIPHER_CTX_set_padding(ctx2, 0);

  unsigned char encrypted[ciphertext_len];

  int update_len2, final_len2;
  int encrypted_len = 0;

  EVP_CipherUpdate(ctx2, encrypted, &update_len2, decrypted, ciphertext_len);
  encrypted_len += update_len2;
  printf("update size: %d\n", encrypted_len);

  EVP_CipherFinal_ex(ctx2, encrypted + encrypted_len, &final_len2);
  encrypted_len += final_len2;

  EVP_CIPHER_CTX_free(ctx2);

  printf("Plaintext length = %d\n", encrypted_len);
  printf("Encrypted content (binary):");
  for (int i = 0; i < encrypted_len; i++)
    printf("%2x", encrypted[i]);
  printf("\n");
  printf("Encrypted content (ASCII):");
  for (int i = 0; i < encrypted_len; i++)
    printf("%c", encrypted[i]);
  printf("\n");

  return 0;
}
