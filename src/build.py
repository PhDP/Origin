#! /usr/bin/env python
#
# A small Python script to build the program.
#
# Use 'python build.py --help' for a list of options
#
# Yes I know about make (and Waf), and I understand the limitations of this 
# simple script, but I prefer this system. Bite me :P

import os
import sys
from optparse import OptionParser

parser = OptionParser()
parser.add_option('-c', '--compiler', dest = 'compiler', default = 'gcc', help = 'Select the compiler')
parser.add_option('-d', action="store_true", default = False, help = 'Debug mode')
(options, args) = parser.parse_args()

# Name of the program:
name = 'origin'

# Flags:
if options.d is False:
    cflags = '-O3 -DHAVE_INLINE -DNDEBUG -DOINLINING -std=c99'
else:
    cflags = '-g -DHAVE_INLINE -DOINLINING -std=c99'

# List of files to compile:
cfiles = 'main.c species.c ivector.c specieslist.c graph.c utils.c'

# Linkage:
clinks = '-lgsl -lgslcblas -lpthread'
if options.compiler != 'icc':
    clinks += ' -lm'

# The final command to compile:
s = options.compiler + ' ' + cflags + ' ' + cfiles + ' -o ' + name + ' ' + clinks

# Show the command used:
print(s)

# Compile:
os.system(s)
