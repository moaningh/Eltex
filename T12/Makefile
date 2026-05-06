CC = gcc
CFLAGS = -Wall -Werror -Wextra -g

DIR1 = Part1
DIR2 = Part2
DIR3 = Part3

TASK1 = T12_1
TASK2_SERVER = T12_2_server
TASK2_CLIENT = T12_2_client
TASK3 = shell

TASK3_SRC = Part3/main.c Part3/parser.c Part3/executor.c Part3/builtin.c
TASK3_OBJ = $(TASK3_SRC:.c=.o)

all: task1 task2 task3

task1: $(DIR1)/$(TASK1)

$(DIR1)/$(TASK1): $(DIR1)/task12_1.c
	$(CC) $(CFLAGS) -o $@ $<

task2: $(DIR2)/$(TASK2_SERVER) $(DIR2)/$(TASK2_CLIENT)

$(DIR2)/$(TASK2_SERVER): $(DIR2)/server.c
	$(CC) $(CFLAGS) -o $@ $<

$(DIR2)/$(TASK2_CLIENT): $(DIR2)/client.c
	$(CC) $(CFLAGS) -o $@ $<

task3: $(DIR3)/$(TASK3)

$(DIR3)/$(TASK3): $(TASK3_OBJ)
	$(CC) $(CFLAGS) -o $@ $^

$(DIR3)/%.o: $(DIR3)/%.c $(DIR3)/shell.h
	$(CC) $(CFLAGS) -c $< -o $@

run1: task1
	./$(DIR1)/$(TASK1)

run2: task2
	./$(DIR2)/$(TASK2_SERVER) &
	@sleep 1
	./$(DIR2)/$(TASK2_CLIENT)

run3: task3
	./$(DIR3)/$(TASK3)

clean:
	rm -f $(DIR1)/$(TASK1)
	rm -f $(DIR2)/$(TASK2_SERVER) $(DIR2)/$(TASK2_CLIENT)
	rm -f $(DIR3)/$(TASK3)
	rm -f $(TASK3_OBJ)
	rm -f $(DIR2)/my_fifo

.PHONY: all task1 task2 task3 run1 run2 run3 clean