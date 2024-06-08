#include "dyn_arr.h"
#include "minides.h"

#define INPUT_SIZE 12
#define K_INPUT_SIZE 8
#define ROUNDS 8

decl_dyn_arr_type(int);

int main() {
    int_dyn_arr_t inputs = new_int_dyn_arr(16);
    char input[INPUT_SIZE];
    char c;
    int n = 0;
    while ((c = getchar()) != '\n' && c != 0) {
        input[n] = c;
        n++;
        if (n == INPUT_SIZE) {
            int input_num = 0;
            char *input_p = input + INPUT_SIZE - 1;
            for (int n = 0; input_p >= input; n++, input_p--) {
                if (*input_p == '1') {
                    input_num += (int)pow(2.0, (double)n);
                }
            }
            push_int(&inputs, input_num);
            n = 0;
        }
    }

    n = 0;
    int i = 0;
    unsigned int key = 0;
    while ((c = getchar()) != '\n' && c != 0) {
        input[n] = c;
        n++;
        if (n == INPUT_SIZE) {
            char *input_p = input + n - 1;
            for (int n = 0; input_p >= input; n++, input_p--) {
                if (*input_p == '1') {
                    key += (int)pow(2.0, (double)(n + i));
                }
            }
            i += INPUT_SIZE;
            n = 0;
        }
    }

    n = 0;
    while ((c = getchar()) != '\n' && c != 0) {
        input[n] = c;
        n++;
    }
    int K[K_INPUT_SIZE];
    char *input_p = input;
    n = 0;
    char str[2];
    str[1] = 0;
    for (int n = 0; n < K_INPUT_SIZE; n++, input_p++) {
        str[0] = *input_p;
        K[n] = atoi(str);
    }

    for (int i = 0; i < inputs.len; i++) {
        unsigned int res = des_decode(int_at(inputs, i), key, K, ROUNDS);
        print_binary(res);
    }
    printf("\n");

    free_int_dyn_arr(inputs);
}
