#include <iostream>
#include <string>
#include <vector>
#include "internalTypes.hpp"

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
	std::vector<Token> temporary;
	while(equation.length() != 0)
	{
		Token token;
		token.type = TokenType::UNKNOWN;

		// Operator
		OperatorType oType = char_to_operatorType(equation[0]);
		if (oType != OperatorType::UNKNOWN)
		{
			token.type = TokenType::Operator;
			token.value.oType = oType;
			temporary.push_back(token);
			equation = equation.substr(1);
			continue;
		}

		unsigned int processed;
		double number = std::stod(equation, &processed);
		if (processed != 0) // number
		{
			Token curToken = {TokenType::Number, number };
			temporary.push_back(curToken);
			equation = equation.substr(processed);
			continue;
		}
	}

	return temporary;
}

void print_token(const Token& token)
{
	std::string typeName = (token.type == TokenType::Number) ? "Number" : "Operator";
	std::cout << "- Token: type: " << typeName << ", value: ";

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

int main()
{
	std::string equation = "1.2+3.5*1.1-3/2";
	auto tokenList = parse_equation(equation);
	print_tokenList(tokenList);

	std::cin.get();
	return 0;
}