cmake_minimum_required(VERSION 3.14)
project(OrderbookProject CXX)

# Set the C++ standard to 20
set(CMAKE_CXX_STANDARD 20)

# Ensure C++20 is actually supported and required
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Disable "extensions" (like gnu++20) to keep code portable
set(CMAKE_CXX_EXTENSIONS OFF) 

# Exports the compile commands for clang LSP to pick up
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


# ==========================================
# 1. CORE LIBRARY
# ==========================================
# Compile your source files into a library. 
# If you add more .cpp files in src/, add them here.
add_library(OrderbookLib 
    src/orderbook/orderbook.cpp
    src/orderbook/price_level.cpp
)

# Tell CMake where to find the headers. 
# PUBLIC means anything linking to OrderbookLib also gets this include path.
target_include_directories(OrderbookLib PUBLIC include)

if(MSVC)
    target_compile_options(OrderbookLib PRIVATE /W4 /WX)
else()
    target_compile_options(OrderbookLib PRIVATE -Wall -Wextra -Wpedantic -Werror)
endif()
# ==========================================
# 2. MAIN EXECUTABLE
# ==========================================
# Create your main application executable
add_executable(main_app main.cpp)

# Link the core library to your main app
target_link_libraries(main_app PRIVATE OrderbookLib)


# ==========================================
# 3. UNIT TESTING (GTEST)
# ==========================================
# Fetch Google Test automatically
include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        v1.14.0
)
# Prevent overriding the parent project's compiler/linker settings on Windows
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

# Create the test executable using your test source file
add_executable(unit_tests tests/unit/orderbook.cpp)

# Link gtest and your core library to the test executable
target_link_libraries(unit_tests PRIVATE 
    gtest_main 
    OrderbookLib
)

# Register the tests with CMake's test runner (CTest)
include(GoogleTest)
gtest_discover_tests(unit_tests)

# Benchmarking 
FetchContent_Declare(
  googlebenchmark
  GIT_REPOSITORY https://github.com/google/benchmark.git
  GIT_TAG        v1.8.3
)

# Disable benchmark's internal tests and installation to speed up your build
set(BENCHMARK_ENABLE_TESTING OFF CACHE BOOL "Disable benchmark tests" FORCE)
set(BENCHMARK_ENABLE_INSTALL OFF CACHE BOOL "Disable benchmark install" FORCE)

FetchContent_MakeAvailable(googlebenchmark)

# Create the benchmark executable
# (Assuming you save the benchmark code from the previous example here)
add_executable(orderbook_benchmark tests/performance/orderbook.cpp)

# Link your core library and the Google Benchmark libraries
target_link_libraries(orderbook_benchmark PRIVATE 
    OrderbookLib 
    benchmark::benchmark 
    benchmark::benchmark_main # Provides the main() function automatically
)
