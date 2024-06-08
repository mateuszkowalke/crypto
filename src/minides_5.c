#include "dyn_arr.h"
#include "minides.h"

#define INPUT_SIZE 12
#define K_INPUT_SIZE 8
#define ROUNDS 8

decl_dyn_arr_type(int);

int K[8] = {0, 4, 3, 2, 3, 5, 4, 1};
unsigned int IV = 0;

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
    char *input_p = input + n - 1;
    n = 0;
    for (int n = 0; input_p >= input; n++, input_p--) {
        if (*input_p == '1') {
            IV += (int)pow(2.0, (double)n);
        }
    }

    int prev = IV;
    for (int i = 0; i < inputs.len; i++) {
        unsigned int res = des_decode(prev ^ int_at(inputs, i), key, K, ROUNDS);
        print_binary(res);
        prev = int_at(inputs, i);
    }
    printf("\n");

    free_int_dyn_arr(inputs);
}
