origin
======
Tools & models to study diversity in complex spatial networks.

The project is developed and tested on Linux x86_64. Stable versions are tagged.

Author
------
Philippe Desjardins-Proulx <philippe.d.proulx@gmail.com>

License
-------
GPL

Dependencies
------------
* gsl (gnu scientific library)... which is why the project is under the GPL license.
* libxml2

On Linux Debian/Ubuntu you can get everything you need to compile and run 'origin' by entering the following line in a terminal:

    sudo apt-get install gcc libgsl0-dev libgsl0ldbl libxml2 libxml2-dev

TODO list
---------
- Pythonization: transfer to Waf & Sphinx.
- Use XML format for output using libxml2 or expat
- Phylogeography.
- Generic tree structure.

