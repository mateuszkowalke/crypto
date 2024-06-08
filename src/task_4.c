#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char decode(char c, int i);

int main(int argc, char **argv) {
  if (argc != 3) {
    printf("Expected one line of text encoded with caesar cipher and one line "
           "of partially decoded text\n");
    exit(1);
  }
  char *encoded = argv[1];
  char *decoded_sample = argv[2];
  int sample_offset = 0;
  char *last_space = strrchr(decoded_sample, ' ');
  if (last_space != NULL) {
    sample_offset = last_space - decoded_sample + 1;
  }
  int sample_size = strlen(decoded_sample + sample_offset);
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
    if (strncmp(decoded + sample_offset, decoded_sample + sample_offset,
                sample_size) == 0) {
      printf("%s\n", decoded);
      printf("%d\n", i);
    }
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
