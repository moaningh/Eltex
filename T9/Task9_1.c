#include <stdio.h>
#include <string.h>

int main() {
    FILE *file;
    char filename[] = "output.txt";
    char write_str[] = "String from file";
    char ch;

    file = fopen(filename, "w");
    fprintf(file, "%s", write_str);
    fclose(file);
    
    printf("Строка записана в файл '%s'\n", filename);

    file = fopen(filename, "r");
    fseek(file, 0, SEEK_END);
    
    long file_size = ftell(file);
    
    printf("Содержимое файла, прочитанное с конца: ");
    
    for (long i = file_size - 1; i >= 0; i--) {
        fseek(file, i, SEEK_SET);
        ch = fgetc(file);
        printf("%c", ch);
    }
    
    printf("\n");
    fclose(file);
    
    return 0;
}