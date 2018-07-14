#include "internalTypes.hpp"

std::array<OperatorDefinition, 4> DEFINED_OPERATORS{ {
	{ '+', OperatorType::plus },
	{ '-', OperatorType::minus },
	{ '/', OperatorType::devid },
	{ '*', OperatorType::multiply }
} };

int get_token_order(const Token& token)
{
	if (token.type == TokenType::Number)
		return 0;

	if (token.type == TokenType::Operator)
	{
		if (token.value.oType == OperatorType::multiply || token.value.oType == OperatorType::devid)
			return 1;
		if (token.value.oType == OperatorType::plus || token.value.oType == OperatorType::minus)
			return 2;
	}

	return -1;
}