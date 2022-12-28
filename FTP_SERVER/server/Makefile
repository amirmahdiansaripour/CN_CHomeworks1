BUILD_DIR = build
SRC_DIR = source
HEADER_DIR = header
EXCEPTION_DIR = exception
CFLAGS = g++ -std=c++11 -I$(HEADER_DIR) -pthread

OBJECTS = \
	$(BUILD_DIR)/Server.o			\
	$(BUILD_DIR)/Main.o				\
	$(BUILD_DIR)/User.o				\
	$(BUILD_DIR)/ConfigReader.o		\
	$(BUILD_DIR)/MessageHandler.o	\
	$(BUILD_DIR)/Response.o			\
	$(BUILD_DIR)/EventLogger.o		\
	$(EXCEPTION_OBJECTS) \

EXCEPTION_HEADERS = \
	$(HEADER_DIR)/$(EXCEPTION_DIR)/badSequenceError.hpp \
	$(HEADER_DIR)/$(EXCEPTION_DIR)/defaultError.hpp 	\
	$(HEADER_DIR)/$(EXCEPTION_DIR)/downloadCapacityError.hpp \
	$(HEADER_DIR)/$(EXCEPTION_DIR)/fileUnavailableError.hpp  \
	$(HEADER_DIR)/$(EXCEPTION_DIR)/invalidUserPassError.hpp	\
	$(HEADER_DIR)/$(EXCEPTION_DIR)/notLoggedInError.hpp	\
	$(HEADER_DIR)/$(EXCEPTION_DIR)/syntaxError.hpp		\

EXCEPTION_OBJECTS = \
	$(BUILD_DIR)/$(EXCEPTION_DIR)/BadSequenceError.o \
	$(BUILD_DIR)/$(EXCEPTION_DIR)/DefaultError.o 	\
	$(BUILD_DIR)/$(EXCEPTION_DIR)/DownloadCapacityError.o \
	$(BUILD_DIR)/$(EXCEPTION_DIR)/FileUnavailableError.o  \
	$(BUILD_DIR)/$(EXCEPTION_DIR)/InvalidUserPassError.o  \
	$(BUILD_DIR)/$(EXCEPTION_DIR)/NotLoggedInError.o	\
	$(BUILD_DIR)/$(EXCEPTION_DIR)/SyntaxError.o		\




all: $(BUILD_DIR) Server.out

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)
	mkdir -p $(BUILD_DIR)/$(EXCEPTION_DIR)

$(BUILD_DIR)/Main.o: $(SRC_DIR)/main.cpp $(HEADER_DIR)/configReader.hpp $(HEADER_DIR)/user.hpp $(HEADER_DIR)/server.hpp $(HEADER_DIR)/messageHandler.hpp $(HEADER_DIR)/response.hpp $(HEADER_DIR)/eventLogger.hpp $(EXCEPTION_HEADERS)
	$(CFLAGS) -c $(SRC_DIR)/main.cpp -o $(BUILD_DIR)/Main.o

$(BUILD_DIR)/Server.o: $(SRC_DIR)/server.cpp $(HEADER_DIR)/configReader.hpp $(HEADER_DIR)/user.hpp $(HEADER_DIR)/server.hpp $(HEADER_DIR)/messageHandler.hpp $(HEADER_DIR)/response.hpp $(HEADER_DIR)/eventLogger.hpp $(EXCEPTION_HEADERS)
	$(CFLAGS) -c $(SRC_DIR)/server.cpp -o $(BUILD_DIR)/Server.o

$(BUILD_DIR)/User.o: $(SRC_DIR)/user.cpp $(HEADER_DIR)/user.hpp
	$(CFLAGS) -c $(SRC_DIR)/user.cpp -o $(BUILD_DIR)/User.o

$(BUILD_DIR)/ConfigReader.o: $(SRC_DIR)/configReader.cpp $(HEADER_DIR)/user.hpp $(HEADER_DIR)/configReader.hpp
	$(CFLAGS) -c $(SRC_DIR)/configReader.cpp -o $(BUILD_DIR)/ConfigReader.o

$(BUILD_DIR)/Response.o: $(SRC_DIR)/response.cpp $(HEADER_DIR)/response.hpp
	$(CFLAGS) -c $(SRC_DIR)/response.cpp -o $(BUILD_DIR)/Response.o

