#include <iostream>
#include <string>
#include "parser.hpp"


int main()
{
	std::string equation = "3*5/3/5";
	auto tokenList = parse_equation(equation);
	print_tokenList(tokenList);

	std::cout << "- Value of equation: " << equation << " = " << evaluate(tokenList) << std::endl;

	std::cin.get();
	return 0;
}