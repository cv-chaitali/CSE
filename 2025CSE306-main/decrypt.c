#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/rsa.h>
#include <openssl/pem.h>
#include <openssl/err.h>

#define MAX_RESULT_LEN 4096
#define MAX_ENCRYPTED_RESULT_LEN 4096

int main() {
    RSA *rsa_key;
    FILE *rsa_file;
    FILE *encrypted_file = fopen("encrypted_result.txt", "r");

    char result[MAX_RESULT_LEN];
    char encrypted_result[MAX_ENCRYPTED_RESULT_LEN];
    char decrypted_result[MAX_RESULT_LEN];
    int encrypted_len, decrypted_len;

    // Initialize the OpenSSL library
    OpenSSL_add_all_algorithms();
    ERR_load_crypto_strings();

    // Load the RSA private key from file
    rsa_file = fopen("privatekey.pem", "r");
    if (rsa_file == NULL) {
        printf("Failed to open RSA private key file\n");
        return 1;
    }
    rsa_key = PEM_read_RSAPrivateKey(rsa_file, NULL, NULL, NULL);
    if (rsa_key == NULL) {
        printf("Failed to read RSA private key from file\n");
        fclose(rsa_file);
        return 1;
    }
    fclose(rsa_file);

    // Read encrypted file
    if (encrypted_file == NULL) {
        printf("Failed to open encrypted result file\n");
        RSA_free(rsa_key);
        return 1;
    }

    if (fgets(encrypted_result, MAX_ENCRYPTED_RESULT_LEN, encrypted_file) == NULL) {
        printf("Failed to read encrypted result\n");
        fclose(encrypted_file);
        RSA_free(rsa_key);
        return 1;
    }

    fclose(encrypted_file);


/*
    // Read the encrypted result from stdin
    printf("Enter the encrypted result:\n");
    if (fgets(encrypted_result, MAX_ENCRYPTED_RESULT_LEN, stdin) == NULL) {
        printf("Failed to read encrypted result\n");
        RSA_free(rsa_key);
        return 1;
    }
*/

    // Decrypt the result using RSA decryption
    encrypted_len = strlen(encrypted_result) - 1; // Remove the newline character
    decrypted_len = RSA_private_decrypt(encrypted_len, (unsigned char *)encrypted_result, (unsigned char *)decrypted_result, rsa_key, RSA_PKCS1_PADDING);

    // Check for any OpenSSL errors
    if (ERR_peek_error() != 0) {
        printf("OpenSSL errors:\n");
        ERR_print_errors_fp(stdout);
    }

    if (decrypted_len == -1) {
        printf("Failed to decrypt result\n");
        RSA_free(rsa_key);
        return 1;
    }
    decrypted_result[decrypted_len] = '\0';

    // Cleanup the OpenSSL library
    ERR_free_strings();
    EVP_cleanup();

    // Free the RSA key
    RSA_free(rsa_key);

    // Print the decrypted result
    printf("Decrypted result: %s\n", decrypted_result);

    return 0;
}
