#! /usr/bin/env python

import os
import sys

if len(sys.argv) is 2:
    compiler = sys.argv[1]
else:
    compiler = "gcc"

name = "ssne"
cflags = "-O3 -DHAVE_INLINE -DOINLINING -std=c99"
cfiles = "model_ssne.c species.c dvector.c ivector.c specieslist.c graph.c graphgen.c utils.c ecology.c stats.c maths.c str.c"
clinks = "-lgsl -lgslcblas -lm -lpthread"
s = compiler + " " + cflags + " " + cfiles + " -o " + name + " " + clinks
print(s)
os.system(s)
