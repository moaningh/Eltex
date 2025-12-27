#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_ABONENTS 100
#define NAME_LEN 10
#define TEL_LEN 10

struct abonent {
    char name[NAME_LEN];
    char second_name[NAME_LEN];
    char tel[TEL_LEN];
};

struct abonent directory[MAX_ABONENTS];
int count = 0; // количество занятых записей

// Функции
void add_abonent();
void delete_abonent();
void search_by_name();
void show_all();
void print_menu();
void clear_input_buffer();

int main() {
    int choice;

    do {
        print_menu();
        printf("Введите пункт меню: ");
        scanf("%d", &choice);
        clear_input_buffer(); // очистка буфера ввода

        switch (choice) {
            case 1:
                add_abonent();
                break;
            case 2:
                delete_abonent();
                break;
            case 3:
                search_by_name();
                break;
            case 4:
                show_all();
                break;
            case 5:
                printf("Выход из программы.\n");
                break;
            default:
                printf("Неверный пункт меню. Попробуйте снова.\n");
        }
    } while (choice != 5);

    return 0;
}

void print_menu() {
    printf("1) Добавить абонента\n");
    printf("2) Удалить абонента\n");
    printf("3) Поиск абонентов по имени\n");
    printf("4) Вывод всех записей\n");
    printf("5) Выход\n");
}

void clear_input_buffer() {
    while (getchar() != '\n');
}

void add_abonent() {
    if (count >= MAX_ABONENTS) {
        printf("Справочник переполнен. Невозможно добавить нового абонента.\n");
        return;
    }

    struct abonent new_abonent;

    printf("Введите имя (макс. %d символов): ", NAME_LEN - 1);
    fgets(new_abonent.name, NAME_LEN, stdin);
    new_abonent.name[strcspn(new_abonent.name, "\n")] = 0;

    printf("Введите фамилию (макс. %d символов): ", NAME_LEN - 1);
    fgets(new_abonent.second_name, NAME_LEN, stdin);
    new_abonent.second_name[strcspn(new_abonent.second_name, "\n")] = 0;

    printf("Введите телефон (макс. %d символов): ", TEL_LEN - 1);
    fgets(new_abonent.tel, TEL_LEN, stdin);
    new_abonent.tel[strcspn(new_abonent.tel, "\n")] = 0;


    if (strlen(new_abonent.name) == 0 || strlen(new_abonent.second_name) == 0 || strlen(new_abonent.tel) == 0) {
        printf("Все поля должны быть заполнены. Абонент не добавлен.\n");
        return;
    }

    directory[count] = new_abonent;
    count++;
    printf("Абонент добавлен успешно.\n");
}

void delete_abonent() {
    int index;
    printf("Введите номер записи для удаления (от 1 до %d): ", count);
    scanf("%d", &index);
    clear_input_buffer();

    if (index < 1 || index > count) {
        printf("Неверный номер записи.\n");
        return;
    }

    index--;

    memset(&directory[index], 0, sizeof(struct abonent));

    for (int i = index; i < count - 1; i++) {
        directory[i] = directory[i + 1];
    }

    count--;
    printf("Абонент удален.\n");
}

void search_by_name() {
    char search_name[NAME_LEN];
    printf("Введите имя для поиска: ");
    fgets(search_name, NAME_LEN, stdin);
    search_name[strcspn(search_name, "\n\n")] = 0;

    int found = 0;
    for (int i = 0; i < count; i++) {
        if (strcmp(directory[i].name, search_name) == 0) {
            printf("%d: %s %s, тел.: %s\n",
                   i + 1,
                   directory[i].name,
                   directory[i].second_name,
                   directory[i].tel);
            found = 1;
        }
    }

    if (!found) {
        printf("Абоненты с именем '%s' не найдены.\n\n", search_name);
    }
}

void show_all() {
    if (count == 0) {
        printf("Справочник пуст.\n");
        return;
    }

    printf("\n=== Все абоненты ===\n");
    for (int i = 0; i < count; i++) {
        printf("%d: %s %s, тел.: %s\n",
               i + 1,
               directory[i].name,
               directory[i].second_name,
               directory[i].tel);
    }
}