#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define HEXAGON_POINTS 6
#define HEX_SIZE 10

typedef struct {
    int x, y;
} Point;

// Function to compute c based on the point in the hexagon
int compute_c(int x, int y) {
    return (x * x + y * y) % 256;
}

// Generate hexagon points based on input parameters
void generate_hexagon(Point hexagon[HEXAGON_POINTS], int size) {
    int angle = 60;
    for (int i = 0; i < HEXAGON_POINTS; ++i) {
        hexagon[i].x = size * cos(i * angle * M_PI / 180);
        hexagon[i].y = size * sin(i * angle * M_PI / 180);
    }
}

// Encrypt data using hexagon schema
void encrypt(const char *input, char *output, const unsigned char *key, size_t key_length) {
    Point hexagon[HEXAGON_POINTS];
    generate_hexagon(hexagon, HEX_SIZE);

    for (size_t i = 0; i < strlen(input); ++i) {
        int c = compute_c(hexagon[i % HEXAGON_POINTS].x, hexagon[i % HEXAGON_POINTS].y);
        output[i] = input[i] ^ key[c % key_length];
    }
    output[strlen(input)] = '\0'; // Null-terminate the output
}

// Decrypt data using hexagon schema
void decrypt(const char *input, char *output, const unsigned char *key, size_t key_length) {
    encrypt(input, output, key, key_length); // XOR encryption is symmetric
}

// Print the encrypted data in hex format
void print_hex(const char *data, size_t length) {
    for (size_t i = 0; i < length; ++i) {
        printf("%02x", (unsigned char)data[i]);
    }
    printf("\n");
}

int main() {
    const char *input = "THIS IS THE BEST ENCRYPTION";
    unsigned char key[] = "1234567890abcdef";
    size_t key_length = strlen((char *)key);
    size_t input_length = strlen(input);
    char encrypted[input_length + 1];
    char decrypted[input_length + 1];
    
    memset(encrypted, 0, sizeof(encrypted));
    memset(decrypted, 0, sizeof(decrypted));

    encrypt(input, encrypted, key, key_length);
    decrypt(encrypted, decrypted, key, key_length);

    printf("Original: %s\n", input);
    printf("Encrypted (hex): ");
    print_hex(encrypted, input_length);
    printf("Decrypted: %s\n", decrypted);

    return 0;
}
