#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_COMMAND_LENGTH 512

void clear_screen() {
    printf("\033[H\033[J");
}

void compile_file(char *filename, char *flags) {
    char command[MAX_COMMAND_LENGTH];
    snprintf(command, sizeof(command), "gcc %s %s -o output", filename, flags);
    int result = system(command);
    if (result == 0) {
        printf("Compilation successful!\n");
    } else {
        printf("Compilation failed!\n");
    }
}

void display_output() {
    printf("Output:\n");
    system("./output");
}

void show_menu() {
    printf("GCC Frontend Menu:\n");
    printf("1. Compile a file\n");
    printf("2. Display output\n");
    printf("3. Set compiler flags\n");
    printf("4. Exit\n");
    printf("Enter your choice: ");
}

int main() {
    int choice;
    char filename[256];
    char flags[256] = "";
    int running = 1;

    while (running) {
        clear_screen();
        show_menu();
        scanf("%d", &choice);
        getchar(); // Clear newline character from buffer

        switch (choice) {
            case 1:
                printf("Enter the filename to compile: ");
                fgets(filename, sizeof(filename), stdin);
                filename[strcspn(filename, "\n")] = 0; // Remove newline character
                compile_file(filename, flags);
                getchar(); // Wait for user to press enter
                break;
            case 2:
                display_output();
                getchar(); // Wait for user to press enter
                break;
            case 3:
                printf("Enter the compiler flags: ");
                fgets(flags, sizeof(flags), stdin);
                flags[strcspn(flags, "\n")] = 0; // Remove newline character
                break;
            case 4:
                running = 0;
                break;
            default:
                printf("Invalid choice, please try again.\n");
                getchar(); // Wait for user to press enter
                break;
        }
    }

    return 0;
}
