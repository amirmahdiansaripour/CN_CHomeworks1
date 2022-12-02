BUILD_DIR = build
SRC_DIR = source
HEADER_DIR = header
CFLAGS = g++ -std=c++11 -I$(HEADER_DIR)

OBJECTS = \
	$(BUILD_DIR)/Server.o \
	$(BUILD_DIR)/Main.o 

all: $(BUILD_DIR) Server.out

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/Main.o: $(SRC_DIR)/main.cpp $(HEADER_DIR)/server.hpp
	$(CFLAGS) -c $(SRC_DIR)/main.cpp -o $(BUILD_DIR)/Main.o


$(BUILD_DIR)/Server.o: $(SRC_DIR)/server.cpp $(HEADER_DIR)/server.hpp
	$(CFLAGS) -c $(SRC_DIR)/server.cpp -o $(BUILD_DIR)/Server.o

Server.out: $(OBJECTS)
	$(CFLAGS) $(OBJECTS) -o Server.out

.PHONY: clean
clean:
	rm $(BUILD_DIR) *.o
	rm $(BUILD_DIR) *.out
	