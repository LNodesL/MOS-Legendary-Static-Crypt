#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <mach-o/loader.h>
#include <mach-o/fat.h>
#include <mach/mach.h>
#include <mach/vm_map.h>
#include "software.h"

// Simple XOR decryption function
int decrypt_data(const unsigned char* encrypted_data, size_t encrypted_size, 
                 const char* password, unsigned char** decrypted_data, size_t* decrypted_size) {
    
    // For simplicity, we'll use a basic XOR with the password
    // In a real implementation, you'd want proper encryption
    
    // Allocate buffer for decrypted data
    *decrypted_data = malloc(encrypted_size);
    if (!*decrypted_data) {
        printf("Error: Memory allocation failed\n");
        return 0;
    }
    
    // Simple XOR decryption with password
    size_t password_len = strlen(password);
    for (size_t i = 0; i < encrypted_size; i++) {
        (*decrypted_data)[i] = encrypted_data[i] ^ password[i % password_len];
    }
    
    *decrypted_size = encrypted_size;
    return 1;
}

// Function to execute the embedded binary
int execute_embedded_binary() {
    printf("Runtime: Loading encrypted executable...\n");
    printf("Runtime: Encrypted size: %u bytes\n", software_size);
    
    // Decrypt the embedded data
    printf("Runtime: Decrypting embedded executable...\n");
    unsigned char* decrypted_data = NULL;
    size_t decrypted_size = 0;
    
    const char* password = "mos-legendary-crypt-2024";
    
    if (!decrypt_data(software_bytes, software_size, password, &decrypted_data, &decrypted_size)) {
        printf("Runtime: Decryption failed!\n");
        return 1;
    }
    
    printf("Runtime: Decryption successful, decrypted size: %zu bytes\n", decrypted_size);
    
    // Create a temporary file to write the decrypted binary data
    char temp_path[] = "/tmp/embedded_exec_XXXXXX";
    int temp_fd = mkstemp(temp_path);
    if (temp_fd == -1) {
        perror("Failed to create temporary file");
        free(decrypted_data);
        return 1;
    }
    
    // Write the decrypted binary data to the temporary file
    ssize_t written = write(temp_fd, decrypted_data, decrypted_size);
    if (written != (ssize_t)decrypted_size) {
        perror("Failed to write decrypted binary data");
        close(temp_fd);
        unlink(temp_path);
        free(decrypted_data);
        return 1;
    }
    
    // Make the file executable
    if (chmod(temp_path, 0755) == -1) {
        perror("Failed to make file executable");
        close(temp_fd);
        unlink(temp_path);
        free(decrypted_data);
        return 1;
    }
    
    close(temp_fd);
    
    // Clear decrypted data from memory for security
    memset(decrypted_data, 0, decrypted_size);
    free(decrypted_data);
    
    printf("Runtime: Executing decrypted binary...\n");
    printf("Runtime: Output from embedded executable:\n");
    printf("----------------------------------------\n");
    
    // Execute the temporary file
    int result = system(temp_path);
    
    printf("----------------------------------------\n");
    printf("Runtime: Embedded executable finished with exit code: %d\n", result);
    
    // Clean up the temporary file
    unlink(temp_path);
    
    return result;
}

int main() {
    printf("Runtime: Starting embedded executable runner...\n");
    
    int result = execute_embedded_binary();
    
    printf("Runtime: Finished with exit code: %d\n", result);
    return result;
}
