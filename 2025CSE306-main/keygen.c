#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/rsa.h>
#include <openssl/pem.h>

#define KEY_LENGTH 2048
#define EXPONENT 65537

int main() {
    RSA *rsa_key = NULL;
    FILE *rsa_file = NULL;
    char publickey_file[] = "publickey.pem";
    char privatekey_file[] = "privatekey.pem";

    // Generate an RSA key pair
    rsa_key = RSA_new();
    BIGNUM *exponent = BN_new();
    BN_set_word(exponent, EXPONENT);
    if (!RSA_generate_key_ex(rsa_key, KEY_LENGTH, exponent, NULL)) {
        printf("Failed to generate RSA key pair\n");
        return 1;
    }

    // Save the public key to file
    rsa_file = fopen(publickey_file, "w");
    if (rsa_file == NULL) {
        printf("Failed to open public key file\n");
        return 1;
    }
    if (!PEM_write_RSA_PUBKEY(rsa_file, rsa_key)) {
        printf("Failed to write public key to file\n");
        return 1;
    }
    fclose(rsa_file);

    // Save the private key to file
    rsa_file = fopen(privatekey_file, "w");
    if (rsa_file == NULL) {
        printf("Failed to open private key file\n");
        return 1;
    }
    if (!PEM_write_RSAPrivateKey(rsa_file, rsa_key, NULL, NULL, 0, NULL, NULL)) {
        printf("Failed to write private key to file\n");
        return 1;
    }
    fclose(rsa_file);

    // Free the RSA key and exponent
    RSA_free(rsa_key);
    BN_free(exponent);

    printf("RSA key pair generated and saved to files: %s, %s\n", publickey_file, privatekey_file);

    return 0;
}