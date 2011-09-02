CC = gcc
CFLAGS = -O3 -DHAVE_INLINE -DEXTRAPRINT -march=native -std=c99 -lgsl -lgslcblas -lm -lpthread

ssne: model_ssne.c
	$(CC) $(CFLAGS) -o ssne model_ssne.c species.c dvector.c ivector.c specieslist.c graph.c graphgen.c utils.c ecology.c stats.c maths.c str.c


