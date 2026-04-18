# CPP Exchange Project
[![C/C++ CI](https://github.com/James-h-1969/exchange-cpp/actions/workflows/c-cpp.yml/badge.svg)](https://github.com/James-h-1969/exchange-cpp/actions/workflows/c-cpp.yml)<br />
This project is to help me fully understand the fundamentals of an exchange and how the matching engine works. It will also explore some of the optimisation techniques that can be used to make the execution of each request as fast as possible. Stretch goals include handling multiple orderbooks at once, passing out orderbook state, etc. 

## Building the project
To first create the build directory and generate the build system files:
```bash
cmake -B build -S .
```
To then compile the project:
```bash
cmake --build build
```

## Running tests
After building, run from within the build folder:
```bash
ctest --output-on-failure
```
