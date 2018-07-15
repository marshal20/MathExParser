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

double evaluate(std::vector<Token> tokenList)
{
	// step(1): do all multiplication and devide
	bool md_done = false;
	while (!md_done)
	{
		std::vector<Token> outPut;
		md_done = true;
		outPut.push_back(tokenList[0]);
		for (int i = 1; i < tokenList.size(); i++)
		{
			outPut.push_back(tokenList[i]);
			if (tokenList[i].type == TokenType::Operator)
			{
				if (!(tokenList[i].value.oType == OperatorType::multiply || tokenList[i].value.oType == OperatorType::devid))
					continue;
				double no1 = tokenList[i - 1].value.number;
				double no2 = tokenList[i + 1].value.number;
				double result;
				if (tokenList[i].value.oType == OperatorType::multiply)
					result = no1*no2;
				if (tokenList[i].value.oType == OperatorType::devid)
					result = no1 / no2;

				Token& lastToken = outPut.back();
				lastToken.type = TokenType::Number;
				lastToken.value.number = result;
				md_done = false;
				for (int j = i + 2; j < tokenList.size(); j++) outPut.push_back(tokenList[j]);
				break;
			}
		}
		tokenList = outPut;
	}

	return tokenList.back().value.number;
}