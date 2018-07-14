cmake_minimum_required(VERSION 3.1)

project(MathExParser)

set(SRC 
		src/main.cpp
		src/internalTypes.hpp
		src/internalTypes.cpp
		src/parser.hpp
		src/parser.cpp
		)

add_executable(MathExParser ${SRC})