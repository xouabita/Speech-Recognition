visualize: visualize_sound.c
	clang -g -lsndfile visualize_sound.c -o visualize

clean:
	rm -f visualize
