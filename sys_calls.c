#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <dirent.h>

#define BUFFER_SIZE 1024

void listFiles() {
    DIR *d;
    struct dirent *dir;
    d = opendir(".");
    if (d) {
        printf("Available files:\n");
        while ((dir = readdir(d)) != NULL) {
            printf("%s\n", dir->d_name);
        }
        closedir(d);
    }
}

void writeFile(char *filename) {
    int file = open(filename, O_WRONLY | O_CREAT, 0644);
    if (file < 0) {
        perror("Error in opening file");
        return;
    }

    printf("Enter text to write in the file (end with newline):\n");
    char buffer[BUFFER_SIZE];
    fgets(buffer, BUFFER_SIZE, stdin);

    ssize_t bytesWritten = write(file, buffer, strlen(buffer));
    if (bytesWritten < 0) {
        perror("Error in writing to file");
    }
    close(file);
}

void readFile(char *filename) {
    int file = open(filename, O_RDONLY);
    if (file < 0) {
        perror("Error in opening file");
        return;
    }

    char buffer[BUFFER_SIZE];
    ssize_t bytesRead = read(file, buffer, BUFFER_SIZE);
    if (bytesRead < 0) {
        perror("Error in reading file");
    } else {
        printf("Data read from file:\n%s\n", buffer);
    }
    close(file);
}

void deleteFile(char *filename) {
    if (remove(filename) < 0) {
        perror("Error in deleting file");
    } else {
        printf("File successfully deleted.\n");
    }
}

int main() {
    int choice;
    char filename[256];

    while (1) {
        printf("\nFile Management System\n");
        printf("1. List files\n");
        printf("2. Read a file\n");
        printf("3. Write to a file\n");
        printf("4. Delete a file\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // to consume the newline character

        switch (choice) {
            case 1:
                listFiles();
                break;
            case 2:
                printf("Enter filename to read: ");
                scanf("%s", filename);
                readFile(filename);
                break;
            case 3:
                printf("Enter filename to write to: ");
                scanf("%s", filename);
                writeFile(filename);
                break;
            case 4:
                printf("Enter filename to delete: ");
                scanf("%s", filename);
                deleteFile(filename);
                break;
            case 5:
                printf("Exiting...\n");
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}