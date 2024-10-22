# Variables de compilation
CC = gcc
CFLAGS = -Iinclude

LDFLAGS = #Libs externes

TARGET = output
SRC = src/*.c
TEST_TARGET = test_output
TEST_SRC = tests/*.c src/unity.c src/features.c  # Ajouter tout autre fichier source à tester ici 

all: $(TARGET)

$(TARGET): $(SRC)
	rm -f $(TARGET)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

$(TEST_TARGET): $(TEST_SRC)
	rm -f $(TEST_TARGET)
	$(CC) $(CFLAGS) -o $(TEST_TARGET) $(TEST_SRC)

test: $(TEST_TARGET)
	./$(TEST_TARGET)

clean:
	rm -f $(TARGET) $(TEST_TARGET)