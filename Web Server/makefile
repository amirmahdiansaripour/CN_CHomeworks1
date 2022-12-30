BUILD_DIR = build
HEADER_DIR = header
EXCEPTION_DIR = exception
SRC_DIR = source
CFLAGS = g++ -std=c++11 -I$(HEADER_DIR) -pthread

OBJECTS = \
	$(BUILD_DIR)/HttpServer.o \
	$(BUILD_DIR)/Main.o \
	$(BUILD_DIR)/RequestHandler.o \
	$(EXCEPTION_OBJECTS) \

EXCEPTION_HEADERS = \
	$(HEADER_DIR)/$(EXCEPTION_DIR)/Error404.hpp \

EXCEPTION_OBJECTS = \
	$(BUILD_DIR)/Error404.o \


all: $(BUILD_DIR) Server.out

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/Main.o: $(SRC_DIR)/main.cpp $(HEADER_DIR)/HttpServer.hpp $(HEADER_DIR)/RequestHandler.hpp $(EXCEPTION_HEADERS)
	$(CFLAGS) -c $(SRC_DIR)/main.cpp -o $(BUILD_DIR)/Main.o

$(BUILD_DIR)/HttpServer.o: $(SRC_DIR)/HttpServer.cpp $(HEADER_DIR)/HttpServer.hpp $(HEADER_DIR)/RequestHandler.hpp $(EXCEPTION_HEADERS)
	$(CFLAGS) -c $(SRC_DIR)/HttpServer.cpp -o $(BUILD_DIR)/HttpServer.o

$(BUILD_DIR)/RequestHandler.o: $(SRC_DIR)/RequestHandler.cpp $(HEADER_DIR)/RequestHandler.hpp $(EXCEPTION_HEADERS)
	$(CFLAGS) -c $(SRC_DIR)/RequestHandler.cpp -o $(BUILD_DIR)/RequestHandler.o

$(BUILD_DIR)/Error404.o: $(SRC_DIR)/$(EXCEPTION_DIR)/Error404.cpp $(HEADER_DIR)/$(EXCEPTION_DIR)/Error404.hpp
	$(CFLAGS) -c $(SRC_DIR)/$(EXCEPTION_DIR)/Error404.cpp -o $(BUILD_DIR)/Error404.o


Server.out: $(OBJECTS)
	$(CFLAGS) $(OBJECTS) -o Server.out

.PHONY: clean
clean:
	rm -rf $(BUILD_DIR) *.o
	rm -rf $(BUILD_DIR) *.out
