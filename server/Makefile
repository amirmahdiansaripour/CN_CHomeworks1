BUILD_DIR = build
SRC_DIR = source
HEADER_DIR = header
CFLAGS = g++ -std=c++11 -I$(HEADER_DIR) -pthread

OBJECTS = \
	$(BUILD_DIR)/Server.o			\
	$(BUILD_DIR)/Main.o				\
	$(BUILD_DIR)/User.o				\
	$(BUILD_DIR)/ConfigReader.o		\
	$(BUILD_DIR)/MessageHandler.o	\
	$(BUILD_DIR)/Response.o			\

all: $(BUILD_DIR) Server.out

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/Main.o: $(SRC_DIR)/main.cpp $(HEADER_DIR)/configReader.hpp $(HEADER_DIR)/user.hpp $(HEADER_DIR)/server.hpp
	$(CFLAGS) -c $(SRC_DIR)/main.cpp -o $(BUILD_DIR)/Main.o

$(BUILD_DIR)/Server.o: $(SRC_DIR)/server.cpp $(HEADER_DIR)/configReader.hpp $(HEADER_DIR)/user.hpp $(HEADER_DIR)/server.hpp $(HEADER_DIR)/messageHandler.hpp $(HEADER_DIR)/response.hpp
	$(CFLAGS) -c $(SRC_DIR)/server.cpp -o $(BUILD_DIR)/Server.o

$(BUILD_DIR)/User.o: $(SRC_DIR)/user.cpp $(HEADER_DIR)/user.hpp
	$(CFLAGS) -c $(SRC_DIR)/user.cpp -o $(BUILD_DIR)/User.o

$(BUILD_DIR)/ConfigReader.o: $(SRC_DIR)/configReader.cpp $(HEADER_DIR)/user.hpp $(HEADER_DIR)/configReader.hpp
	$(CFLAGS) -c $(SRC_DIR)/configReader.cpp -o $(BUILD_DIR)/ConfigReader.o

$(BUILD_DIR)/Response.o: $(SRC_DIR)/response.cpp $(HEADER_DIR)/response.hpp
	$(CFLAGS) -c $(SRC_DIR)/response.cpp -o $(BUILD_DIR)/Response.o

$(BUILD_DIR)/MessageHandler.o: $(SRC_DIR)/messageHandler.cpp $(HEADER_DIR)/messageHandler.hpp $(HEADER_DIR)/response.hpp $(HEADER_DIR)/user.hpp
	$(CFLAGS) -c $(SRC_DIR)/messageHandler.cpp -o $(BUILD_DIR)/MessageHandler.o



Server.out: $(OBJECTS)
	$(CFLAGS) $(OBJECTS) -o Server.out

.PHONY: clean
clean:
	rm -rf $(BUILD_DIR) *.o
	rm -rf $(BUILD_DIR) *.out
	