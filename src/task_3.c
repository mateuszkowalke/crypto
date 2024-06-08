#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char decode(char c, int i);

int main(int argc, char **argv) {
  if (argc != 2) {
    printf("Expected one line of text encoded with caesar cipher\n");
    exit(1);
  }
  char *encoded = argv[1];
  char *decoded = malloc((strlen(encoded) + 1) * sizeof(char));
  if (decoded == NULL) {
    printf("Error malloc");
    exit(1);
  }
  for (int i = 1; i < 53; i++) {
    char *src = encoded;
    char *dst = decoded;
    while ((*dst++ = *src++) != 0) {
      char c = *(dst - 1);
      if (!isalpha(c))
        continue;
      c = decode(c, i);
      *(dst - 1) = c;
    }
    printf("Klucz: %d | Tekst: %s\n", i, decoded);
  }
}

// decodes ascii alpha char given caesar cipher offset
char decode(char c, int i) {
  if (c >= 65 && c <= 90) {
    c -= 65;
  } else {
    c -= 97 - 26;
  }
  c += 52;
  c -= i;
  c %= 52;
  if (c < 26) {
    c += 65;
  } else {
    c += 97 - 26;
  }
  return c;
}
