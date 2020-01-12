cmake_minimum_required(VERSION 3.10)
project(ComplexMachine)

set(CMAKE_CXX_STANDARD 20)

file(GLOB Complex "Complex/*.h" "Complex/*.cpp")
file(GLOB Computer "Computer/*.h" "Computer/*.cpp")
file(GLOB Polynomial "Polynomial/*.h" "Polynomial/*.cpp")
file(GLOB Bash "Bash/*.h" "Bash/*.cpp")
file(GLOB Test "Test/*.h" "Test/*.cpp")

add_library(Complex SHARED ${Complex})

add_library(Computer SHARED ${Computer})
target_link_libraries(Computer Complex)

add_library(Polynomial SHARED ${Polynomial})
target_link_libraries(Polynomial Complex)

add_executable(ComplexMachine-Test ${Test})
target_link_libraries(ComplexMachine-Test Complex Polynomial)

add_executable(ComplexMachine-Bash ${Bash})
target_link_libraries(ComplexMachine-Bash Complex Computer Polynomial)
