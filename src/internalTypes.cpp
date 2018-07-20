#include "internalTypes.hpp"

/*
std::array<OperatorDefinition, 7> DEFINED_OPERATORS{ {
	{ '+', OperatorType::plus },
	{ '-', OperatorType::minus },
	{ '/', OperatorType::divide },
	{ '*', OperatorType::multiply },
	{ '(', OperatorType::openBracket },
	{ ')', OperatorType::closeBracket },
	{ ',', OperatorType::comma }
} };

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
		if (token.value.oType == OperatorType::divide)
			return 3;
		if (token.value.oType == OperatorType::multiply)
			return 4;
		if (token.value.oType == OperatorType::minus)
			return 5;
		if (token.value.oType == OperatorType::plus)
			return 6;
	}

	return -1;
}
*/