CC = gcc
CFLAGS = -Wall -Werror -Wextra -pthread
TARGET = store
OBJS = main.o stall.o customer.o loader.o logger.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

main.o: main.c stall.h customer.h loader.h
	$(CC) $(CFLAGS) -c main.c

stall.o: stall.c stall.h
	$(CC) $(CFLAGS) -c stall.c

customer.o: customer.c customer.h stall.h logger.h
	$(CC) $(CFLAGS) -c customer.c

loader.o: loader.c loader.h stall.h logger.h
	$(CC) $(CFLAGS) -c loader.c

logger.o: logger.c logger.h
	$(CC) $(CFLAGS) -c logger.c

clean:
	rm -f $(OBJS) $(TARGET)

run: $(TARGET)
	./$(TARGET)