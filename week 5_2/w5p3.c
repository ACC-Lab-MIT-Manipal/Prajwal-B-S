#include <stdio.h>
#include <math.h>

int gcd(int a, int b) {
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

long long fastExponentiation(long long base, long long exponent, long long modulus) {
    long long result = 1;

    base %= modulus;

    while (exponent > 0) {
        if (exponent % 2 == 1)
            result = (result * base) % modulus;

        base = (base * base) % modulus;
        exponent /= 2;
    }

    return result;
}

int findModularInverse(int a, int m) {
   for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1) {
            return x;
        }
    }
    return -1;
}

int main() {
    int p, q, n, phi, e, d;

    printf("Enter two prime numbers (p and q): ");
    scanf("%d %d", &p, &q);

    n = p * q;

    phi = (p - 1) * (q - 1);

    for (e = 2; e < phi; e++) {
        if (gcd(e, phi) == 1)
            break;
    }

    d = findModularInverse(e, phi);

    printf("\nPublic Key (e, n): (%d, %d)\n", e, n);
    printf("Private Key (d, n): (%d, %d)\n", d, n);

    int plaintext;
    printf("\nEnter plaintext to be encrypted: ");
    scanf("%d", &plaintext);

    long long ciphertext = fastExponentiation(plaintext, e, n);
    printf("Ciphertext: %lld\n", ciphertext);

    long long decryptedText = fastExponentiation(ciphertext, d, n);
    printf("Decrypted Text: %lld\n", decryptedText);

    return 0;
}

