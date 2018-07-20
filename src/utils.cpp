#include "utils.hpp"
#include "parser.hpp"
#include <iostream>
#include <string>

std::string strtokenType(TokenType tokenType)
{
	switch (tokenType)
	{
	case TokenType::Number: return "Number";
	case TokenType::Operator: return "Operator";
	case TokenType::Group: return "Group";
	case TokenType::Name: return "Name";
	case TokenType::UNKNOWN: return "UNKNOWN";
	default: return "UNDEFINED";
	}
}

std::string strtokenvalue(const Token& token)
{
	switch (token.type)
	{
	case TokenType::Number: return token.innerText;
	case TokenType::Operator: return token.innerText;
	case TokenType::Name: return token.innerText;
	default: return "";
	}
}

void print_token(const Token& token)
{
	std::string typeName = strtokenType(token.type);
	std::string value = strtokenvalue(token);
	std::cout << "- Token: index(" << token.index << "), type: " << typeName;
	if (value != "")
		std::cout << ", value: " << value;
	std::cout << std::endl;
}

void print_tokenList(const std::vector<Token>& tokenList)
{
	for (const Token& token : tokenList)
		print_token(token);
}

void print_node(const Node* node, std::string offset)
{
	std::cout << offset;
	print_token(node->token);
	offset += "\t";

	// print all the child
	for (const Node* node : node->childList)
		print_node(node, offset);
}