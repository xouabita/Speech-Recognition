CCFLAGS = clang -std=c99 -Wall -Wextra -O3 -pedantic
BIN     = ./pretreatment_demo

default: $(BIN)

clean:
	rm -f  ./src/*.o
	rm -f  pretreatment_demo
	rm -rf *.dSYM

debug: CCFLAGS += -g
debug: clean default
	valgrind --leak-check=yes --dsymutil=yes --suppressions=objc.supp $(BIN) oui.wav

$(BIN): ./src/gnuplot.o ./src/pretreatment.o ./src/main.c
	$(CCFLAGS) -lsndfile -o $(BIN) $^

./src/pretreatment.o: ./src/pretreatment.c
	$(CCFLAGS) -o $@ -c $<

./src/gnuplot.o: ./src/gnuplot.c
	$(CCFLAGS) -o $@ -c $<
