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


extern OperatorType getOperatorType(const Token& token);
extern MathOperationType getMathOperationType(const Token& token);
extern TokenType getCharType(const char c);
extern bool isNewToken(const TokenType lastType, const char curC);