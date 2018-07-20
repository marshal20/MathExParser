cmake_minimum_required(VERSION 3.1)

project(MathExParser)

set(SRC 
		src/main.cpp

		src/internalTypes.hpp
		src/internalTypes.cpp
		src/defined.hpp
		src/defined.cpp
		src/grammer.hpp
		src/grammer.cpp

		src/parser.hpp
		src/parser.cpp
		src/lexer.hpp
		src/lexer.cpp

		src/node.hpp
		src/node.cpp
		src/tree.hpp
		src/tree.cpp

		src/evaluate.hpp
		src/evaluate.cpp

		src/utils.hpp
		src/utils.cpp
		)
		
add_executable(MathExParser ${SRC})