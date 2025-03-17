#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/utsname.h>
#include <openssl/rsa.h>
#include <openssl/pem.h>
#include <openssl/err.h>

#define MAX_IFACE_NAME_LEN 16
#define DEVICE_TREE_PATH "/proc/device-tree"
#define SERIAL_NUMBER_NODE "serial-number"
#define MAX_RSA_LENGTH 4096

int main() {
    int sockfd, fd, ret, encrypted_len;
    struct ifreq ifr;
    char line[256];
    char *serial_number_str;
    char iface_name[MAX_IFACE_NAME_LEN];
    unsigned char mac_addr[6];
    struct utsname uts;
    char result[1024];
    char encrypted_result[MAX_RSA_LENGTH];
    RSA *rsa_key = NULL;
    FILE *rsa_file = NULL;
    FILE *encrypted_file = fopen("encrypted_result.txt", "w");

    // Open a socket
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        printf("Failed to open socket\n");
        return 1;
    }

    // Get the name of the first network interface
    strncpy(iface_name, "eth0", MAX_IFACE_NAME_LEN);

    // Get the MAC address of the network interface
    strncpy(ifr.ifr_name, iface_name, IFNAMSIZ - 1);
    if (ioctl(sockfd, SIOCGIFHWADDR, &ifr) < 0) {
        printf("Failed to get MAC address\n");
        return 1;
    }
    memcpy(mac_addr, ifr.ifr_hwaddr.sa_data, 6);

    // Close the socket
    close(sockfd);

    // Get the kernel version and build timestamp
    if (uname(&uts) < 0) {
        printf("Failed to get kernel information\n");
        return 1;
    }

    // Format the results as a single string
    snprintf(result, sizeof(result), "MAC address: %02x:%02x:%02x:%02x:%02x:%02x \nKernel version: %s %s\n", mac_addr[0], mac_addr[1], mac_addr[2], mac_addr[3], mac_addr[4], mac_addr[5], uts.release, uts.version);

    // Load the RSA key from file
    rsa_file = fopen("publickey.pem", "r");
    if (rsa_file == NULL) {
        printf("Failed to open RSA key file\n");
        return 1;
    }
    rsa_key = PEM_read_RSA_PUBKEY(rsa_file, NULL, NULL, NULL);
    if (rsa_key == NULL){
        printf("Failed to read RSA key from file\n");
        fclose(rsa_file);
        return 1;
    }
    fclose(rsa_file);



    // Encrypt the results using RSA encryption
    encrypted_len = RSA_public_encrypt(strlen(result), (unsigned char *)result, (unsigned char *)encrypted_result, rsa_key, RSA_PKCS1_PADDING);
    if (encrypted_len == -1) {
        printf("Failed to encrypt result\n");
        return 1;
    }

    if (encrypted_file == NULL) {
        printf("Failed to open encrypted result file\n");
        RSA_free(rsa_key);
        return 1;
    }
    fwrite(encrypted_result, 1, encrypted_len, encrypted_file);
    fclose(encrypted_file);

    // Free the RSA key
    RSA_free(rsa_key);

    printf("Encrypted result saved to encrypted_result.txt\n");

    // check version 
    char target_version[50];
    strcpy(target_version, "5.15.92CSE2025-v8+");

    if(strcmp(uts.release, target_version) == 0){
        printf("Pass!\n");
    }else{
        printf("Fail... You need to check again.\n");
    }


    return 0;
}
