CC = gcc
CFLAGS = -std=c17 -Wall -Wextra -Werror -g

TARGET = x9sh
SRCS = main.c $(wildcard builtin/*.c)
OBJS = $(SRCS:.c=.o)

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)
