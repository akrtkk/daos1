#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>

#define MENU_ITEMS_COUNT 3

void clear_screen() {
    printf("\033[H\033[J"); // ANSI escape sequence for clearing the screen
}

void set_text_color(int text_color, int background_color) {
    printf("\033[%d;%dm", text_color, background_color); // ANSI escape sequence for setting text and background color
}

void reset_text_color() {
    printf("\033[0m"); // ANSI escape sequence for resetting text color
}

int getch() {
    struct termios oldattr, newattr;
    int ch;

    tcgetattr(STDIN_FILENO, &oldattr);
    newattr = oldattr;
    newattr.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newattr);

    ch = getchar();

    tcsetattr(STDIN_FILENO, TCSANOW, &oldattr);

    return ch;
}

void run_program(int option) {
    switch (option) {
        case 0:
            printf("Running Program 1...\n");
            system("gcc lenti.c -o program1 && ./program1");
            break;
        case 1:
            printf("Running Program 2...\n");
            system("gcc calc.c -o program2 && ./program2");
            break;
        case 2:
            printf("Running Program 3...\n");
            system("gcc lenman.c -o program3 && ./program3");
            break;
        case 3:
            printf("Exited Succesfully, See you next time!\n");
            break;
        default:
            printf("Invalid option.\n");
            break;
    }
}

int main() {
    char* menu_items[MENU_ITEMS_COUNT] = {
        "Lenti Terminal",
        "Calenluctor",
        "LenMan",
        "Exit and Close"
    };

    int highlight = 0;
    int choice = -1;
    int key;

    while (choice == -1) {
        clear_screen(); // Clear the screen
        printf("Chose an operating system :- \n");
        printf("Use the arrow keys to highlight your choice, then press ENTER.)");
        printf("\n\n"); // Extra newline for spacing

        // Display the menu options
        for (int i = 0; i < MENU_ITEMS_COUNT; i++) {
            if (i == highlight) {
                set_text_color(30, 47); // Set text color to black and background color to white
                printf("           %s   \n", menu_items[i]);
            } else {
                reset_text_color(); // Reset text color
                printf("           %s   \n", menu_items[i]);
            }
            reset_text_color(); // Reset text color
        }

        printf("\n"); // Extra newline for spacing

        key = getch(); // Get user input

        switch (key) {
            case 'w': // Move up
            case 'k': // Vim-style up key
            case 65:  // Up arrow key
                highlight--;
                if (highlight < 0) {
                    highlight = 0;
                }
                break;
            case 's': // Move down
            case 'j': // Vim-style down key
            case 66:  // Down arrow key
                highlight++;
                if (highlight >= MENU_ITEMS_COUNT) {
                    highlight = MENU_ITEMS_COUNT - 1;
                }
                break;
            case '\n': // Enter key
                choice = highlight;
                break;
        }
    }

    clear_screen(); // Clear the screen
    run_program(choice);

    return 0;
}

