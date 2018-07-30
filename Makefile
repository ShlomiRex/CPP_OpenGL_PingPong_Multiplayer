#Note: you must have the correct project structure in order to compile/link.
#You can run: make create_directories in order to automatically create the project directories.



CXX := clang++-5.0
CXXFLAGS := -Wall -std=c++17 -Iinclude #Insted of include you can create other directory and type: -Iheaders
DBGFLAG := -g
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
	./bin/main.out

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
.PHONY: clean
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
.PHONY: test1_server test1_client
test1_server:
	./bin/test1_server.out
test1_client:
	./bin/test1_client.out

	