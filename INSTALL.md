Installation Instructions
=========================

Basic Installation
------------------

This is a cmake-based package. To build it from the root directory, you must
call these commands :

	mkdir build
	cd build
    cmake ..
    make

You may also want to run `make check` to launch unit tests. Additionnaly,
type `make install` to install the programs and any data files and
documentation.

You can remove the program binaries and object files from the build
directory by typing `make clean`.

Compilers and Options
---------------------

cmake should use your system compiler but you can override default in
the configuration step :

	CC=/usr/bin/clang CXX=/usr/bin/clang++ cmake ..

You can choose to rune make command with verbose output :

	make VERBOSE=1

Optional Features
-----------------

If you already ran `cmake` for this project, remove the *CMakeCache.txt*
file then choose an option value when you call cmake, for example :

	cmake -DBUILD_LOGGER_EXAMPLES=ON ..

You can choose to build or not the following optional features :


* **BUILD_LOGGER_EXAMPLES** : build logger example code (default : OFF)
* **BUILD_LOGREADER** :  build an application to help you deal with logfiles
  (default : OFF)
* **BUILD_TESTS** : build unit tests (default : ON)

