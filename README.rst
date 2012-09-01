origin
======
A neutral model with allopatric/parapatric speciation.

The project is developed and tested on Linux x86_64. Stable versions are tagged.

how-to
======
Compile with make

    $ make

And then look at the usage and options with

    $ ./origin --help

references
==========
P Desjardins-Proulx and D Gravel. A complex speciation-richness relationship in
a simple neutral model. Ecology and Evolution 2(8):1781-1790.
PDF: http://figshare.com/articles/How_Likely_Is_Speciation_in_Neutral_Ecology_/94291
DOI: 10.1002/ece3.292.

P Desjardins-Proulx and D Gravel. How likely is speciation in neutral ecology?
The American Naturalist 179(1):137-144, 2012.
PDF: http://onlinelibrary.wiley.com/doi/10.1002/ece3.292/abstract
DOI: 10.1086/663196.

Author
------
Philippe Desjardins-Proulx <philippe.d.proulx@gmail.com>

License
-------
GPL

Dependencies
------------
gsl (gnu scientific library)... which is why the project is under the GPL license.

On Linux Debian/Ubuntu/Mint you can get everything you need to compile and run
'origin' by entering the following line in a terminal:

    sudo apt-get install gcc libgsl0-dev libgsl0ldbl
