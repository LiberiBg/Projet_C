# Compilateur et options
CC = gcc
CFLAGS = -Wall -Wextra
INCLUDES = -I./include -I./src `pkg-config --cflags gtk+-3.0`
LIBS = `pkg-config --libs gtk+-3.0`

# Répertoires
SRC_DIR = src
BUILD_DIR = build
TEST_DIR = tests
INCLUDE_DIR = include

# Fichiers source
SRCS = $(SRC_DIR)/main.c $(SRC_DIR)/analyseur.c
TEST_SRCS = $(wildcard $(TEST_DIR)/*.c) $(filter-out $(SRC_DIR)/main.c, $(wildcard $(SRC_DIR)/*.c))

# Exécutables
EXEC = program
TEST_EXEC = test_program
BUILD_EXEC = $(BUILD_DIR)/program

# Règle par défaut : nettoie, compile et exécute
all: clean $(EXEC)
	./$(EXEC)

# Compilation du programme principal
$(EXEC): $(SRCS)
	$(CC) $(CFLAGS) $(INCLUDES) $(SRCS) -o $@ $(LIBS)

# Compilation et exécution des tests
test: $(TEST_EXEC)
	./$(TEST_EXEC)

$(TEST_EXEC): $(TEST_SRCS)
	$(CC) $(CFLAGS) $(INCLUDES) $(TEST_SRCS) -o $@ $(LIBS)

# Compilation dans le répertoire build
compile: $(BUILD_DIR) $(BUILD_EXEC)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BUILD_EXEC): $(SRCS)
	$(CC) $(CFLAGS) $(INCLUDES) $(SRCS) -o $@ $(LIBS)

# Nettoyage
clean:
	rm -f $(EXEC) $(TEST_EXEC) $(BUILD_EXEC) *.o
	rm -rf $(BUILD_DIR)

.PHONY: all clean test compile