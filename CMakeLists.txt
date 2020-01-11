cmake_minimum_required(VERSION 3.10)
project(ComplexMachine)

set(CMAKE_CXX_STANDARD 20)

file(GLOB Complex "Complex/*.h" "Complex/*.cpp")
file(GLOB Computer "Computer/*.h" "Computer/*.cpp")
file(GLOB Polynomial "Polynomial/*.h" "Polynomial/*.cpp")
file(GLOB Bash "Bash/*.h" "Bash/*.cpp")
file(GLOB Test "Test/*.h" "Test/*.cpp")

add_executable(ComplexMachine-Bash ${Complex} ${Computer} ${Polynomial} ${Bash})
add_executable(ComplexMachine-Test ${Complex} ${Computer} ${Polynomial} ${Test})
