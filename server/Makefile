CC = g++
BUILD_DIR = build
SRC_DIR = src
INCLUDE_DIR = include
CFLAGS = -std=c++11 -I$(INCLUDE_DIR)

EXECUTABLE_FILE = Server.out
OBJECTS = \
	$(BUILD_DIR)/Server.o \
	$(BUILD_DIR)/Main.o

all: $(BUILD_DIR) $(EXECUTABLE_FILE)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)


$(BUILD_DIR)/Main.o: $(SRC_DIR)/main.cpp $(INCLUDE_DIR)/Server.hpp
	$(CC) $(CFLAGS) -c $(SRC_DIR)/main.cpp -o $(BUILD_DIR)/Main.o


$(BUILD_DIR)/Server.o: $(SRC_DIR)/Server.cpp $(INCLUDE_DIR)/Server.hpp
	$(CC) $(CFLAGS) -c $(SRC_DIR)/Server.cpp -o $(BUILD_DIR)/Server.o


$(EXECUTABLE_FILE): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $(EXECUTABLE_FILE)

.PHONY: clean
clean:
	rm -rf $(BUILD_DIR) *.o *.out