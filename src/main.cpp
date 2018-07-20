#include <iostream>
#include <string>
#include "parser.hpp"
//#include "lester.hpp"
//#include "utils.hpp"
//#include "lester.hpp"
//#include "evaluate.hpp"
#include "lexer.hpp"

int main()
{
	std::string equation = "5.5* max(0,sin(2))+2";
	std::vector<char> parsed;
	parse(parsed, equation);
	std::vector<Token> tokenList;
	tokenize(tokenList, parsed);
	Node* head = parse_tokenList(tokenList);

	/*auto tokenList = parse_equation(equation);

	Node* head = parse_tokenList(tokenList);
	print_node(head);

	std::cout << "- Value of equation: " << equation << " = " << evaluate(head) << std::endl;

	std::cin.get();

	free_node(head);*/
	return 0;
}