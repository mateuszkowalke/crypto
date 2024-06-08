#include "minides.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define INPUT_SIZE 3
#define ROUNDS 8

unsigned int key = 0b101010101010;
int K[8] = {0, 1, 3, 2, 3, 2, 4, 5};

unsigned int IV = 0b111010001101;

int main() {
    uint8_t c;
    FILE *input_file = fopen("src/test.pbm", "rb");
    FILE *EBC = fopen("test_EBC.pbm", "wb");
    FILE *CBC = fopen("test_CBC.pbm", "wb");
    int lines_to_skip = 2;
    while (lines_to_skip > 0) {
        while ((c = getc(input_file)) != '\n') {
            if (feof(input_file)) {
                exit(1);
            }
            fputc(c, EBC);
            fputc(c, CBC);
        }
        fputc('\n', EBC);
        fputc('\n', CBC);
        lines_to_skip--;
    }

    uint8_t input[INPUT_SIZE];
    int n = 0;
    int prev = IV;
    while (!feof(input_file)) {
        input[n] = getc(input_file);
        printf("%u, ", input[n]);
        n++;
        if (n == INPUT_SIZE) {
            unsigned int input_num_1, input_num_2;
            input_num_1 = (input[0] << 4) + ((input[1] >> 4) & 0xF);
            input_num_2 = ((input[1] << 8) & 0xF00) + input[2];

            printf("{%u, %u}", input_num_1, input_num_2);

            unsigned long res_ebc = des_encode(input_num_1, key, K, ROUNDS);
            unsigned long res_cbc =
                des_encode(prev ^ input_num_1, key, K, ROUNDS);
            prev = res_cbc;
            printf("{%lu, %lu}", res_ebc, res_cbc);
            unsigned long res_ebc_2 = des_encode(input_num_2, key, K, ROUNDS);
            unsigned long res_cbc_2 =
                des_encode(prev ^ input_num_2, key, K, ROUNDS);
            prev = res_cbc_2;
            res_ebc = ((res_ebc << 12) & 0xFFF000) + res_ebc_2;
            res_cbc = ((res_cbc << 12) & 0xFFF000) + res_cbc_2;

            printf("{%lu, %lu, %lu}", (res_ebc >> 16) & 0xFF,
                   (res_ebc >> 8) & 0xFF, res_ebc & 0xFF);

            fputc((res_ebc >> 16) & 0xFF, EBC);
            fputc((res_ebc >> 8) & 0xFF, EBC);
            fputc(res_ebc & 0xFF, EBC);
            fputc((res_cbc >> 16) & 0xFF, CBC);
            fputc((res_cbc >> 8) & 0xFF, CBC);
            fputc(res_cbc & 0xFF, CBC);
            n = 0;
        }
    }

    fclose(EBC);
    fclose(CBC);
    fclose(input_file);
}
