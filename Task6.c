#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define NAME_LEN 10
#define TEL_LEN 10

struct abonent {
    char name[NAME_LEN];
    char second_name[NAME_LEN];
    char tel[TEL_LEN];
    struct abonent* next;
    struct abonent* prev;
};

struct abonent* head = NULL;
struct abonent* tail = NULL;
int count = 0;

void add_abonent();
void delete_abonent();
void search_by_name();
void show_all();
void print_menu();
void clear_input_buffer();
void free_list();

int main() {
    int choice;

    do {
        print_menu();
        printf("Введите пункт меню: ");
        scanf("%d", &choice);
        clear_input_buffer();

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

    free_list();

    return 0;
}

void print_menu() {
    printf("\n=== Меню ===\n");
    printf("1) Добавить абонента\n");
    printf("2) Удалить абонента\n");
    printf("3) Поиск абонентов по имени\n");
    printf("4) Вывод всех записей\n");
    printf("5) Выход\n\n");
}

void clear_input_buffer() {
    while (getchar() != '\n');
}

void add_abonent() {
    struct abonent* new_abonent = (struct abonent*)malloc(sizeof(struct abonent));
    if (new_abonent == NULL) {
        printf("Ошибка выделения памяти!\n");
        return;
    }

    printf("Введите имя (макс. %d символов): ", NAME_LEN - 1);
    fgets(new_abonent->name, NAME_LEN, stdin);
    new_abonent->name[strcspn(new_abonent->name, "\n")] = 0;

    printf("Введите фамилию (макс. %d символов): ", NAME_LEN - 1);
    fgets(new_abonent->second_name, NAME_LEN, stdin);
    new_abonent->second_name[strcspn(new_abonent->second_name, "\n")] = 0;

    printf("Введите телефон (макс. %d символов): ", TEL_LEN - 1);
    fgets(new_abonent->tel, TEL_LEN, stdin);
    new_abonent->tel[strcspn(new_abonent->tel, "\n")] = 0;

    if (strlen(new_abonent->name) == 0 || 
        strlen(new_abonent->second_name) == 0 || 
        strlen(new_abonent->tel) == 0) {
        printf("Все поля должны быть заполнены. Абонент не добавлен.\n");
        free(new_abonent);
        return;
    }

    new_abonent->next = NULL;
    new_abonent->prev = NULL;

    if (head == NULL) {
        head = new_abonent;
        tail = new_abonent;
    } else {
        tail->next = new_abonent;
        new_abonent->prev = tail;
        tail = new_abonent;
    }

    count++;
    printf("Абонент добавлен успешно. Всего абонентов: %d\n", count);
}

void delete_abonent() {
    if (count == 0) {
        printf("Справочник пуст. Удалять нечего.\n");
        return;
    }

    int index;
    printf("Введите номер записи для удаления (от 1 до %d): ", count);
    scanf("%d", &index);
    clear_input_buffer();

    if (index < 1 || index > count) {
        printf("Неверный номер записи.\n");
        return;
    }

    struct abonent* current = head;
    int current_index = 1;

    while (current != NULL && current_index < index) {
        current = current->next;
        current_index++;
    }

    if (current == NULL) {
        printf("Абонент не найден.\n");
        return;
    }

    if (current->prev != NULL) {
        current->prev->next = current->next;
    } else {
        head = current->next;
    }

    if (current->next != NULL) {
        current->next->prev = current->prev;
    } else {
        tail = current->prev;
    }

    free(current);
    count--;
    printf("Абонент удален. Осталось абонентов: %d\n", count);
}

void search_by_name() {
    if (count == 0) {
        printf("Справочник пуст.\n");
        return;
    }

    char search_name[NAME_LEN];
    printf("Введите имя для поиска: ");
    fgets(search_name, NAME_LEN, stdin);
    search_name[strcspn(search_name, "\n")] = 0;

    struct abonent* current = head;
    int found = 0;
    int index = 1;

    printf("\nРезультаты поиска:\n");
    while (current != NULL) {
        if (strcmp(current->name, search_name) == 0) {
            printf("%d: %s %s, тел.: %s\n",
                   index,
                   current->name,
                   current->second_name,
                   current->tel);
            found = 1;
        }
        current = current->next;
        index++;
    }

    if (!found) {
        printf("Абоненты с именем '%s' не найдены.\n", search_name);
    }
}

void show_all() {
    if (count == 0) {
        printf("Справочник пуст.\n");
        return;
    }

    struct abonent* current = head;
    int index = 1;

    printf("\nВсе абоненты (%d):\n", count);
    while (current != NULL) {
        printf("%d: %s %s, тел.: %s\n",
               index,
               current->name,
               current->second_name,
               current->tel);
        current = current->next;
        index++;
    }
}

void free_list() {
    struct abonent* current = head;
    struct abonent* next_node;
    
    while (current != NULL) {
        next_node = current->next;
        free(current);
        current = next_node;
    }

    head = NULL;
    tail = NULL;
    count = 0;

    printf("Память освобождена.\n");
}