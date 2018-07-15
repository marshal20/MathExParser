#include "internalTypes.hpp"

std::array<OperatorDefinition, 6> DEFINED_OPERATORS{ {
	{ '+', OperatorType::plus },
	{ '-', OperatorType::minus },
	{ '/', OperatorType::divide },
	{ '*', OperatorType::multiply },
	{ '(', OperatorType::openBracket },
	{ ')', OperatorType::closeBracket }
} };

int get_token_order(const Token& token)
{
	if (token.type == TokenType::Number)
		return 0;

	if (token.type == TokenType::Group)
		return 1;

	if (token.type == TokenType::Operator)
	{
		if (token.value.oType == OperatorType::divide)
			return 2;
		if (token.value.oType == OperatorType::multiply)
			return 3;
		if (token.value.oType == OperatorType::minus)
			return 4;
		if (token.value.oType == OperatorType::plus)
			return 5;
	}

	return -1;
}