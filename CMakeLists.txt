cmake_minimum_required(VERSION 3.14)
project(OrderbookProject CXX)

# Require C++17 (or change to 20 if you prefer)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

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