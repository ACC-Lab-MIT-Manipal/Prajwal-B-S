#include <stdio.h>
#include <string.h>
#include <ctype.h>

void vigenereEncrypt(char plaintext[], char keyword[]) {
    int keywordLength = strlen(keyword);
    for (int i = 0, j = 0; plaintext[i] != '\0'; i++) {
        if (isalpha(plaintext[i])) {
            char ch = islower(plaintext[i]) ? 'a' : 'A';
            int shift = tolower(keyword[j % keywordLength]) - 'a';
            int encrypted = (plaintext[i] - ch + shift) % 26;
            printf("%c", encrypted + ch);
            j++;
        } else {
            printf("%c", plaintext[i]);
        }
    }
}

void vigenereDecrypt(char ciphertext[], char keyword[]) {
    int keywordLength = strlen(keyword);
    for (int i = 0, j = 0; ciphertext[i] != '\0'; i++) {
        if (isalpha(ciphertext[i])) {
            char ch = islower(ciphertext[i]) ? 'a' : 'A';
            int shift = tolower(keyword[j % keywordLength]) - 'a';
            int decrypted = (ciphertext[i] - ch - shift + 26) % 26;
            printf("%c", decrypted + ch);
            j++;
        } else {
            printf("%c", ciphertext[i]);
        }
    }
}

int main() {
    char input[100];
    char keyword[50];

    printf("Enter the text to encrypt/decrypt: ");
    fgets(input, sizeof(input), stdin);

    printf("Enter the keyword for the Vigenère cipher: ");
    fgets(keyword, sizeof(keyword), stdin);
    keyword[strcspn(keyword, "\n")] = '\0'; // Remove newline character

    printf("Encrypted text: ");
    vigenereEncrypt(input, keyword);

    printf("\n");

    printf("Decrypted text: ");
    vigenereDecrypt(input, keyword);

    return 0;
}
