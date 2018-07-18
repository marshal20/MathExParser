#pragma once
#include <array>
#include <string>

enum class TokenType
{
	Number,
	Operator,
	Group,
	Name,
	UNKNOWN
};

enum class OperatorType
{
	plus = 1,
	minus,
	divide,
	multiply,

	openBracket,
	closeBracket,

	UNKNOWN
};

struct Token
{
	TokenType type;
	union
	{
		double number;
		OperatorType oType;
	} value;
	std::string innerText;
	int index;
};

struct OperatorDefinition
{
	char charachter;
	OperatorType type;
};

extern std::array<OperatorDefinition, 6> DEFINED_OPERATORS;

extern int get_token_order(const Token& token);