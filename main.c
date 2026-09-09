#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int get_hex_digits_count(int n) {
    char buffer[32];
    int digits = sprintf(buffer, "%X", n);
    return digits;
}

void clear_buffer(char buffer[], int size) {
    for (int i = 0; i < size; i++)
        buffer[i] = ' ';
}

void display_line(char buffer[], int size, int digits, int offset) {
    // offset:
    for (int i = 0; i < (8-get_hex_digits_count(offset)); i++)
        printf("0");
    printf("%x | ", offset);

    // Hex Format
    for (int i = 0; i < digits; i++) {
        if (get_hex_digits_count((int)buffer[i]) < 2) {
            printf("0");
            printf("%x ", buffer[i]);
        }
        else if (get_hex_digits_count((int)buffer[i]) > 2) {
            printf("?? ");
        }
        else {
            printf("%x ", buffer[i]);
        }
    }
    // Empty Bytes
    for (int i = 0; i < size - digits; i++) {
        printf("   ");
    }
    printf("| ");

    // ASCII Format
    for (int i = 0; i < size; i++) {
        if (buffer[i] < ' ' || buffer[i] > '~') buffer[i] = '.';
        printf("%c", buffer[i]);
    }
    printf(" |\n");
}

void display_hexdump(FILE *file, int buffer_size) {
    char buffer[buffer_size];
    char c;
    int position = 0;
    while ((c = fgetc(file)) != EOF) {
        buffer[position%buffer_size] = c;
        position++;
        if (position % buffer_size == 0) {
            display_line(buffer, buffer_size, buffer_size, position-buffer_size);
            clear_buffer(buffer, buffer_size);
        }
    }
    display_line(buffer, buffer_size, buffer_size - (position%buffer_size), position-buffer_size);
}

int main()
{
    char path[1024];
    printf("PATH: ");
    fgets(path, 1024, stdin);
    path[strlen(path)-1] = '\0';
    FILE *file = fopen(path, "r");
    while (file == NULL) {
        printf("Can't Find file '%s' Try again: ", path);
        fgets(path, 1024, stdin);
        path[strlen(path)-1] = '\0';
        printf("'%s'\n", path);
        file = fopen(path, "r");
    }

    int digits_count = 0;
    do {
        printf("Enter Digits Count: ");
        scanf("%d", &digits_count);
    } while (digits_count < 1);

    printf("\n");
    display_hexdump(file, digits_count);
    fclose(file);
    return 0;
}

// Boualleg Kaissar
