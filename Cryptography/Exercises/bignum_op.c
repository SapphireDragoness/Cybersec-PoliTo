#include <openssl/bn.h>
#include <openssl/err.h>

int main() {
  // a newly instantiated BIGNUM is initialized to 0
  char a_hex[] = "11111111111111111111111111111111";
  char b_hex[] = "22222222222222222222222222222222";
  char c_hex[] = "3333";
  char d_hex[] = "2341234123412341234";

  BIGNUM *a = BN_new();
  // creeate from decimal string
  BN_hex2bn(&a, a_hex);
  BIGNUM *b = BN_new();
  BN_hex2bn(&b, b_hex);

  /* https://www.openssl.org/docs/man1.0.2/man3/BN_add.html */

  // add two numbers
  BIGNUM *aplusb = BN_new();
  BN_add(aplusb, a, b);
  // BN_add(a,a,b);
  BN_print_fp(stdout, aplusb);
  puts("");
  printf("%lu\n", BN_get_word(aplusb));

  /*
  For all functions, 1 is returned for success, 0 on error.
  */

  /*
  int BN_mod_exp(BIGNUM *r, BIGNUM *a, const BIGNUM *p,
         const BIGNUM *m, BN_CTX *ctx);
  */
  BN_CTX *ctx = BN_CTX_new();
  BIGNUM *res = BN_new();
  BIGNUM *c = BN_new();
  BIGNUM *d = BN_new();

  BN_hex2bn(&c, c_hex);
  BN_hex2bn(&d, d_hex);

  // a^b mod m
  if (!BN_mod_exp(res, aplusb, c, d, ctx)) {
    ERR_print_errors_fp(stdout);
    exit(1);
  }

  BN_print_fp(stdout, res);
  puts("");

  return 0;
}