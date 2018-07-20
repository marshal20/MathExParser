#include "grammer.hpp"
#include "internalTypes.hpp"

namespace DEFINED
{
	const std::string OPERATORS = "(){}[],+-*/";
	const std::string BLANCHCHARS = " \t";

	const std::string NUMBER_FIRST = "0123456789";
	const std::string NUMBER_ELSE = "0123456789.";
	const std::string NAME_FIRST = "abcdefghijklmnopqrstuvwxyABCDEFGHIJKLMNOPQRSTUVWXY_";
	const std::string NAME_ELSE = "abcdefghijklmnopqrstuvwxyABCDEFGHIJKLMNOPQRSTUVWXY_0123456789.";

	namespace BRACKETS
	{
		const std::string OPEN = "({[";
		const std::string CLOSE = ")}]";
	}

	const std::string DIVIDORS = ",";
	const std::string OPERATIONS = "+-*/";
}

extern OperatorType getOperatorType(const Token& token)
{
	if (DEFINED::BRACKETS::OPEN.find(token.innerText) != std::string::npos)
		return OperatorType::OpenBracket;

	if (DEFINED::BRACKETS::CLOSE.find(token.innerText) != std::string::npos)
		return OperatorType::CloseBracket;

	if (DEFINED::DIVIDORS.find(token.innerText) != std::string::npos)
		return OperatorType::Dividor;

	if (DEFINED::OPERATIONS.find(token.innerText) != std::string::npos)
		return OperatorType::Operation;

	return OperatorType::UNKNOWN;
}

MathOperationType getMathOperationType(const Token& token)
{
	switch (token.innerText[0])
	{
	case '+': return MathOperationType::Plus; break;
	case '-': return MathOperationType::Minus; break;
	case '*': return MathOperationType::Multiply; break;
	case '/': return MathOperationType::Divide; break;
	default: return MathOperationType::UNKNOWN; break;
	}
}

TokenType getCharType(const char c)
{
	if (DEFINED::OPERATORS.find(c) != std::string::npos)
		return TokenType::Operator;

	if (DEFINED::NUMBER_ELSE.find(c) != std::string::npos)
		return TokenType::Number;

	if (DEFINED::NAME_ELSE.find(c) != std::string::npos)
		return TokenType::Name;

	if (DEFINED::BLANCHCHARS.find(c) != std::string::npos)
		return TokenType::UNKNOWN;

	throw std::exception("Undefined charachter.");
}

bool isNewToken(const TokenType lastType, const char curC)
{
	if (lastType == TokenType::UNKNOWN)
		return true;

	if (DEFINED::BLANCHCHARS.find(curC) != std::string::npos)
		return true;

	if (lastType == TokenType::Operator)
		return true;

	if (lastType == TokenType::Name && DEFINED::NAME_ELSE.find(curC) != std::string::npos)
		return false;

	if (lastType == TokenType::Number && DEFINED::NUMBER_ELSE.find(curC) != std::string::npos)
		return false;
	else if (lastType == TokenType::Number && DEFINED::NAME_ELSE.find(curC) != std::string::npos)
		throw std::exception("Unexpecter name charachter after a number.");

	return true;
}