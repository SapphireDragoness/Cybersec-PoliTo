#include <openssl/bn.h>
#include <stdio.h>

void print_hex_with_colons(const BIGNUM *bn) {
  char *hex = BN_bn2hex(bn);
  if (!hex) {
    fprintf(stderr, "Error converting BIGNUM to hex\n");
    return;
  }

  for (int i = 0; hex[i] != '\0'; i += 2) {
    if (i > 0)
      printf(":");
    printf("%c%c", hex[i], hex[i + 1]);
  }
  OPENSSL_free(hex);
  printf("\n");
}

int main() {
  BIGNUM *num1 = NULL, *num2 = NULL, *result = NULL;
  BN_CTX *ctx = BN_CTX_new();
  if (!ctx) {
    fprintf(stderr, "Failed to create BN_CTX\n");
    return 1;
  }

  num1 = BN_new();
  num2 = BN_new();
  result = BN_new();
  if (!num1 || !num2 || !result) {
    fprintf(stderr, "Failed to allocate BIGNUMs\n");
    return 1;
  }

  BN_hex2bn(&num1,
            "009EEE82DC2CD4A00C4F5A7B8663B0C1ED0677FCEBDE1A235DF4C3FF876A7DADC6"
            "07FAA835F6AE0503573E223676D50D574F99F958AD637AE745A6AAFA023423B69D"
            "34157B1141B6B1CAB91ACD2955BD42F504ABDF454A9D4ECA4E01F9F8745967EEB6"
            "A9FB96B7C09400178A530EB6D831C968E66438D3633A04D7886BF0E1AD607F41BD"
            "857BD904E1975B1F9B05CEAC2CC4553FB48B894D0A509A094E5E8F5B5F5569725F"
            "049B3A8A09B47F8DB2CA520E5EBFF4B0EEC9BADC934F6DD31F821AD9FC2CA73F18"
            "230DD744C728546784EE739265F01CE81E6D4D9565B4C84FB80462582BEE3264A0"
            "A7DC99250E505376BC30DB715E93D69F1F881C765D82C8593951");
  BN_hex2bn(&num2,
            "00D2C601326B4C4B855F527BB78ED68AE4C8767E6BC9249A3ECACD2FC9B875D4F9"
            "7111E1CFBE62D32C5FF9FD9BFAED62F3DF44C757FBEE9BB232CB5449296C692E30"
            "1D8C1FFAB18EE44966C1FB927C82CA60C940A40AB2DB50ECF6FF98A71623388D06"
            "D27CA9858AC22B4DD4E6F189E5B04254A05F3CDD7C64330511FBEE8B2607");

  // Compute the missing parameter (e.g., result = num1 * num2)
  BN_mul(result, num1, num2, ctx);

  printf("CRYPTO25{");
  print_hex_with_colons(result);
  printf("}\n");

  // Free resources
  BN_free(num1);
  BN_free(num2);
  BN_free(result);
  BN_CTX_free(ctx);

  return 0;
}
