CCFLAGS = clang -std=c99 -Werror -O3 -pedantic -D_BSD_SOURCE
BIN     = ./pretreatment_demo

default: $(BIN)

clean:
	rm -f  ./src/*.o
	rm -f  pretreatment_demo
	rm -rf *.dSYM
	rm -f  *.png

debug: CCFLAGS += -g
debug: clean default
	valgrind --leak-check=yes --dsymutil=yes --suppressions=objc.supp $(BIN) oui.wav

$(BIN): ./src/pretreatment.o ./src/gnuplot.o ./src/main.c
	$(CCFLAGS) -o $(BIN) $^ -lsndfile -lm

./src/pretreatment.o: ./src/pretreatment.c
	$(CCFLAGS) -o $@ -c $<

./src/gnuplot.o: ./src/gnuplot.c
	$(CCFLAGS) -o $@ -c $<
