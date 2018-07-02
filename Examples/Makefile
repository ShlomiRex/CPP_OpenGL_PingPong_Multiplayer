CXX := clang++-5.0
CXXFLAGS := -Wall -std=c++17
LIBS := -lglut -lGL -lGLU
DBGFLAG := -g
#Tell make to make one .out file for each .cpp file found in the current directory
OBJS := $(patsubst %.cpp, %.o, $(wildcard *.cpp))

all: link
	./a.out

link: $(OBJS)
	$(CXX) $(CXXFLAGS) $(LIBS) $^

#Clean objects
clean:
	rm -f *.o *.out *.exe

#For each xxx.cpp file, compile it and save as xxx.o
%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(DBGFLAG) -c $<
