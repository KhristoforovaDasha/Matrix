cmake_minimum_required(VERSION 3.21)
project(Matrix)

set(CMAKE_CXX_STANDARD 17)

add_executable(Matrix main.cpp BigInteger.cpp BigInteger.h Rational.cpp Rational.h Residue.cpp Residue.h Matrix.cpp Matrix.h)
