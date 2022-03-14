CC = g++
BUILD_DIR = build
SRC_DIR = src
INCLUDE_DIR = include
CFLAGS = -std=c++11 -I$(INCLUDE_DIR)
LINK_FLAGS = -pthread

EXECUTABLE_FILE = Server.out

OBJECTS = \
	$(BUILD_DIR)/Main.o 			\
	$(BUILD_DIR)/Server.o 			\
	$(BUILD_DIR)/ConfigReader.o 	\
	$(BUILD_DIR)/User.o 			\
	$(BUILD_DIR)/CommandHandler.o	\
	$(BUILD_DIR)/Logger.o			\
	$(BUILD_DIR)/Exception.o 		\
	$(BUILD_DIR)/Response.o
	
ResponseSensitivityList = \
	$(SRC_DIR)/Response.cpp

ExceptionSensitivityList = \
	$(SRC_DIR)/Exception.cpp

LoggerSensitivityList = \
	$(SRC_DIR)/Logger.cpp

UserSensitivityList = \
	$(SRC_DIR)/User.cpp

ConfigReaderSensitivityList = \
	$(SRC_DIR)/ConfigReader.cpp \
	$(INCLUDE_DIR)/User.hpp

CommandHandlerSensitivityList = \
	$(SRC_DIR)/CommandHandler.cpp 	\
	$(INCLUDE_DIR)/Logger.hpp		\
	$(INCLUDE_DIR)/User.hpp			\
	$(INCLUDE_DIR)/Response.hpp		\
	$(INCLUDE_DIR)/Exception.hpp

ServerSensitivityList = \
	$(SRC_DIR)/Server.cpp 				\
	$(INCLUDE_DIR)/User.hpp 			\
	$(INCLUDE_DIR)/ConfigReader.hpp		\
	$(INCLUDE_DIR)/CommandHandler.hpp

MainSensitivityList = \
	$(SRC_DIR)/main.cpp \
	$(INCLUDE_DIR)/Server.hpp


all: $(BUILD_DIR) $(EXECUTABLE_FILE)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/Main.o: $(MainSensitivityList)
	$(CC) $(CFLAGS) $(LINK_FLAGS) -c $(SRC_DIR)/main.cpp -o $(BUILD_DIR)/Main.o

$(BUILD_DIR)/Server.o: $(ServerSensitivityList)
	$(CC) $(CFLAGS) $(LINK_FLAGS) -c $(SRC_DIR)/Server.cpp -o $(BUILD_DIR)/Server.o

$(BUILD_DIR)/CommandHandler.o: $(CommandHandlerSensitivityList)
	$(CC) $(CFLAGS) $(LINK_FLAGS) -c $(SRC_DIR)/CommandHandler.cpp -o $(BUILD_DIR)/CommandHandler.o

$(BUILD_DIR)/ConfigReader.o: $(ConfigReaderSensitivityList)
	$(CC) $(CFLAGS) $(LINK_FLAGS) -c $(SRC_DIR)/ConfigReader.cpp -o $(BUILD_DIR)/ConfigReader.o

$(BUILD_DIR)/User.o: $(UserSensitivityList)
	$(CC) $(CFLAGS) $(LINK_FLAGS) -c $(SRC_DIR)/User.cpp -o $(BUILD_DIR)/User.o

$(BUILD_DIR)/Logger.o: $(LoggerSensitivityList)
	$(CC) $(CFLAGS) $(LINK_FLAGS) -c $(SRC_DIR)/Logger.cpp -o $(BUILD_DIR)/Logger.o

$(BUILD_DIR)/Exception.o: $(ExceptionSensitivityList)
	$(CC) $(CFLAGS) $(LINK_FLAGS) -c $(SRC_DIR)/Exception.cpp -o $(BUILD_DIR)/Exception.o

$(BUILD_DIR)/Response.o: $(ResponseSensitivityList)
	$(CC) $(CFLAGS) $(LINK_FLAGS) -c $(SRC_DIR)/Response.cpp -o $(BUILD_DIR)/Response.o


$(EXECUTABLE_FILE): $(OBJECTS)
	$(CC) $(CFLAGS) $(LINK_FLAGS) $(OBJECTS) -o $(EXECUTABLE_FILE)

.PHONY: clean
clean:
	rm -rf $(BUILD_DIR) *.o *.out