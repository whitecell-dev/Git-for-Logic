CC = gcc
CFLAGS = -std=c11 -Wall -Wextra -Werror -pedantic -O2 -g -I. -D_POSIX_C_SOURCE=200809L
LDFLAGS = -lcrypto

SRC = git_for_logic.c
OBJ = $(SRC:.c=.o)
TARGET = git-for-logic

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.c git_for_logic.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)

test: $(TARGET)
	./$(TARGET) init
	@echo ""
	@echo "✅ Test passed!"

run-example: $(TARGET)
	./$(TARGET) execute loan.yaml test.json "First test"

.PHONY: all clean test run-example
