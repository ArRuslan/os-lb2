#include <cmath>
#include <iostream>
#include <random>

uint64_t randrange(uint64_t min, uint64_t max) {
    std::random_device rd;
    std::mt19937_64 eng(rd());
    std::uniform_int_distribution<uint64_t> distr;

    uint64_t range = max - min + 1;
    return distr(eng) % range + min;
}

uint64_t modpow(uint64_t base, uint64_t exp, uint64_t mod) {
    uint64_t x = 1, y = base;
    while (exp > 0) {
        if (exp % 2 == 1) {
            x = x * y % mod; // multiplying with base
        }
        y = y * y % mod; // squaring the base
        exp /= 2;
    }
    return x % mod;
}

uint64_t gcdExtended(uint64_t a, uint64_t b, uint64_t *x, uint64_t *y) {
    // Base Case
    if (a == 0) {
        *x = 0, *y = 1;
        return b;
    }

    // To store results of recursive call
    uint64_t x1, y1;
    uint64_t gcd = gcdExtended(b % a, a, &x1, &y1);

    // Update x and y using results of recursive
    // call
    *x = y1 - (b / a) * x1;
    *y = x1;

    return gcd;
}

uint64_t modinv(uint64_t x, uint64_t y) {
    uint64_t a, b;
    uint64_t g = gcdExtended(x, y, &a, &b);
    if (g != 1)
        return 0;

    return (a % y + y) % y;
}

uint64_t modinv2(uint64_t u, uint64_t v)
{
    uint64_t inv, u1, u3, v1, v3, t1, t3, q;
    int64_t iter;
    u1 = 1;
    u3 = u;
    v1 = 0;
    v3 = v;
    iter = 1;
    while(v3 != 0)
    {
        q = u3 / v3;
        t3 = u3 % v3;
        t1 = u1 + q * v1;
        u1 = v1;
        v1 = t1;
        u3 = v3;
        v3 = t3;
        iter = -iter;
    }
    if(u3 != 1)
        return  0;
    if(iter < 0)
        inv = v - u1;
    else
        inv = u1;
    return inv;
}

int LOW_PRIMES[] = {
    3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101, 103, 107, 109,
    113, 127, 131, 137, 139, 149, 151, 157, 163, 167, 173, 179, 181, 191, 193, 197, 199, 211, 223, 227, 229, 233, 239,
    241, 251, 257, 263, 269, 271, 277, 281, 283, 293, 307, 311, 313, 317, 331, 337, 347, 349, 353, 359, 367, 373, 379,
    383, 389, 397, 401, 409, 419, 421, 431, 433, 439, 443, 449, 457, 461, 463, 467, 479, 487, 491, 499, 503, 509, 521,
    523, 541, 547, 557, 563, 569, 571, 577, 587, 593, 599, 601, 607, 613, 617, 619, 631, 641, 643, 647, 653, 659, 661,
    673, 677, 683, 691, 701, 709, 719, 727, 733, 739, 743, 751, 757, 761, 769, 773, 787, 797, 809, 811, 821, 823, 827,
    829, 839, 853, 857, 859, 863, 877, 881, 883, 887, 907, 911, 919, 929, 937, 941, 947, 953, 967, 971, 977, 983, 991,
    997
};

bool rabin_miller(uint64_t n) {
    uint64_t s = n - 1;
    uint64_t t = 0;
    while ((s & 1) == 0) {
        s = s / 2;
        t++;
    }
    uint64_t k = 0;
    while (k < 128L) {
        uint64_t a = randrange(2, n - 1);
        uint64_t v = modpow(a, s, n);
        if (v != 1) {
            uint64_t i = 0;
            while (v != n - 1) {
                if (t - 1 == i)
                    return false;
                i++;
                v = (v * v) % n;
            }
        }
        k += 2L;
    }

    return true;
}

bool is_prime(uint64_t n) {
    if (n < 3 || (n & 1) == 0)
        return false;

    for (int p: LOW_PRIMES) {
        if (n == p)
            return true;
        if (n % p == 0)
            return false;
    }

    return rabin_miller(n);
}

uint64_t gen_prime(int k) {
    uint64_t r = 100L * (log2(k) + 1);
    while (r > 0) {
        uint64_t n = randrange(pow(2, k - 1), pow(2, k));
        r--;
        if (is_prime(n))
            return n;
    }

    return -1;
}

struct PQ {
    unsigned int p;
    unsigned int q;
};

struct PubKey {
    uint64_t n;
    unsigned int e;
};

struct PrivKey {
    uint64_t d;
    uint64_t n;
};

PQ gen_pq() {
    return PQ{(uint32_t) gen_prime(32), (uint32_t) gen_prime(32)};
}

void encrypt(PubKey key, char *in, char *out, char len) {
}

int main() {
    PQ pq = gen_pq();
    uint64_t N = pq.p * pq.q;
    uint64_t phi_N = (pq.p - 1) - (pq.q - 1);
    uint32_t e = 0x10001;
    uint64_t d = modinv(e, phi_N);
    auto pubKey = PubKey{N, e};
    auto privKey = PrivKey{d, N};

    uint64_t input = 123456789;
    uint64_t encrypted = modpow(input, pubKey.e, pubKey.n);
    uint64_t decrypted = modpow(encrypted, privKey.d, privKey.n);

    std::cout << input << std::endl;
    std::cout << encrypted << std::endl;
    std::cout << decrypted << std::endl;
    return 0;
}
