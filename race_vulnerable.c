#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

int main() {
    char *filename = "/tmp/racefile";
    
    printf("Checking file existence...\n");
    
    if (access(filename, F_OK) == -1) {
        printf("File not found, sleeping for 2 seconds...\n");
        sleep(2);
        
        printf("Creating file...\n");
        FILE *fp = fopen(filename, "w");
        if (fp) {
            fprintf(fp, "Secret data: password123\n");
            fclose(fp);
            printf("File created successfully!\n");
        } else {
            printf("Failed to create file!\n");
        }
    } else {
        printf("File already exists!\n");
    }
    
    return 0;
}
