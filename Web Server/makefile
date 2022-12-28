BUILD_DIR = build
HEADER_DIR = header
SRC_DIR = source
CFLAGS = g++ -std=c++11 -I$(HEADER_DIR) -pthread

OBJECTS = \
	$(BUILD_DIR)/HttpServer.o \
	$(BUILD_DIR)/Main.o \
	$(BUILD_DIR)/RequestHandler.o \


all: $(BUILD_DIR) Server.out

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/Main.o: $(SRC_DIR)/main.cpp $(HEADER_DIR)/HttpServer.hpp $(HEADER_DIR)/RequestHandler.hpp
	$(CFLAGS) -c $(SRC_DIR)/main.cpp -o $(BUILD_DIR)/Main.o

$(BUILD_DIR)/HttpServer.o: $(SRC_DIR)/HttpServer.cpp $(HEADER_DIR)/HttpServer.hpp $(HEADER_DIR)/RequestHandler.hpp
	$(CFLAGS) -c $(SRC_DIR)/HttpServer.cpp -o $(BUILD_DIR)/HttpServer.o

$(BUILD_DIR)/RequestHandler.o: $(SRC_DIR)/RequestHandler.cpp $(HEADER_DIR)/RequestHandler.hpp
	$(CFLAGS) -c $(SRC_DIR)/RequestHandler.cpp -o $(BUILD_DIR)/RequestHandler.o

Server.out: $(OBJECTS)
	$(CFLAGS) $(OBJECTS) -o Server.out

.PHONY: clean
clean:
	rm -rf $(BUILD_DIR) *.o
	rm -rf $(BUILD_DIR) *.out
