#include "mathparser.hpp"
#include "parser.hpp"
#include "lexer.hpp"

Node* equation_to_tree(const std::string& equation)
{
	std::vector<char> parsed;
	parse(parsed, equation);

	std::vector<Token> tokenList;
	tokenize(tokenList, parsed);

	return create_tree(tokenList);
}