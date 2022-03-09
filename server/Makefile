CC = g++
BUILD_DIR = build
SRC_DIR = src
INCLUDE_DIR = include
CFLAGS = -std=c++11 -I$(INCLUDE_DIR)

EXECUTABLE_FILE = Server.out

OBJECTS = \
	$(BUILD_DIR)/Main.o 		\
	$(BUILD_DIR)/Server.o 		\
	$(BUILD_DIR)/ConfigReader.o \
	$(BUILD_DIR)/User.o 		
	
UserSensitivityList = \
	$(SRC_DIR)/User.cpp

ConfigReaderSensitivityList = \
	$(SRC_DIR)/ConfigReader.cpp \
	$(INCLUDE_DIR)/User.hpp

ServerSensitivityList = \
	$(SRC_DIR)/Server.cpp \
	$(INCLUDE_DIR)/User.hpp \
	$(INCLUDE_DIR)/ConfigReader.hpp

MainSensitivityList = \
	$(SRC_DIR)/main.cpp \
	$(INCLUDE_DIR)/Server.hpp \


all: $(BUILD_DIR) $(EXECUTABLE_FILE)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/Main.o: $(MainSensitivityList)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/main.cpp -o $(BUILD_DIR)/Main.o

$(BUILD_DIR)/Server.o: $(ServerSensitivityList)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/Server.cpp -o $(BUILD_DIR)/Server.o

$(BUILD_DIR)/ConfigReader.o: $(ConfigReaderSensitivityList)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/ConfigReader.cpp -o $(BUILD_DIR)/ConfigReader.o

$(BUILD_DIR)/User.o: $(UserSensitivityList)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/User.cpp -o $(BUILD_DIR)/User.o


$(EXECUTABLE_FILE): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $(EXECUTABLE_FILE)

.PHONY: clean
clean:
	rm -rf $(BUILD_DIR) *.o *.out