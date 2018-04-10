SRC=$(wildcard src/*.cc src/**/*.cc)
OBJS=$(SRC:.cc=.o)
OUT=./calc
CC=clang++
CCOPTS=-std=c++14 -c -Wall
LDOPTS=-lpthread

default: $(SRC) $(OUT)

$(OUT): $(OBJS) 
	@echo -n "Link "
	@echo $@
	$(CC) $(OBJS) $(LDOPTS) -o $@

.cc.o:
	@echo -n "Build source "
	@echo $<
	$(CC) $(CCOPTS) $< -o $@

clean:
	rm -f *.o calc
	rm -f src/*.o
	rm -f src/**/*.o