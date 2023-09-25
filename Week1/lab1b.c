#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

void affineEncrypt(char plaintext[], int a, int b) {
    for (int i = 0; plaintext[i] != '\0'; i++) {
        if (isalpha(plaintext[i])) {
            char ch = islower(plaintext[i]) ? 'a' : 'A';
            int x = plaintext[i] - ch;
            int encrypted = (a * x + b) % 26;
            printf("%c", encrypted + ch);
        } else {
            printf("%c", plaintext[i]);
        }
    }
}

void affineDecrypt(char ciphertext[], int a, int b) {
    int a_inverse = 0;
    for (int i = 0; i < 26; i++) {
        if ((a * i) % 26 == 1) {
            a_inverse = i;
            break;
        }
    }
    for (int i = 0; ciphertext[i] != '\0'; i++) {
        if (isalpha(ciphertext[i])) {
            char ch = islower(ciphertext[i]) ? 'a' : 'A';
            int y = ciphertext[i] - ch;
            int decrypted = (a_inverse * (y - b + 26)) % 26;
            printf("%c", decrypted + ch);
        } else {
            printf("%c", ciphertext[i]);
        }
    }
}

int main() {
    char input[100];
    int a, b;
    int choice;

    printf("Enter the text to encrypt/decrypt: ");
    fgets(input, sizeof(input), stdin);

    printf("Enter the key 'a' for the Affine cipher (must be coprime with 26): ");
    scanf("%d", &a);

    printf("Enter the key 'b' for the Affine cipher: ");
    scanf("%d", &b);

    printf("Enter 1 for encryption or 2 for decryption: ");
    scanf("%d", &choice);

    if (choice == 1) {
        printf("Encrypted text: ");
        affineEncrypt(input, a, b);
    } else if (choice == 2) {
        printf("Decrypted text: ");
        affineDecrypt(input, a, b);
    } else {
        printf("Invalid choice.");
    }

    return 0;
}
