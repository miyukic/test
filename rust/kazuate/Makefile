TARGET = main.exe
CXX = clang++
OBJS = main.o
CXXFLAGS = -Wall -Wextra -std=c++20
LDFLAGS = 


DEBUG = -g -fsanitize=address -Wfloat-equal -O0

.PHONY: all
all: main.exe Makefile

.PHONY: clean
clean:
	rm -rf *.o

.PHONY: debug
debug: Makefile
	$(CXX) $(CXXFLAGS) $(DEBUG) main.cpp


main.exe: $(OBJS) Makefile
	$(CXX) $(LDFLAGS) -o main.exe $<

%.o: %.cpp Makefile
	$(CXX) $(CXXFLAGS) -O2 -c $<
