# Compilateur et options
CC = gcc
CFLAGS = -Wall -Wextra
INCLUDES = -I./include -I./src

# Répertoires
SRC_DIR = src
TEST_DIR = tests
INCLUDE_DIR = include

# Fichiers source
SRCS = src/main.c src/analyseur.c
TEST_SRCS = $(wildcard $(TEST_DIR)/*.c) $(filter-out $(SRC_DIR)/main.c, $(wildcard $(SRC_DIR)/*.c))

# Exécutables
EXEC = output
TEST_EXEC = test_output

# Règle par défaut : nettoie, compile et exécute
all: clean $(EXEC)
	./$(EXEC)

# Compilation du programme principal
$(EXEC): $(SRCS)
	$(CC) $(CFLAGS) $(INCLUDES) $(SRCS) -o $@

# Compilation et exécution des tests
test: $(TEST_EXEC)
	./$(TEST_EXEC)

$(TEST_EXEC): $(TEST_SRCS)
	$(CC) $(CFLAGS) $(INCLUDES) `pkg-config --cflags gtk+-3.0` $(TEST_SRCS) -o $@

# Nettoyage
clean:
	rm -f $(EXEC) $(TEST_EXEC) *.o

.PHONY: all clean test