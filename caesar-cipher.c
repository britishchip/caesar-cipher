#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "ctype.h"


char *encodeCipher(char *plaintext, char *ciphertext, int key){
    char *output = malloc(strlen(plaintext));
    
    // C is beautiful: an abomination dedicateed to holy C
    //good luck trying to figure out this eyesore
    for (int i = 0; i < strlen(plaintext); i++) {
        while (plaintext[i] != '\0') {
            for (int j = 0; j<26; j++) {
                if (tolower(plaintext[i]) == ciphertext[j]) {
                    if ((j+key) > 25) {
                        output[i] = ciphertext[(j+key)-26];
                    } else {
                        output[i] = ciphertext[j+key];
                    }
                } else if (plaintext[i] == ' ') {
                    output[i] = ' ';
                }
            }
            break;
        }
    }
    //cant free the ptr befor returning, and cant free
    //after returning because nothing runs after return
    //beautiful skill issue
    return output;
}

char *decodeCipher(char *plaintext, char *ciphertext, int key){
    char *output = malloc(strlen(plaintext));

    // C is beautiful: an abomination dedicateed to holy C
    //good luck trying to figure out this eyesore
    for (int i = 0; i < strlen(plaintext); i++) {
        while (plaintext[i] != '\0') {
            for (int j = 0; j<26; j++) {
                if (tolower(plaintext[i]) == ciphertext[j]) {
                    if ((j-key) < 0) {
                        output[i] = ciphertext[(j-key)+26];
                    } else {
                        output[i] = ciphertext[j-key];
                    }
                } else if (plaintext[i] == ' ') {
                    output[i] = ' ';
                }
            }
            break;
        }
    }
    return output;
}


int main(int argc, char *argv[]){
    if (argc != 2) {
        printf("Usage: ./caesar-cipher -[mode]\n");
        printf("use -d to decode/ -e to encode\n");
        return 1;
    }

    char *arg2 = argv[1];
    char cipher[26];
    int idx = 0;
    // cipher wheel
    for (int i = 97; i <= 122; i++) {
        while (idx < 26) {
            cipher[idx] = (char)(i);
            idx++;
            break;
        }
    }

    char plaintext[100];
    int key;

    if (strcmp(arg2, "e") == 0) {
        printf("Enter the text to encode: ");
        fgets(plaintext, sizeof(plaintext), stdin);
        for (int i = 0; plaintext[i] != '\0'; i++) {
            if (isdigit(plaintext[i])) {
                printf("Plaintext should not include numerical digits.\n");
                return 1;
            }
        }
        printf("Enter the key(number): ");
        scanf("%d", &key);
        if (key > 25 || key < 0) {
            printf("Invalid key\n");
            return 1;
        }    
        char *result = encodeCipher(plaintext, cipher, key);
        printf("Your ciphertext: %s\n", result);

    } else if (strcmp(arg2, "d") == 0) {
        printf("Enter the text to decode: ");
        fgets(plaintext, sizeof(plaintext), stdin);
        for (int i = 0; plaintext[i] != '\0'; i++) {
            if (isdigit(plaintext[i])) {
                printf("Plaintext should not include numerical digits.\n");
                return 1;
            }
        }
        printf("Enter the key(number): ");
        scanf("%d", &key);
        if (key > 25 || key < 0) {
            printf("Invalid key\n");
            return 1;
        }    
        char *result = decodeCipher(plaintext, cipher, key);
        printf("Decoded text: %s\n", result);
    } else {
        printf("Bad argument\n");
        return 1;
    }
    
    return 0;
    
}
