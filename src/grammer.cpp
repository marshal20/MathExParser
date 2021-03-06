#include "grammer.hpp"
#include "internalTypes.hpp"

namespace DEFINED
{
	const std::string BLANKCHARS = " \t";
	
	namespace CHARS
	{
		const std::string NUMBERS = "0123456789";
		const std::string AZ_SMALL = "abcdefghijklmnopqrstuvwxy";
		const std::string AZ_CAPITAL = "ABCDEFGHIJKLMNOPQRSTUVWXY";
	}

	const std::string NUMBER = CHARS::NUMBERS + ".";
	const std::string NAME = CHARS::AZ_SMALL + CHARS::AZ_CAPITAL + "_" + CHARS::NUMBERS;

	namespace BRACKETS
	{
		const std::string OPEN = "({[";
		const std::string CLOSE = ")}]";
	}

	const std::string DIVIDORS = ",";
	const std::string OPERATIONS = "+-*/^";

	const std::string OPERATORS = BRACKETS::OPEN + BRACKETS::CLOSE + DIVIDORS + OPERATIONS;
}

extern OperatorType get_operatorType(const Token& token)
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

MathOperationType get_mathOperationType(const Token& token)
{
	switch (token.innerText[0])
	{
	case '+': return MathOperationType::Plus; break;
	case '-': return MathOperationType::Minus; break;
	case '*': return MathOperationType::Multiply; break;
	case '/': return MathOperationType::Divide; break;
	case '^': return MathOperationType::Exponent; break;
	default: return MathOperationType::UNKNOWN; break;
	}
}

TokenType get_charType(const char c)
{
	if (DEFINED::OPERATORS.find(c) != std::string::npos)
		return TokenType::Operator;

	if (DEFINED::NUMBER.find(c) != std::string::npos)
		return TokenType::Number;

	if (DEFINED::NAME.find(c) != std::string::npos)
		return TokenType::Name;

	if (DEFINED::BLANKCHARS.find(c) != std::string::npos)
		return TokenType::UNKNOWN;

	throw std::runtime_error("Undefined character.");
}

bool is_new_token(const TokenType lastType, const char curC)
{
	// if last character is blank
	if (lastType == TokenType::UNKNOWN)
		return true;
	// if current character is blank
	if (DEFINED::BLANKCHARS.find(curC) != std::string::npos)
		return true;

	if (lastType == TokenType::Operator)
		return true;

	if (lastType == TokenType::Name && DEFINED::NAME.find(curC) != std::string::npos)
		return false;

	if (lastType == TokenType::Number && DEFINED::NUMBER.find(curC) != std::string::npos)
		return false;
	else if (lastType == TokenType::Number && DEFINED::NAME.find(curC) != std::string::npos)
		throw std::runtime_error("Unexpecter name character after a number.");

	return true;
}