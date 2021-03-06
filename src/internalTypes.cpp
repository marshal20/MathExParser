#include "internalTypes.hpp"
#include <string>
#include <exception>

int get_token_order(const Token& token)
{
	if (token.type == TokenType::Number)
		return 0;

	if (token.type == TokenType::Group)
		return 1;

	if (token.type == TokenType::Name)
		return 2;

	if (token.type == TokenType::Operator)
	{
		if (token.innerText == "^")
			return 3;
		if (token.innerText == "/")
			return 4;
		if (token.innerText == "*")
			return 5;
		if (token.innerText == "-")
			return 6;
		if (token.innerText == "+")
			return 7;
	}

	std::string error_msg = std::string("Unknown order of token: ") 
		+ token.innerText + ", index: " + std::to_string(token.index);
	throw std::runtime_error(error_msg.c_str());
}