$(BUILD_DIR)/MessageHandler.o: $(SRC_DIR)/messageHandler.cpp $(HEADER_DIR)/messageHandler.hpp $(HEADER_DIR)/response.hpp $(HEADER_DIR)/user.hpp $(HEADER_DIR)/eventLogger.hpp $(EXCEPTION_HEADERS)
	$(CFLAGS) -c $(SRC_DIR)/messageHandler.cpp -o $(BUILD_DIR)/MessageHandler.o

$(BUILD_DIR)/EventLogger.o: $(SRC_DIR)//eventLogger.cpp $(HEADER_DIR)/eventLogger.hpp $(HEADER_DIR)/user.hpp 
	$(CFLAGS) -c $(SRC_DIR)/eventLogger.cpp -o $(BUILD_DIR)/EventLogger.o

$(BUILD_DIR)/$(EXCEPTION_DIR)/BadSequenceError.o: $(SRC_DIR)/$(EXCEPTION_DIR)/badSequenceError.cpp $(HEADER_DIR)/$(EXCEPTION_DIR)/badSequenceError.hpp
	$(CFLAGS) -c $(SRC_DIR)/$(EXCEPTION_DIR)/badSequenceError.cpp -o $(BUILD_DIR)/$(EXCEPTION_DIR)/BadSequenceError.o

$(BUILD_DIR)/$(EXCEPTION_DIR)/DefaultError.o: $(SRC_DIR)/$(EXCEPTION_DIR)/defaultError.cpp $(HEADER_DIR)/$(EXCEPTION_DIR)/defaultError.hpp
	$(CFLAGS) -c $(SRC_DIR)/$(EXCEPTION_DIR)/defaultError.cpp -o $(BUILD_DIR)/$(EXCEPTION_DIR)/DefaultError.o

$(BUILD_DIR)/$(EXCEPTION_DIR)/DownloadCapacityError.o: $(SRC_DIR)/$(EXCEPTION_DIR)/downloadCapacityError.cpp $(HEADER_DIR)/$(EXCEPTION_DIR)/downloadCapacityError.hpp
	$(CFLAGS) -c $(SRC_DIR)/$(EXCEPTION_DIR)/downloadCapacityError.cpp -o $(BUILD_DIR)/$(EXCEPTION_DIR)/DownloadCapacityError.o

$(BUILD_DIR)/$(EXCEPTION_DIR)/FileUnavailableError.o: $(SRC_DIR)/$(EXCEPTION_DIR)/fileUnavailableError.cpp $(HEADER_DIR)/$(EXCEPTION_DIR)/fileUnavailableError.hpp
	$(CFLAGS) -c $(SRC_DIR)/$(EXCEPTION_DIR)/fileUnavailableError.cpp -o $(BUILD_DIR)/$(EXCEPTION_DIR)/FileUnavailableError.o

$(BUILD_DIR)/$(EXCEPTION_DIR)/InvalidUserPassError.o: $(SRC_DIR)/$(EXCEPTION_DIR)/invalidUserPassError.cpp $(HEADER_DIR)/$(EXCEPTION_DIR)/invalidUserPassError.hpp
	$(CFLAGS) -c $(SRC_DIR)/$(EXCEPTION_DIR)/invalidUserPassError.cpp -o $(BUILD_DIR)/$(EXCEPTION_DIR)/InvalidUserPassError.o

$(BUILD_DIR)/$(EXCEPTION_DIR)/NotLoggedInError.o: $(SRC_DIR)/$(EXCEPTION_DIR)/notLoggedInError.cpp $(HEADER_DIR)/$(EXCEPTION_DIR)/notLoggedInError.hpp
	$(CFLAGS) -c $(SRC_DIR)/$(EXCEPTION_DIR)/notLoggedInError.cpp -o $(BUILD_DIR)/$(EXCEPTION_DIR)/NotLoggedInError.o

$(BUILD_DIR)/$(EXCEPTION_DIR)/SyntaxError.o: $(SRC_DIR)/$(EXCEPTION_DIR)/syntaxError.cpp $(HEADER_DIR)/$(EXCEPTION_DIR)/syntaxError.hpp
	$(CFLAGS) -c $(SRC_DIR)/$(EXCEPTION_DIR)/syntaxError.cpp -o $(BUILD_DIR)/$(EXCEPTION_DIR)/SyntaxError.o

Server.out: $(OBJECTS)
	$(CFLAGS) $(OBJECTS) -o Server.out

.PHONY: clean
clean:
	rm -rf $(BUILD_DIR) *.o
	rm -rf $(BUILD_DIR) *.out
	