#include "utils.hpp"
#include "parser.hpp"
#include <iostream>
#include <string>

void print_token(const Token& token)
{
	std::string typeName = (token.type == TokenType::Number) ? "Number" : "Operator";
	std::cout << "- Token: index(" << token.index << "), type: " << typeName << ", value: ";

	if (token.type == TokenType::Number)
		std::cout << token.value.number << std::endl;
	else
		std::cout << operatorType_to_char(token.value.oType) << std::endl;
}

void print_tokenList(const std::vector<Token>& tokenList)
{
	for (const Token& token : tokenList)
		print_token(token);
}

void print_node(Node* node, std::string offset)
{
	std::cout << offset;
	print_token(node->token);
	offset += "\t";
	if (node->cfirst)
		print_node(node->cfirst, offset);
	if (node->csecond)
		print_node(node->csecond, offset);
}