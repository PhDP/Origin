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
from optparse import OptionParser

compiler = 'gcc'

parser = OptionParser()
parser.add_option('-c', '--compiler', dest = 'compiler', help='select the compiler')
parser.add_option('-d', '--debug', help='debug mode')
(options, args) = parser.parse_args()

# Name of the program:
name = 'origin'

# Flags:
if debug is False:
	cflags = '-O3 -DHAVE_INLINE -DNDEBUG -DOINLINING -std=c99'
else:
	cflags = '-g -DHAVE_INLINE -DOINLINING -std=c99'

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
