cmake_minimum_required(VERSION 3.1)

project(MathExParser)

set(SRC 
		src/main.cpp
		src/internalTypes.hpp
		src/internalTypes.cpp
		src/parser.hpp
		src/parser.cpp
#		src/node.hpp
#		src/node.cpp
#		src/utils.hpp
#		src/utils.cpp
#		src/lester.hpp
#		src/lester.cpp
#		src/evaluate.hpp
#		src/evaluate.cpp
#		src/defined.hpp
#		src/defined.cpp
		src/lexer.hpp
		src/lexer.cpp
		)
		
add_executable(MathExParser ${SRC})