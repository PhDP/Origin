#! /usr/bin/env python
#
# A small Python script to compile the programs.
#
# Yes I know about make (and Waf), and I understand the limitations of this simple script, but
# I prefer this system. Bite me :P
#
# Currently the script takes only one argument: the name of the compiler.

import os
import sys

# If the name of the compiler isn't supplied, use gcc:
if len(sys.argv) is 2:
    compiler = sys.argv[1]
else:
    compiler = 'gcc'

# Name of the program:
name = 'ssne'

# Flags:
cflags = '-O3 -DHAVE_INLINE -DOINLINING -DEXTRAPRINT -std=c99'

# List of files to compile:
cfiles = 'model_ssne.c species.c dvector.c ivector.c specieslist.c graph.c graphgen.c utils.c ecology.c stats.c maths.c str.c'

# Linkage:
clinks = '-lgsl -lgslcblas -lpthread'
if compiler != 'icc':
    clinks += ' -lm'

# The final command to compile:
s = compiler + ' ' + cflags + ' ' + cfiles + ' -o ' + name + ' ' + clinks

# Show the command used:
print(s)

# Compile:
os.system(s)
