cmake_minimum_required(VERSION 3.21)
project(Matrix)

set(CMAKE_CXX_STANDARD 17)

add_executable(Matrix main.cpp src/BigInteger.cpp include/BigInteger.h src/Rational.cpp include/Rational.h src/Residue.cpp include/Residue.h src/Matrix.cpp include/Matrix.h)
