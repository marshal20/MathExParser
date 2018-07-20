#pragma once
#include <string>
#include "internalTypes.hpp"

enum class OperatorType
{
	OpenBracket,
	CloseBracket,
	Dividor,
	Operation,
	UNKNOWN
};

enum class MathOperationType
{
	Plus,
	Minus,
	Multiply,
	Divide,
	UNKNOWN
};


extern OperatorType get_operatorType(const Token& token);
extern MathOperationType get_mathOperationType(const Token& token);
extern TokenType get_charType(const char c);
extern bool is_new_token(const TokenType lastType, const char curC);