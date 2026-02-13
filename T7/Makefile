# Имя исполняемого файла
TARGET = calculator

# Компилятор и флаги
CC = gcc
CFLAGS = -Wall -Werror -Wextra -std=c99

# Файлы исходного кода
LIB_SRCS = add.c sub.c mul.c div.c
LIB_OBJS = $(LIB_SRCS:.c=.o)
LIB_NAME = libcalc.a

# Сборка всего проекта
all: $(TARGET)

# Сборка исполняемого файла
$(TARGET): main.c $(LIB_NAME)
	$(CC) $(CFLAGS) main.c -L. -lcalc -o $(TARGET)

# Сборка статической библиотеки
$(LIB_NAME): $(LIB_OBJS)
	ar rcs $@ $^

# Правило для компиляции .c в .o
%.o: %.c calc.h
	$(CC) $(CFLAGS) -c $< -o $@

# Очистка
clean:
	rm -f $(LIB_OBJS) $(LIB_NAME) $(TARGET)

# Псевдоцели
.PHONY: all clean