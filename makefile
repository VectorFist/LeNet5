CC=g++
CFLAGS=-c -Wall -std=c++11
SOURCES=$(wildcard src/*.cpp)
INC=-I./include/

$(shell mkdir -p objs)

lenet5: $(SOURCES:src/%.cpp=objs/%.o)
	$(CC) -pthread $^ -o $@

objs/%.o: src/%.cpp
	$(CC) $(CFLAGS) $(INC) $< -o $@
clean:
	rm -r objs
	rm lenet5
