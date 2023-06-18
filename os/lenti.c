#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_COMMAND_LENGTH 100

void printly(char** tokens, int numTokens) {
    if (numTokens <= 3) {
        printf("%s %s\n", tokens[1], tokens[2]);
    } else {
        if (numTokens == 2) {
            printf("%s\n", tokens[1]);
        } else {
            int disk = numTokens - 1;
            printf("Can only display 1-2 words amount of words given: %d\n", disk);
        }
    }
}

void helply() {
    printf("Available commands:\n");
    printf("print - Prints the given words\n");
    printf("help - Displays available commands\n");
    printf("add - Adds two numbers and prints the result\n");
    printf("read - Reads the content of a file and prints it\n");
    printf("write - Writes content to a file\n");
    printf("append - Appends content to a file\n");
    printf("copy - Copies a file\n");
    printf("rename - Renames a file\n");
    printf("delete - Deletes a file\n");
}

void addly(char** tokens, int numTokens) {
    if (numTokens != 3) {
        printf("Invalid number of arguments\n");
        return;
    }
    int num1 = atoi(tokens[1]);
    int num2 = atoi(tokens[2]);
    printf("%d\n", num1 + num2);
}

void readly(char** tokens, int numTokens) {
    if (numTokens != 2) {
        printf("Invalid number of arguments\n");
        return;
    }
    FILE* file = fopen(tokens[1], "r");
    if (file == NULL) {
        printf("File %s not found\n", tokens[1]);
        return;
    }
    char* line = NULL;
    size_t len = 0;
    ssize_t read;
    while ((read = getline(&line, &len, file)) != -1) {
        printf("%s", line);
    }
    fclose(file);
    if (line)
        free(line);
}

void writely(char** tokens, int numTokens) {
    if (numTokens < 3) {
        printf("Invalid number of arguments\n");
        return;
    }
    FILE* file = fopen(tokens[1], "w");
    if (file == NULL) {
        printf("File %s not found\n", tokens[1]);
        return;
    }
    char* content = malloc(MAX_COMMAND_LENGTH * sizeof(char));
    strcpy(content, tokens[2]);
    for (int i = 3; i < numTokens; i++) {
        strcat(content, " ");
        strcat(content, tokens[i]);
    }
    fprintf(file, "%s", content);
    fclose(file);
    free(content);
    printf("Content written to %s\n", tokens[1]);
}

void appendly(char** tokens, int numTokens) {
    if (numTokens < 3) {
        printf("Invalid number of arguments\n");
        return;
    }
    FILE* file = fopen(tokens[1], "a");
    if (file == NULL) {
        printf("File %s not found\n", tokens[1]);
        return;
    }
    char* content = malloc(MAX_COMMAND_LENGTH * sizeof(char));
    strcpy(content, tokens[2]);
    for (int i = 3; i < numTokens; i++) {
        strcat(content, " ");
        strcat(content, tokens[i]);
    }
    fprintf(file, "%s", content);
    fclose(file);
    free(content);
    printf("Content appended to %s\n", tokens[1]);
}

void copyly(char** tokens, int numTokens) {
    if (numTokens != 3) {
        printf("Invalid number of arguments\n");
        return;
    }
    FILE* srcFile = fopen(tokens[1], "r");
    if (srcFile == NULL) {
        printf("File %s not found\n", tokens[1]);
        return;
    }
    FILE* destFile = fopen(tokens[2], "w");
    if (destFile == NULL) {
        printf("File %s not found\n", tokens[2]);
        fclose(srcFile);
        return;
    }
    char* line = NULL;
    size_t len = 0;
    ssize_t read;
    while ((read = getline(&line, &len, srcFile)) != -1) {
        fprintf(destFile, "%s", line);
    }
    fclose(srcFile);
    fclose(destFile);
    if (line)
        free(line);
    printf("File %s copied to %s\n", tokens[1], tokens[2]);
}

void renamely(char** tokens, int numTokens) {
    if (numTokens != 3) {
        printf("Invalid number of arguments\n");
        return;
    }
    if (rename(tokens[1], tokens[2]) == 0) {
        printf("File %s renamed to %s\n", tokens[1], tokens[2]);
    } else {
        printf("File %s not found\n", tokens[1]);
    }
}

void deletely(char** tokens, int numTokens) {
    if (numTokens != 2) {
        printf("Invalid number of arguments\n");
        return;
    }
    if (remove(tokens[1]) == 0) {
        printf("File %s deleted\n", tokens[1]);
    } else {
        printf("File %s not found\n", tokens[1]);
    }
}

int main() {
    char code[MAX_COMMAND_LENGTH];
    printf("Lenti Terminal\n");
    while (1) {
        printf(">> ");
        fgets(code, MAX_COMMAND_LENGTH, stdin);
        code[strcspn(code, "\n")] = 0;  // Remove the newline character
        printf("\n");

        char* token = strtok(code, " ");
        char* tokens[MAX_COMMAND_LENGTH];
        int numTokens = 0;
        while (token != NULL) {
            tokens[numTokens] = token;
            numTokens++;
            token = strtok(NULL, " ");
        }

        if (strcmp(tokens[0], "print") == 0) {
            printly(tokens, numTokens);
        } else if (strcmp(tokens[0], "help") == 0) {
            helply();
        } else if (strcmp(tokens[0], "add") == 0) {
            addly(tokens, numTokens);
        } else if (strcmp(tokens[0], "read") == 0) {
            readly(tokens, numTokens);
        } else if (strcmp(tokens[0], "write") == 0) {
            writely(tokens, numTokens);
        } else if (strcmp(tokens[0], "append") == 0) {
            appendly(tokens, numTokens);
        } else if (strcmp(tokens[0], "copy") == 0) {
            copyly(tokens, numTokens);
        } else if (strcmp(tokens[0], "rename") == 0) {
            renamely(tokens, numTokens);
        } else if (strcmp(tokens[0], "delete") == 0) {
            deletely(tokens, numTokens);
        } else {
            printf("Invalid keyword: %s\n", tokens[0]);
        }

        printf("\n");
    }

    return 0;
}
