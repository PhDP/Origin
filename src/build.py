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
name = 'origin'

# Flags:
cflags = '-O3 -DHAVE_INLINE -DOINLINING -std=c99'

# List of files to compile:
cfiles = 'main.c species.c ivector.c specieslist.c graph.c utils.c'

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
