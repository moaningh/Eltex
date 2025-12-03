#include <stdio.h>

void task1() {
    int num;
    unsigned char *bytePtr;
    unsigned char newValue;

    printf("\nВведите целое положительное число: ");
    scanf("%d", &num);

    printf("Введите новое значение для третьего байта (0-255): ");
    scanf("%hhu", &newValue);

    bytePtr = (unsigned char *)&num;
    bytePtr[2] = newValue;

    printf("\nИзмененное число: %d\n\n", num);
}

void task2() {
    float x = 5.0;
    printf("x = %f, ", x);
    float y = 6.0;
    printf("y = %f\n", y);
    float *xp = &y; // Отредактированная строка

    float *yp = &y;
    printf("Результат: %f\n", *xp + *yp);
    
    printf("\n\n");
}

void task3() {
    int arr[10] = {1,2,3,4,5,6,7,8,9,10};
    int *prt = arr;

    printf("Элементы массива:\n");

    for(int i = 0; i < 10; i++) {
        printf("%d ", *(prt + i));
    }

    printf("\n\n");
}

// Функция поиска подстроки
const char* findSubstring(const char *str, const char *sub) {
    if (*sub == '\0') return str;

    for (int i = 0; str[i] != '\0'; i++) {
        int j = 0;
        while (sub[j] != '\0' && str[i + j] == sub[j]) {
            j++;
        }
        if (sub[j] == '\0') {
            return &str[i]; 
        }
    }
    return NULL;
}

void task4() {
    char str[256];
    char sub[256];
    
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
    
    printf("\nВведите строку: ");
    fgets(str, sizeof(str), stdin);
    
    int len = 0;
    while (str[len] != '\0' && str[len] != '\n') len++;
    str[len] = '\0';
    
    printf("Введите подстроку: ");
    fgets(sub, sizeof(sub), stdin);
    
    len = 0;
    while (sub[len] != '\0' && sub[len] != '\n') len++;
    sub[len] = '\0';
    
    const char *result = findSubstring(str, sub);
    
    if (result != NULL) {
        printf("\nПодстрока найдена на позиции: %ld\n", result - str);
        printf("Остаток строки: %s\n\n", result);
    } else {
        printf("\nПодстрока не найдена.\n\n");
    }
}

int main() {
    int choice;
    
    do {
        printf("Выберите задание:\n");
        printf("1 - Изменения значения третьего байта\n");
        printf("2 - Измененная часть уравнения\n");
        printf("3 - Вывод массива указателем\n");
        printf("4 - Поиск подстроки\n");
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