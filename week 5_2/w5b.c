#include <stdio.h>

unsigned long long fastExpo(unsigned long long a, unsigned long long b, unsigned long long n) {
    unsigned long long result = 1;

    while (b > 0) {
        if (b % 2 == 1) {
            result = (result * a) % n;
        }

        a = (a * a) % n;
        b = b / 2;
    }

    return result;
}

int main() {
    unsigned long long a, b, n;

    printf("Enter base (a): ");
    scanf("%llu", &a);

    printf("Enter exponent (b): ");
    scanf("%llu", &b);

    printf("Enter modulus (n): ");
    scanf("%llu", &n);

    unsigned long long result = fastExpo(a, b, n);

    printf("%llu^%llu mod %llu = %llu\n", a, b, n, result);

    return 0;
}

