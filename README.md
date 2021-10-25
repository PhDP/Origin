# Origin

A neutral biodiversity model with allopatric/parapatric speciation.

The project is developed and tested on Linux x86_64.

## how-to

Compile with make (in a terminal):

    $ mkdir build && cd $_
    $ cmake ..
    $ make

It should build the **origin** executable in the **src** directory.

You can look at all the options with:

    ./origin --help

## References

P Desjardins-Proulx and D Gravel. A complex speciation-richness relationship in
a simple neutral model. Ecology and Evolution 2(8):1781-1790.
DOI: 10.1002/ece3.292. [PDF](https://onlinelibrary.wiley.com/doi/10.1002/ece3.292/abstract).

P Desjardins-Proulx and D Gravel. How likely is speciation in neutral ecology?
The American Naturalist 179(1):137-144, 2012.
DOI: 10.1086/663196. [PDF](https://phdp.github.io/files/desjardins-proulx_2012a.pdf)

## Author

Philippe Desjardins-Proulx <philippe.desjardins.proulx@umontreal.ca>

## Dependencies

On Ubuntu you can get everything you need to compile and run *Origin* with:

    $ sudo apt install gcc cmake libgsl0-dev

## License

The code is released under the permissive [Apache v2](http://www.apache.org/licenses/LICENSE-2.0)
license, [along with an exception to ensure GPLv2 compatibility](https://lwn.net/Articles/701155/)
see **LICENSE.md**.

Be warned though: it links to the GNU Scientific Library, which is under the GPL license.

