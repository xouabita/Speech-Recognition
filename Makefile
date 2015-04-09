CCFLAGS = clang -std=c99 -g -Werror -pedantic -D_BSD_SOURCE
BIN     = ./recognize

default: $(BIN)

clean:
	rm -f  ./src/*.o
	rm -f  pretreatment_demo
	rm -rf *.dSYM
	rm -f  *.png

debug: CCFLAGS += -g
debug: clean default
	valgrind --leak-check=yes --dsymutil=yes --suppressions=objc.supp $(BIN) oui.wav

$(BIN): ./src/mfcc.o ./src/gnuplot.o ./src/narr.o ./src/dtw.o ./src/main.c
	$(CCFLAGS) -o $(BIN) $^	-lsndfile -lm

./src/gnuplot.o: ./src/gnuplot.c
	$(CCFLAGS) -o $@ -c $<

./src/mfcc.o: ./src/mfcc.c
	$(CCFLAGS) -o $@ -c $<

./src/narr.o: ./NArr/src/narr.c
	$(CCFLAGS) -o $@ -c $<

./src/dtw.o: ./src/dtw.c
	$(CCFLAGS) -o $@ -c $<
