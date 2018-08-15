#Note: you must have the correct project structure in order to compile/link.
#You can run: make create_directories in order to automatically create the project directories.



CXX := clang++-5.0
CXXFLAGS := -Wall -std=c++11 -Iinclude #Insted of include you can create other directory and type: -Iheaders
DBGFLAG := -g
RELEASE := -O3
LDFLAGS := -lglut -lGL -lGLU -lpthread #For linker

#Project Structure
BIN_DIR := bin
BUILD_DIR := build
SRC_DIR := src
TEST_DIR := test
DIRS := src bin doc include test build logs include/lib #The project structure in the main directory

SOURCES = $(wildcard $(SRC_DIR)/*.cpp)
OBJECTS = $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SOURCES))

#Run
run: link
	./$(BIN_DIR)/main.out

#Link
link: $(OBJECTS)
	$(CXX) $(LDFLAGS) $^ -o bin/main.out

#Compile
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) $(DBGFLAG) -c $< -o $@ 

#Create directories if not exists(project structure)
create_directories:
	mkdir -p $(DIRS)
	

#Clean
clean:
	find . \( -name '*.o' -or -name '*.out' -or -name '*.exe' \) -delete

#Automatic git commit
git:
	git add .
	git commit -m "Automatic Makefile Commit"
	git push

.PHONY: test
test1:
	$(CXX) $(CXXFLAGS) $(DBGFLAG) -c "$(TEST_DIR)/test1/client.cpp" -o "$(BIN_DIR)/test1_client.out"
	$(CXX) $(CXXFLAGS) $(DBGFLAG) -c "$(TEST_DIR)/test1/server.cpp" -o "$(BIN_DIR)/test1_server.out"

create_server: link
	./$(BIN_DIR)/main.out < $(TEST_DIR)/create_server_input.txt

create_client1: link
	./$(BIN_DIR)/main.out < $(TEST_DIR)/create_client_input.txt

create_client2: link
	./$(BIN_DIR)/main.out < $(TEST_DIR)/create_client_input2.txt

test_server_connection:
	netstat -a | grep 8888


	