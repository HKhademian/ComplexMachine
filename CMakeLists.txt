cmake_minimum_required(VERSION 3.10)
project(ComplexMachine)

set(CMAKE_CXX_STANDARD 20)

file(GLOB Complex "Complex/*.h" "Complex/*.cpp")
file(GLOB Computer "Computer/*.h" "Computer/*.cpp")
file(GLOB Program "./*.h" "./*.cpp")

add_executable(ComplexMachine ${Complex} ${Computer} ${Program})
