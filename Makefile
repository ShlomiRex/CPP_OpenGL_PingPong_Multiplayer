CXX := clang++-5.0
CXXFLAGS := -Wall -std=c++17 -Iinclude
DBGFLAG := -g
LDFLAGS := -lglut -lGL -lGLU -lpthread #For linker
CWD := $(shell pwd)

#Project Structure
BIN_DIR := bin
BUILD_DIR := build
SRC_DIR := src
HEADERS_DIR := include

SOURCES = $(wildcard $(SRC_DIR)/*.cpp)
OBJECTS = $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SOURCES))

run: link
	./bin/a.out

link: $(OBJECTS)
	$(CXX) $(LDFLAGS) $^ -o bin/a.out #Link objects

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@ 




.PHONY: clean
clean:
	rm -f $(BUILD_DIR)/*.o
	rm -f $(BIN_DIR)/*.out

git:
	git add .
	git commit -m "Automatic Makefile Commit"
	git push

