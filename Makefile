visualize: visualize_sound.c
	clang -lsndfile visualize_sound.c -o visualize

clean:
	rm -f visualize
