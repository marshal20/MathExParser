#pragma once
#include <array>

enum class TokenType
{
	Number,
	Operator,
	UNKNOWN
};

enum class OperatorType
{
	plus = 1,
	minus,
	devid,
	multiply,
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
};

struct OperatorDefinition
{
	char charachter;
	OperatorType type;
};

extern std::array<OperatorDefinition, 4> DEFINED_OPERATORS;
