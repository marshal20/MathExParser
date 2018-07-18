#pragma once
#include <array>

enum class TokenType
{
	Number,
	Operator,
	Group,
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
	int index;
};

struct OperatorDefinition
{
	char charachter;
	OperatorType type;
};

extern std::array<OperatorDefinition, 6> DEFINED_OPERATORS;

extern int get_token_order(const Token& token);