# Static Map

[![build status](https://gitlab.com/htfy96/gsoc-static-map/badges/master/build.svg)](https://gitlab.com/htfy96/gsoc-static-map/commits/master)
[![Project Status: Abandoned - Initial development has started, but there has not yet been a stable, usable release; the project has been abandoned and the author(s) do not intend on continuing development.](http://www.repostatus.org/badges/latest/abandoned.svg)](http://www.repostatus.org/#abandoned)

A compile-time map built with `constexpr` targeting C++ 14 and zero runtime overhead.

This is a implementation of [GSoC2017 project of Boost Foundation](https://svn.boost.org/trac/boost/wiki/SoC2017).

## Highlights
- O(1) lookup
- string literals supported by `constexpr_string_view`
- Customizable constexpr comparator and hash function
- Modifiable

## Tested platform
- g++5.3
- g++6
- clang++3.8
- clang++3.9

