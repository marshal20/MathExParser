#include <iostream>
#include <string>
#include "mathparser.hpp"
#include "utils.hpp"

int main()
{
	std::string equation = "5 * max(0, sin(30*pi/180)) + 2^3*e";

	Node* head = equation_to_tree(equation);

	print_node(head);
	std::cout << std::endl;
	std::cout << "- Value of equation: " << equation << " = " << evaluate(head) << std::endl;
	std::cin.get();

	free_node(head);

	return 0;
}