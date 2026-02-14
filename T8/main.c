#include "calc.h"
#include <stdio.h>

void input_two_numbers(int *a, int *b) {
    printf("Введите два числа: ");
    while (scanf("%d %d", a, b) != 2) {
        while (getchar() != '\n');
        printf("Ошибка! Введите два целых числа: ");
    }
}

int main() {
    int a, b, choice;
    
    do {
        printf("Выберите действие:\n");
        printf("1 - Сложение\n");
        printf("2 - Вычитание\n");
        printf("3 - Умножение\n");
        printf("4 - Деление\n");
        printf("5 - Выход\n");
        printf("Ваш выбор:");

        if (scanf("%d", &choice) != 1) {
            while (getchar() != '\n');
            printf("Ошибка! Введите число.\n");
            continue;
        }
        
        switch(choice) {
            case 1:
                input_two_numbers(&a, &b);
                printf("Результат: %d\n\n", add(a, b));
                break;
            case 2:
                input_two_numbers(&a, &b);
                printf("Результат: %d\n\n", sub(a, b));
                break;
            case 3:
                input_two_numbers(&a, &b);
                printf("Результат: %d\n\n", mul(a, b));
                break;
            case 4:
                input_two_numbers(&a, &b);
                printf("Результат: %f\n\n", div(a, b));
                break;
            case 5:
                printf("Выход из программы.\n");
                break;
            default:
                printf("\nНеверный выбор! Попробуйте снова.\n\n");
        }
    } while (choice != 5);
    
    return 0;
}