# cppanim

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
 - `test` - coverage tests (`bash` necessary)
 - `utils` - utility tools (builds library)
 - `clean` - deletes built files (leaves installed files)
 - `docs` - Runs doxygen

## Documentation

Code is written with javadoc documentation. Doxygen generated docs
are in `docs/`
