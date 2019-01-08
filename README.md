origin
======
A neutral model with allopatric/parapatric speciation.

The project is developed and tested on Linux x86_64. Stable versions are tagged.

how-to
======
Compile with make (in a terminal):

    make

And then look at the usage and options with

    ./origin --help

references
==========
P Desjardins-Proulx and D Gravel. A complex speciation-richness relationship in
a simple neutral model. Ecology and Evolution 2(8):1781-1790.
DOI: 10.1002/ece3.292. [PDF](http://figshare.com/articles/How_Likely_Is_Speciation_in_Neutral_Ecology_/94291).

P Desjardins-Proulx and D Gravel. How likely is speciation in neutral ecology?
The American Naturalist 179(1):137-144, 2012.
DOI: 10.1086/663196. [PDF](http://onlinelibrary.wiley.com/doi/10.1002/ece3.292/abstract).

Author
------
Philippe Desjardins-Proulx <philippe.d.proulx@gmail.com>

License
-------
-------
The code is released under the permissive [Apache v2](http://www.apache.org/licenses/LICENSE-2.0)
license, [along with an exception to ensure GPLv2 compatibility](https://lwn.net/Articles/701155/)
see **LICENSE.md**.

Be warned though: it links to the GNU Scientific Library, which is under the GPL license.

Dependencies
------------
gsl (gnu scientific library)... which is why the project is under the GPL license.

On Linux Debian/Ubuntu/Mint you can get everything you need to compile and run
'origin' by entering the following line in a terminal:

    sudo apt-get install gcc libgsl0-dev libgsl0ldbl
