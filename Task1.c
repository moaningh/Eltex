#include <stdio.h>

void task1() {
    unsigned int num;

    printf("\nВведите положительное целое число: ");
    scanf("%u", &num);

    const int bits = sizeof(int) * 8;

    printf("Двоичное представление: ");

    for (int i = bits - 1; i >= 0; i--) {
        int bit = (num >> i) & 1;
        printf("%d", bit);

        if (i % 8 == 0 && i != 0) {
            printf(" ");
        }
    }

    printf("\n\n");
}

void task2() {
    int num;

    printf("\nВведите отрицательное целое число: ");
    scanf("%d", &num);

    if (num >= 0) {
        printf("Ошибка: введено не отрицательное число!\n\n");
        return;
    }

    const int bits = sizeof(int) * 8;

    printf("Двоичное представление: ");

    for (int i = bits - 1; i >= 0; i--) {
        int bit = (num >> i) & 1;
        printf("%d", bit);
        
        if (i % 8 == 0 && i != 0) {
            printf(" ");
        }
    }

    printf("\n\n");
}

void task3() {
    unsigned int num;

    printf("\nВведите положительное целое число: ");
    scanf("%u", &num);
    
    int count = 0;
    unsigned int temp = num;
    
    while (temp != 0) {
        count += temp & 1;  
        temp >>= 1;         
    }
    
    printf("Количество единиц в двоичном представлении: %d\n\n", count);
}

void task4() {
    unsigned int num;
    unsigned char new_byte;

    printf("\nВведите положительное целое число: ");
    scanf("%u", &num);
    printf("Введите новое значение для третьего байта (0-255): ");
    scanf("%hhu", &new_byte);

    printf("\nИсходное число: %u\n", num);
    printf("Исходное двоичное представление: ");

    const int bits = sizeof(int) * 8;
    for (int i = bits - 1; i >= 0; i--) {
        printf("%d", (num >> i) & 1);
        if (i % 8 == 0 && i != 0) printf(" ");
    }
    printf("\n");

    unsigned int mask = 0xFF00FFFF;
    unsigned int result = num & mask;

    result = result | (new_byte << 16);
    
    printf("Новое число: %u\n", result);
    printf("Новое двоичное представление: ");
    for (int i = bits - 1; i >= 0; i--) {
        printf("%d", (result >> i) & 1);
        if (i % 8 == 0 && i != 0) printf(" ");
    }
    printf("\n");
    
    printf("Байты (от младшего к старшему):\n");
    printf("Байт 1 (0-7 биты): %u\n", (result >> 0) & 0xFF);
    printf("Байт 2 (8-15 биты): %u\n", (result >> 8) & 0xFF);
    printf("Байт 3 (16-23 биты): %u <-- изменен\n", (result >> 16) & 0xFF);
    printf("Байт 4 (24-31 биты): %u\n\n", (result >> 24) & 0xFF);
}

int main() {
    int choice;
    
    do {
        printf("Выберите задание:\n");
        printf("1 - Двоичное представление положительного числа\n");
        printf("2 - Двоичное представление отрицательного числа\n");
        printf("3 - Количество единиц в двоичном представлении\n");
        printf("4 - Замена третьего байта\n");
        printf("0 - Выход\n");
        printf("Ваш выбор: ");
        scanf("%d", &choice);
        
        switch(choice) {
            case 1:
                task1();
                break;
            case 2:
                task2();
                break;
            case 3:
                task3();
                break;
            case 4:
                task4();
                break;
            case 0:
                printf("\nВыход из программы.\n");
                break;
            default:
                printf("\nНеверный выбор! Попробуйте снова.\n\n");
        }
    } while (choice != 0);
    
    return 0;
}