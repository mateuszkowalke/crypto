#include <ctype.h>
#include <stdio.h>
#include <unistd.h>

#define CIPHER_SIZE 2048
#define AB_SIZE 64

char encoded[CIPHER_SIZE], ab_str[AB_SIZE], decoded[CIPHER_SIZE];

size_t read_line(char *buf, size_t size);
int mod_inverse(int a, int c);

int main(int argc, char **argv) {
  size_t encoded_size = read_line(encoded, CIPHER_SIZE);
  decoded[encoded_size] = 0;
  int offset = isupper(encoded[0]) ? 0x41 : 0x61;
  for (int a = 1; a <= 26; a++) {
    int inv_a = mod_inverse(a, 26);
    if (inv_a == -1) continue;
    for (int b = 0; b < 26; b++) {
      for (int i = 0; i < encoded_size; i++) {
        if (isalpha(encoded[i])) {
            decoded[i] = ((encoded[i] - offset - b + 26) * inv_a) % 26 + offset;
        } else {
            decoded[i] = encoded[i];
        }
      }
      printf("A=%d B=%d %s\n", a, b, decoded);
    }
  }
}

size_t read_line(char *buf, size_t size) {
  size_t n = 0;
  char c;

  while ((c = getchar()) != 0 && c != '\n') {
    *(buf + n++) = c;
  }

  while (isspace(c = *(buf + n - 1)))
    n--;

  *(buf + n) = 0;
  return n;
}

int mod_inverse(int a, int c) {
  for (int i = 1; i < c; i++) {
    if (a * i % c == 1)
      return i;
  }
  return -1;
}
