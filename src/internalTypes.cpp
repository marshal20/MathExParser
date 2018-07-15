#include "internalTypes.hpp"

std::array<OperatorDefinition, 6> DEFINED_OPERATORS{ {
	{ '+', OperatorType::plus },
	{ '-', OperatorType::minus },
	{ '/', OperatorType::devid },
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
		if (token.value.oType == OperatorType::multiply || token.value.oType == OperatorType::devid)
			return 2;
		if (token.value.oType == OperatorType::plus || token.value.oType == OperatorType::minus)
			return 3;
	}

	return -1;
}