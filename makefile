CC = gcc
CFLAGS = -Wall -Wextra -g

SOURCES = main.c interface.c double.c complex.c vector.c vector_errors.c
TEST_SOURCES = test.c vector.c double.c complex.c vector_errors.c

TARGET = main
TEST_TARGET = test

all: $(TARGET) $(TEST_TARGET)

$(TARGET): $(SOURCES)
 $(CC) $(CFLAGS) $(SOURCES) -o $(TARGET)

$(TEST_TARGET): $(TEST_SOURCES)
 $(CC) $(CFLAGS) $(TEST_SOURCES) -o $(TEST_TARGET)

clean:
 rm -f $(TARGET) $(TEST_TARGET)

.PHONY: all clean