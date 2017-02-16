# CMake generated Testfile for 
# Source directory: /Users/SanLee/Desktop/EECS211/hw3/eecs211-hw03
# Build directory: /Users/SanLee/Desktop/EECS211/hw3/eecs211-hw03/cmake-build-debug
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(Test_circle_test "circle_test")
add_test(Test_prime_test "prime_test")
subdirs(.eecs211/lib/unittest-cpp)
subdirs(.eecs211/lib/graphics)
