#include "minides.h"

#define INPUT_SIZE 12
#define ROUNDS 8

unsigned int key = 0b101010101010;
int K[8] = {0, 1, 3, 2, 3, 2, 4, 5};

int main() {
    char input[INPUT_SIZE + 1];
    scanf("%12s", &input);

    int input_num = 0;
    char *input_p = input + INPUT_SIZE - 1;
    for (int n = 0; input_p >= input; n++) {
        if (*input_p == '1') {
            input_num += (int)pow(2.0, (double)n);
        }
        input_p--;
    }

    unsigned int res = des_decode(input_num, key, K, ROUNDS);

    print_binary(res);
    printf("\n");
}
