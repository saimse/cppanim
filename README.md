# cppanim ![build-status](https://travis-ci.com/saimse/cppanim.svg?branch=master)

Fully-fledged extensible standalone console animation library. Supports
gif-like animation (with delta-compression), z-axis stacking, transparency,
dynamic content.

Comes with a set of tools to work with animations.

## Building

cppanim only uses GNU Make, so just doing
```
make && make install
```
should be enough.

Possible build targets are:
 - `cppanim`: Builds the library into bin/
 - `utils`: Builds util programs to aid with development
 - `test`: Builds and runs the entire test suite
 - `all`: Builds cppanim, utils and test
 - `docs`: Builds documentation into docs/
 - `help`: Prints this help screen
The following clean operations are available:
 - `clean`: Deletes bin/ output
 - `cleandocs`: Deletes generated documentation
 - `mrproper`: Deletes everything built
	 

## Documentation

Code is written with javadoc documentation. Doxygen generated docs
are in `docs/output`
