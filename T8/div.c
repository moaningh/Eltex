#include "calc.h"
#include <stdio.h>

float div(int a, int b) {
    if (b == 0) {
        printf("Ошибка: деление на ноль!\n");
        return 0;
    }
    return (float) a / b;
}