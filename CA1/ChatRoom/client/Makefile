BUILD_DIR = build
SRC_DIR = src
HEADER_DIR = header
CFLAGS = g++ -std=c++11 -I$(HEADER_DIR)

OBJECTS = \
	$(BUILD_DIR)/Client.o \
	$(BUILD_DIR)/Main.o

all: $(BUILD_DIR) Client.out

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)


$(BUILD_DIR)/Main.o: $(SRC_DIR)/main.cpp $(HEADER_DIR)/client.hpp
	$(CFLAGS) -c $(SRC_DIR)/main.cpp -o $(BUILD_DIR)/Main.o

$(BUILD_DIR)/Client.o: $(SRC_DIR)/client.cpp $(HEADER_DIR)/client.hpp
	$(CFLAGS) -c $(SRC_DIR)/client.cpp -o $(BUILD_DIR)/Client.o

Client.out: $(OBJECTS)
	$(CFLAGS) $(OBJECTS) -o Client.out

.PHONY: clean
clean:
	rm -rf $(BUILD_DIR) *.o
	rm -rf $(BUILD_DIR) *.out
