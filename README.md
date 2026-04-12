# Exchange 
This project is to help me fully understand the fundamentals of an exchange and how the matching engine works. It will also explore some of the optimisation techniques that can be used to make the execution of each request as fast as possible. Stretch goals include handling multiple orderbooks at once, passing out orderbook state, etc. 

## Building the project
To build the project, run the following in the root folder: 
```bash
cmake --build build
```

## Running tests
After building, run from within the build folder:
```bash
ctest --output-on-failure
```