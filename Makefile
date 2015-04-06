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

$(BIN): ./src/pretreatment.o ./src/signal_analysis.o ./src/gnuplot.o ./src/narr.o ./src/main.c
	$(CCFLAGS) -o $(BIN) $^	-lsndfile -lm

./src/pretreatment.o: ./src/pretreatment.c
	$(CCFLAGS) -o $@ -c $<

./src/gnuplot.o: ./src/gnuplot.c
	$(CCFLAGS) -o $@ -c $<

./src/signal_analysis.o: ./src/signal_analysis.c
	$(CCFLAGS) -o $@ -c $<

./src/narr.o: ./NArr/src/narr.c
	$(CCFLAGS) -o $@ -c $<
