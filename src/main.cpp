#include <iostream>
#include <string>
#include "parser.hpp"
#include "utils.hpp"
#include "lester.hpp"
#include "evaluate.hpp"

int main()
{
	std::string equation = "5*pi(3+1)+2";
	auto tokenList = parse_equation(equation);

	Node* head = parse_tokenList(tokenList);
	print_node(head);

	std::cout << "- Value of equation: " << equation << " = " << evaluate(head) << std::endl;

	std::cin.get();

	free_node(head);
	return 0;
}