#include <iostream>
#include <string>
#include "parser.hpp"
#include "utils.hpp"

int main()
{
	std::string equation = "5*2+1+3+6+9*2-8";
	auto tokenList = parse_equation(equation);
	//print_tokenList(tokenList);

	Node* head = parse_tokenList(tokenList);
	print_node(head);

	std::cout << "- Value of equation: " << equation << " = " << evaluate(tokenList) << std::endl;

	std::cin.get();

	free_node(head);
	return 0;
}