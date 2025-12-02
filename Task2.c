#include <stdio.h>

void task1() {
    int n, count = 1;

    printf("\nВведите размер матрицы: ");
    scanf("%d", &n);

    printf("Квадратная матрица:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%3d ", count++);
        }
        printf("\n");
    }

    printf("\n\n");
}

void task2() {
    int n;

    printf("\nВведите размер массива: ");
    scanf("%d", &n);

    int arr[n];

    printf("Заполните массив целыми числами:\n");

    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    printf("\nОбратный массив:\n");

    for (int i = n - 1; i >= 0; i--) {
        printf("%d ", arr[i]);
    }
    
    
    printf("\n\n");
}

void task3() {
    int n;

    printf("\nВведите размер матрицы: ");
    scanf("%d", &n);

    int matrix[n][n];

    printf("Матрица с треугольниками:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i + j >= n - 1) {
                matrix[i][j] = 1;
            } 
            else {
                matrix[i][j] = 0;
            }
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }

    printf("\n\n");

}

void task4() {
    int n;

    printf("\nВведите размер матрицы: ");
    scanf("%d", &n);

    int matrix[n][n];
    int value = 1;
    int up = 0, down = n - 1, left = 0, right = n - 1;
    
    printf("Вывод матрицы улиткой:\n");

    while (value <= n * n) {
        for (int i = left; i <= right && value <= n * n; i++) {
            matrix[up][i] = value++;
        }
        up++;
        
        for (int i = up; i <= down && value <= n * n; i++) {
            matrix[i][right] = value++;
        }
        right--;
        
        for (int i = right; i >= left && value <= n * n; i--) {
            matrix[down][i] = value++;
        }
        down--;
        
        for (int i = down; i >= up && value <= n * n; i--) {
            matrix[i][left] = value++;
        }
        left++;
    }
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%3d ", matrix[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

int main() {
    int choice, n;
    
    do {
        printf("Выберите задание:\n");
        printf("1 - Квадратная матрица\n");
        printf("2 - Массив в обратном порядке\n");
        printf("3 - Верхний и нижний треугольники\n");
        printf("4 - Матрица-улитка\n");
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