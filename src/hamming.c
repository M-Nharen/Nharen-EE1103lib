#include "EE1103lib.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int hamming(unsigned char* a, unsigned char* b, int N) 
{
    int H = 0;
    for (int i = 0; i < N; i++) {
        int bit_a = (a[i / 8] >> (7 - (i % 8))) & 1;  
        int bit_b = (b[i / 8] >> (7 - (i % 8))) & 1;  
        if (bit_a != bit_b)
            H++;
    }
    return H;
}

// Inserts M bits from src[] into dest[] starting at bit offset d (MSB-first, big-endian)
void insert_bits(unsigned char *dest, unsigned char *src, int d, int M)
{
    for (int i = 0; i < M; i++) {
        int pos = d + i;                                 // current position in destination
        int dest_byte = pos / 8;                         // byte index in dest
        int dest_bit = pos % 8;                          // bit index within byte (MSB-first)
        int bit_val = (src[i / 8] >> (7 - (i % 8))) & 1; // extract bit from src (MSB-first)

        if (bit_val)
            dest[dest_byte] |= (1 << (7 - dest_bit));    // set bit
        else
            dest[dest_byte] &= ~(1 << (7 - dest_bit));   // clear bit
    }
}

unsigned char *generate_random_bits(int N) // returns a char * pointer with randomly generated bits
{
    int nbytes = (N + 7) / 8;  // number of bytes needed
    unsigned char *block = malloc(nbytes);
    if (!block) return NULL;

    for (int i = 0; i < nbytes; i++) {
        block[i] = 0;
        for (int b = 0; b < 8; b++) {
            int bit_pos = 7 - b; // MSB-first
            if (((double)rand() / RAND_MAX) < 0.5)
                block[i] |= (1 << bit_pos); // set bit randomly
        }
    }

    // zero out unused bits if N not multiple of 8
    int extra_bits = nbytes * 8 - N;
    if (extra_bits > 0)
        block[nbytes - 1] &= ~((1 << extra_bits) - 1);

    return block; // caller must free()
}

void add_noise(unsigned char *block, int N, double p) //adds noise to a block of size N flipping with probability p
{
    for (int i = 0; i < N; i++) {
        double r = (double)rand() / RAND_MAX;
        if (r < p) {
            int byte = i / 8;
            int bit = i % 8;
            block[byte] ^= (1 << (7 - bit)); // flip bit (MSB-first)
        }
    }
}
