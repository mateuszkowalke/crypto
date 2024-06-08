#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define CIPHER_SIZE 2048
#define AB_SIZE 64

char encoded[CIPHER_SIZE], ab_str[AB_SIZE];

size_t read_encoded(char *buf, size_t size);
size_t read_ab(char *buf, size_t size);
void parse_ab(char *ab_str, int *a, int *b);
void ensure_a_valid(int a);

int main(int argc, char **argv) {
  size_t encoded_size = read_encoded(encoded, CIPHER_SIZE);
  read_ab(ab_str, AB_SIZE);
  int a, b;
  parse_ab(ab_str, &a, &b);
  int offset = isupper(encoded[0]) ? 0x41 : 0x61;
  for (int i = 0; i < encoded_size; i++) {
    if (isalpha(encoded[i]))
      encoded[i] = ((encoded[i] - offset) * a + b) % 26 + offset;
  }
  printf("%s\n", encoded);
}

size_t read_encoded(char *buf, size_t size) {
  size_t n = 0;
  char c;

  while ((c = getchar()) != 0) {
    if (c > 0x2f && c < 0x3a) {
      ungetc(c, stdin);
      break;
    }
    *(buf + n++) = c;
  }

  while (isspace(c = *(buf + n - 1)))
    n--;

  *(buf + n) = 0;
  return n;
}

size_t read_ab(char *buf, size_t size) {
  size_t n = 0;
  char c;

  while ((c = getchar()) != 0 && c != '\n') {
    *(buf + n++) = c;
  }

  *(buf + n++) = 0;
  return n;
}

void parse_ab(char *ab_str, int *a, int *b) {
  char *split_ptr = strchr(ab_str, ' ');
  if (NULL == split_ptr) {
    printf("BŁĄD\n");
    exit(1);
  }
  *split_ptr = 0;
  *a = atoi(ab_str);
  *b = atoi(split_ptr + 1);
}

void ensure_a_valid(int a) {
    
}
