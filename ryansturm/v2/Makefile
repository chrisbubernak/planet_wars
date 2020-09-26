CC=gcc 
CPP=g++ 

TARGETS= TreeTwoBot

CFLAGS := -std=c++17 -g1 -lSegFault  -g -rdynamic
CFLAGS := $(CFLAGS) $(shell \
	[ "$$(uname -s)" = "Darwin" ] && echo "-arch" && uname -m; \
)

LFLAGS := $(CFLAGS)


all: $(TARGETS)

clean:
	rm -rf *.o $(TARGETS)

game.o: game.cpp game.h utils.h
	$(CPP) $(CFLAGS) $< -c -o $@

utils.o: utils.cpp utils.h
	$(CPP) $(CFLAGS) $< -c -o $@
	
#%.o: %.cpp

Tree%: Tree%.cpp game.o utils.o
	$(CPP) $(LFLAGS) $^ -o $@
