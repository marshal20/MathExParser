#include <iostream>
#include <string>
#include "parser.hpp"
#include "evaluate.hpp"
#include "lexer.hpp"
#include "tree.hpp"
#include "utils.hpp"

int main()
{
	std::string equation = "5 * max(0, sin(30*pi/180)) + 2";
	std::vector<char> parsed;
	parse(parsed, equation);

	std::vector<Token> tokenList;
	tokenize(tokenList, parsed);

	Node* head = create_tree(tokenList);

	print_node(head);
	std::cout << std::endl;
	std::cout << "- Value of equation: " << equation << " = " << evaluate(head) << std::endl;
	std::cin.get();

	free_node(head);

	return 0;
}