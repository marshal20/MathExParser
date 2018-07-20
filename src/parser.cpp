#include "parser.hpp"
//#include "utils.hpp"
#include <string>
#include <iostream>
#include <regex>

/*
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

// the name shouldn't start with numbers
std::string getName(std::string full)
{
	std::regex azNamerx("^([a-zA-z][a-zA-z0-9]*)");
	std::smatch azMatch;
	std::regex_search(full, azMatch, azNamerx);
	if (azMatch.size() >= 1) return azMatch[0];
	return "";
}

std::vector<Token> parse_equation(std::string equation)
{
	std::string originalEquation = equation; // just for debug perpos
	int index = 0;
	int level = 0;
	std::vector<Token> temporary;
	while (equation.length() != 0)
	{
		Token token;
		token.type = TokenType::UNKNOWN;
		token.index = index;
		token.level = level;

		if (equation[0] == ' ') { index += 1; equation = equation.substr(1); } // skip spaces

		// Operator
		OperatorType oType = char_to_operatorType(equation[0]);
		if (oType != OperatorType::UNKNOWN)
		{
			// level managing (Brackets)
			if (oType == OperatorType::openBracket) level++;
			else if (oType == OperatorType::closeBracket) level--;
			if (oType == OperatorType::closeBracket) token.level = level;

			token.type = TokenType::Operator;
			token.value.oType = oType;
			token.innerText = equation[0];
			temporary.push_back(token);
			index += 1;
			equation = equation.substr(1);
			continue;
		}

		// function or constant
		std::string fname = getName(equation);
		if (fname != "")
		{
			token.type = TokenType::Name;
			token.innerText = fname;
			temporary.push_back(token);
			index += fname.length();
			equation = equation.substr(fname.length());
			continue;
		}

		size_t processed;
		double number = std::stod(equation, &processed);
		if (processed != 0) // number
		{
			token.type = TokenType::Number;
			token.value.number = number;
			token.innerText = std::to_string(number);
			temporary.push_back(token);
			index += processed;
			equation = equation.substr(processed);
			continue;
		}
	}

	return temporary;
}*/


void parse(std::vector<char>& out, const std::string& equation)
{
	out.reserve(equation.length());
	for (const char c : equation)
		out.push_back(c);
}
