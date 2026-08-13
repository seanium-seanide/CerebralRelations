# CerebralRelations

A simple BrainFuck interpreter

## Build instructions

```
cmake --preset config-debug
cmake --build --preset build-debug
```

## Build and run unit tests

The following packages are required to build the project with tests:

* CMake >= 3.25
* Catch2 >= 3.15.3
* Clang++ >= 20

The following command can will build and run all tests:

```
ctest --workflow --preset build-and-test
```

## Usage

```
build/debug/source/CerebralRelations [<script filename>]
```
