cmake_minimum_required(VERSION 3.5)
project(Complex)

set(CMAKE_C_STANDARD 11)

set(SOURCE_FILES ComplexAdd.c Mycomplex.h ComlexSub.c ComplexMul.c ComlplexDiv.c)
add_library(MyComplex ${SOURCE_FILES})
