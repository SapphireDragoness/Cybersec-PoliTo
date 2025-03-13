#include <openssl/rand.h>
#include <stdio.h>
#include <string.h>

#define DIM 64

int main() {
  unsigned char rand1[DIM];
  unsigned char rand2[DIM];

  RAND_bytes(rand1, DIM);
  RAND_bytes(rand2, DIM);

  printf("Rand1: ");
  for (int i = 0; i < DIM; i++) {
    if (i != 0)
      printf("-");
    printf("%x", rand1[i]);
  }

  printf("\n\n");

  printf("Rand2: ");
  for (int i = 0; i < DIM; i++) {
    if (i != 0)
      printf("-");
    printf("%x", rand2[i]);
  }

  unsigned char k1[DIM];

  for (int i = 0; i < DIM; i++) {
    k1[i] = rand1[i] | rand2[i];
  }

  printf("\n\n");

  printf("K1, bytewise OR of rand1 and rand2: ");
  for (int i = 0; i < DIM; i++) {
    if (i != 0)
      printf("-");
    printf("%x", k1[i]);
  }

  unsigned char k2[DIM];

  for (int i = 0; i < DIM; i++) {
    k2[i] = rand1[i] & rand2[i];
  }

  printf("\n\n");

  printf("K2, bytewise AND of rand1 and rand2: ");
  for (int i = 0; i < DIM; i++) {
    if (i != 0)
      printf("-");
    printf("%x", k2[i]);
  }

  unsigned char key[DIM];

  for (int i = 0; i < DIM; i++) {
    key[i] = rand1[i] ^ rand2[i];
  }

  printf("\n\n");

  printf("Key, bytewise XOR of rand1 and rand2: ");
  for (int i = 0; i < DIM; i++) {
    if (i != 0)
      printf("-");
    printf("%02x", key[i]);
  }

  printf("\n\n");

  printf("...ok, now for the flag: ");

  unsigned char rand1_flag[] = {
      "ed-8a-3b-e8-17-68-38-78-f6-b1-77-3e-73-b3-f7-97-f3-00-47-76-54-ee-8d-51-"
      "0a-2f-10-79-17-f8-ea-d8-81-83-6e-0f-0c-b8-49-5a-77-ef-2d-62-b6-5e-e2-10-"
      "69-d6-cc-d6-a0-77-a2-0a-d3-f7-9f-a7-9e-a7-c9-08"};

  unsigned char rand2_flag[] = {
      "4c-75-82-ca-02-07-bd-1d-8d-52-f0-6c-7a-d6-b7-87-83-95-06-2f-e0-f7-d4-24-"
      "f8-03-68-97-41-4c-85-29-e5-0d-b0-e4-3c-ee-74-dc-18-8a-aa-26-f0-46-94-e8-"
      "52-91-4a-43-8f-dd-ea-bb-a8-cf-51-14-79-ec-17-c2"};

  unsigned char key_flag[DIM];

  printf("\n\n");

  for (int i = 0; i < DIM; i++) {
    if (i != 0)
      printf("-");
    printf("%02x", key_flag[i]);
  }

  printf("\n\n");

  return 0;
}