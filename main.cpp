#include <cmath>
#include <iostream>
#include <random>
#include "lb2rsa.h"

int main() {
    RSA* d0e0n0 = new RSA();
    RSA* d1e1n1 = new RSA();
    uint64_t ti = 123456789;

    uint64_t e1t = d1e1n1->encrypt(ti);
    uint64_t d1e1t = d1e1n1->decrypt(e1t);
    if(d1e1t != ti) {
        printf("Original value and decrypted do not match!\n");
        return 1;
    }

    printf("Input: %ld\n", ti);
    printf("Encrypted: %ld\n", e1t);
    printf("Decrypted: %ld\n", d1e1t);
    printf("--------------------------\n");

    uint64_t e0d1e1t = d0e0n0->encrypt(d1e1t);
    uint64_t d0e0d1e1t = d0e0n0->decrypt(e0d1e1t);
    if(d0e0d1e1t != d1e1t) {
        printf("Original value and decrypted do not match!\n");
        return 1;
    }

    printf("Input: %ld\n", d1e1t);
    printf("Encrypted: %ld\n", e0d1e1t);
    printf("Decrypted: %ld\n", d0e0d1e1t);
    printf("--------------------------\n");

    delete d0e0n0;
    delete d1e1n1;
    return 0;
}
