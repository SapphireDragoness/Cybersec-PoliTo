#include <openssl/err.h>
#include <openssl/evp.h>
#include <stdio.h>
#include <string.h>

#define SECRET "this_is_my_secret"

int main(int argc, char **argv) {
  if (argc != 2) {
    fprintf(stderr, "Invalid parameters. Usage: %s filename\n", argv[0]);
    exit(1);
  }

  FILE *f_in;
  if ((f_in = fopen(argv[1], "r")) == NULL) {
    fprintf(stderr, "Couldn't open the input file, try again\n");
    exit(1);
  }

  EVP_MD_CTX *md = EVP_MD_CTX_new();
  EVP_DigestInit(md, EVP_sha512());

  fseek(f_in, 0, SEEK_END);
  long file_size = ftell(f_in);
  fseek(f_in, 0, SEEK_SET);

  unsigned char *file_content = malloc(file_size);

  fread(file_content, 1, file_size, f_in);
  fclose(f_in);

  EVP_DigestUpdate(md, SECRET, strlen(SECRET));
  EVP_DigestUpdate(md, file_content, file_size);
  EVP_DigestUpdate(md, SECRET, strlen(SECRET));

  unsigned char md_value[EVP_MD_size(EVP_sha512())];
  int md_len;

  EVP_DigestFinal_ex(md, md_value, &md_len);

  // void EVP_MD_CTX_free(EVP_MD_CTX *ctx);
  EVP_MD_CTX_free(md);

  printf("\nThe digest is: ");
  for (int i = 0; i < md_len; i++)
    printf("%02x", md_value[i]);
  printf("\n");

  return 0;
}