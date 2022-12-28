BUILD_DIR = build
CFLAGS = g++ -std=c++11 -pthread

OBJECTS = \
	$(BUILD_DIR)/HttpServer.o \
	$(BUILD_DIR)/Main.o \


all: $(BUILD_DIR) Server.out

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/Main.o: main.cpp HttpServer.hpp
	$(CFLAGS) -c main.cpp -o $(BUILD_DIR)/Main.o

$(BUILD_DIR)/HttpServer.o: HttpServer.cpp HttpServer.hpp
	$(CFLAGS) -c HttpServer.cpp -o $(BUILD_DIR)/HttpServer.o

Server.out: $(OBJECTS)
	$(CFLAGS) $(OBJECTS) -o Server.out

.PHONY: clean
clean:
	rm -rf $(BUILD_DIR) *.o
	rm -rf $(BUILD_DIR) *.out
