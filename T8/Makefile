# Имя исполняемого файла
TARGET = calculator

# Компилятор и флаги
CC = gcc
CFLAGS = -Wall -Werror -Wextra -std=c99 -fPIC

# Файлы исходного кода
LIB_SRCS = add.c sub.c mul.c div.c
LIB_OBJS = $(LIB_SRCS:.c=.o)
LIB_NAME = libcalc.so

# Сборка всего проекта
all: $(TARGET)

# Сборка исполняемого файла
$(TARGET): main.c $(LIB_NAME)
	$(CC) $(CFLAGS) main.c -L. -lcalc -Wl,-rpath=. -o $(TARGET)

# Сборка динамической библиотеки
$(LIB_NAME): $(LIB_OBJS)
	$(CC) -shared $^ -o $@

# Правило для компиляции .c в .o
%.o: %.c calc.h
	$(CC) $(CFLAGS) -c $< -o $@

# Очистка
clean:
	rm -f $(LIB_OBJS) $(LIB_NAME) $(TARGET)

# Псевдоцели
.PHONY: all clean