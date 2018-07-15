#include "parser.hpp"
#include "utils.hpp"
#include <string>
#include <iostream>

OperatorType char_to_operatorType(const char charachter)
{
	for (auto def : DEFINED_OPERATORS)
		if (charachter == def.charachter)
			return def.type;

	return OperatorType::UNKNOWN;
}

char operatorType_to_char(const OperatorType oType)
{
	for (auto def : DEFINED_OPERATORS)
		if (oType == def.type)
			return def.charachter;

	return '0';
}

std::vector<Token> parse_equation(std::string equation)
{
	std::string originalEquation = equation; // just for debug perpos
	int index = 0;
	std::vector<Token> temporary;
	while (equation.length() != 0)
	{
		Token token;
		token.type = TokenType::UNKNOWN;
		token.index = index;

		if (equation[0] == ' ') { index += 1; equation = equation.substr(1); } // skip spaces

																			   // Operator
		OperatorType oType = char_to_operatorType(equation[0]);
		if (oType != OperatorType::UNKNOWN)
		{
			token.type = TokenType::Operator;
			token.value.oType = oType;
			temporary.push_back(token);
			index += 1;
			equation = equation.substr(1);
			continue;
		}

		unsigned int processed;
		double number = std::stod(equation, &processed);
		if (processed != 0) // number
		{
			token.type = TokenType::Number;
			token.value.number = number;
			temporary.push_back(token);
			index += processed;
			equation = equation.substr(processed);
			continue;
		}
	}

	return temporary;
}
