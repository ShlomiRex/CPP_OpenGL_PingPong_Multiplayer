CXX := clang++-5.0
CXXFLAGS := -Wall -std=c++17 -pthread
DBGFLAG := -g
OBJS := $(patsubst %.cpp, %.o, $(wildcard *.cpp))
LIBS := -lglut -lGL -lGLU
all: link
	./a.out

link: $(OBJS)
	$(CXX) $(CXXFLAGS) $(LIBS) $^

clean:
	rm -f *.o *.out *.exe

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(DBGFLAG) -c $<

git:
	git add .
	git commit -m "Automatic Makefile Commit"
	git push