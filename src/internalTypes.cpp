#include "internalTypes.hpp"


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

	throw std::exception("Unknown order of token.");
}
