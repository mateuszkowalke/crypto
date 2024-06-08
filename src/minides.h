#include <stddef.h>
#include <stdio.h>
#include <math.h>

int Sbox1[16] = {0b101, 0b010, 0b001, 0b110, 0b011, 0b100, 0b111, 0b000,
                 0b001, 0b100, 0b110, 0b010, 0b000, 0b111, 0b101, 0b011};
int Sbox2[16] = {0b100, 0b000, 0b110, 0b101, 0b111, 0b001, 0b011, 0b010,
                 0b101, 0b011, 0b000, 0b111, 0b110, 0b010, 0b001, 0b100};

// this reverses 8 bits
unsigned char reverse(unsigned int b) {
   b = (b & 0b11110000) >> 4 | (b & 0b00001111) << 4;
   b = (b & 0b11001100) >> 2 | (b & 0b00110011) << 2;
   b = (b & 0b10101010) >> 1 | (b & 0b01010101) << 1;
   return b;
}

void print_binary(unsigned int n) {
    char buf[13];
    size_t buf_i = 0;
    unsigned int d = 2048;
    while (d >= 1) {
        buf[buf_i++] = n >= d ? '1' : '0';
        n = n >= d ? n - d : n;
        d /= 2;
    }
    buf[buf_i] = 0;
    printf("%s", buf);
}

// this expects key to be 8 bits
unsigned int f(unsigned int k, unsigned int R, int *K) {
    unsigned int er = 0;
    for (int i = 0; i < 8; i++) {
        er += (R >> K[i] & 1) << i;
    }
    return (Sbox1[(er ^ k) >> 4] << 3) + Sbox2[(er ^ k) & 15];
}

// this expects key to be 12 bits
unsigned int des_encode(unsigned int input, unsigned int key, int *K, int rounds) {
    unsigned int L = (input & 0b111111000000) >> 6;
    unsigned int R = input & 0b000000111111;
    key += ((key << 12) & 0b111111111111000000000000);

    for (int i = 0; i < rounds - 1; i++) {
        unsigned int Li, Ri;
        Li = R;
        Ri = L ^ f((key >> (16 - i - 1)) & 0b11111111, R, K);
        L = Li;
        R = Ri;
    }
    return (R << 6) + L;
}

unsigned int des_decode(unsigned int input, unsigned int key, int *K, int rounds) {
    unsigned int L = (input & 0b111111000000) >> 6;
    unsigned int R = input & 0b000000111111;
    key += ((key << 12) & 0b111111111111000000000000);

    for (int i = 0; i < rounds - 1; i++) {
        unsigned int Li, Ri;
        Li = R;
        Ri = L ^ f(reverse((key >> i) & 0b11111111), R, K);
        L = Li;
        R = Ri;
    }
    return (R << 6) + L;
}

