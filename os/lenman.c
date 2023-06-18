#include <stdio.h>

void list_files(const char* path) {
    FILE* pipe;
    char command[100];

    sprintf(command, "ls %s", path);
    pipe = popen(command, "r");
    if (pipe == NULL) {
        printf("Error executing command.\n");
        return;
    }

    printf("Files in %s:\n", path);

    char line[256];
    while (fgets(line, sizeof(line), pipe) != NULL) {
        printf("%s", line);
    }

    pclose(pipe);
}

void create_file(const char* path) {
    FILE* file = fopen(path, "w");
    if (file == NULL) {
        printf("Error creating file.\n");
        return;
    }

    fclose(file);
}

void rename_file(const char* old_path, const char* new_path) {
    if (rename(old_path, new_path) != 0) {
        printf("Error renaming file.\n");
        return;
    }
}

void delete_file(const char* path) {
    if (remove(path) != 0) {
        printf("Error deleting file.\n");
        return;
    }
}

int main() {
    char path[256];
    int choice;

    printf("Welcome to the Lenti File Manager!\n");

    while (1) {
        printf("\nMenu:\n");
        printf("1. List files\n");
        printf("2. Create a file\n");
        printf("3. Rename a file\n");
        printf("4. Delete a file\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter the path: ");
                scanf("%s", path);
                list_files(path);
                break;
            case 2:
                printf("Enter the path and name of the file to create: ");
                scanf("%s", path);
                create_file(path);
                break;
            case 3:
                printf("Enter the current path and name of the file: ");
                scanf("%s", path);
                printf("Enter the new path and name of the file: ");
                char new_path[256];
                scanf("%s", new_path);
                rename_file(path, new_path);
                break;
            case 4:
                printf("Enter the path and name of the file to delete: ");
                scanf("%s", path);
                delete_file(path);
                break;
            case 5:
                printf("Exiting...\n");
                return 0;
            default:
                printf("Invalid choice. Please try again.\n");
                break;
        }
    }
}

