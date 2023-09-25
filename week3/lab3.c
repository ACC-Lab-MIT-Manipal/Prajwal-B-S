#include <stdio.h>

// Permutation functions
int permute8(int value, int permutation[]) {
    int result = 0;
    for (int i = 0; i < 8; i++) {
        result |= ((value >> (8 - permutation[i])) & 1) << (7 - i);
    }
    return result;
}

// S-boxes
int sbox0[4][4] = {
    {1, 0, 3, 2},
    {3, 2, 1, 0},
    {0, 2, 1, 3},
    {3, 1, 3, 2}
};

int sbox1[4][4] = {
    {0, 1, 2, 3},
    {2, 0, 1, 3},
    {3, 0, 1, 0},
    {2, 1, 0, 3}
};

// SDES functions
int f(int value, int subkey) {
    int expanded = permute8(value, (int[]){4, 1, 2, 3, 2, 3, 4, 1});
    int xored = expanded ^ subkey;
    int row = ((xored & 0x08) >> 2) | (xored & 0x01);
    int col = (xored >> 1) & 0x03;
    int sboxValue = (sbox0[row][col] << 2) | sbox1[row][col];
    return permute8(sboxValue, (int[]){2, 4, 3, 1, 4, 3, 2, 1});
}

int encrypt(int plaintext, int key) {
    int subkey1 = permute8(key, (int[]){3, 5, 2, 7, 4, 10, 1, 9});
    int subkey2 = permute8(key, (int[]){5, 2, 7, 4, 9, 1, 8, 0});

    int initialPermutation = permute8(plaintext, (int[]){2, 6, 3, 1, 4, 8, 5, 7});
    int left = initialPermutation >> 4;
    int right = initialPermutation & 0x0F;

    int fResult = f(right, subkey1) ^ left;
    int newRight = fResult ^ right;

    fResult = f(newRight, subkey2) ^ newRight;
    int newLeft = fResult ^ left;

    int finalPermutation = (newLeft << 4) | newRight;
    return permute8(finalPermutation, (int[]){4, 1, 3, 5, 7, 2, 8, 6});
}

int decrypt(int ciphertext, int key) {
    // Decryption is the same as encryption, but using the subkeys in reverse order
    int subkey1 = permute8(key, (int[]){3, 5, 2, 7, 4, 10, 1, 9});
    int subkey2 = permute8(key, (int[]){5, 2, 7, 4, 9, 1, 8, 0});

    int initialPermutation = permute8(ciphertext, (int[]){2, 6, 3, 1, 4, 8, 5, 7});
    int left = initialPermutation >> 4;
    int right = initialPermutation & 0x0F;

    int fResult = f(right, subkey2) ^ left;
    int newRight = fResult ^ right;

    fResult = f(newRight, subkey1) ^ newRight;
    int newLeft = fResult ^ left;

    int finalPermutation = (newLeft << 4) | newRight;
    return permute8(finalPermutation, (int[]){4, 1, 3, 5, 7, 2, 8, 6});
}

int main() {
    int plaintext, key;

    printf("Enter 8-bit plaintext (in hexadecimal): ");
    scanf("%x", &plaintext);

    printf("Enter 10-bit key (in hexadecimal): ");
    scanf("%x", &key);

    printf("Plaintext:  %x\n", plaintext);
    printf("Key:        %x\n", key);

    int ciphertext = encrypt(plaintext, key);
    printf("Ciphertext: %x\n", ciphertext);

    int decrypted = decrypt(ciphertext, key);
    printf("Decrypted:  %x\n", decrypted);

    return 0;
}
