#include "lexer.hpp"
#include <exception>

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
}

bool isOpenBracket(const Token& token)
{
	return (DEFINED::BRACKETS::OPEN.find(token.innerText) != std::string::npos);
}

bool isCloseBracket(const Token& token)
{
	return (DEFINED::BRACKETS::CLOSE.find(token.innerText) != std::string::npos);
}

bool isDividor(const Token& token)
{
	return (DEFINED::DIVIDORS.find(token.innerText) != std::string::npos);
}

Type getCharType(const char c)
{
	if (DEFINED::OPERATORS.find(c) != std::string::npos)
		return Type::Operator;

	if (DEFINED::NUMBER_ELSE.find(c) != std::string::npos)
		return Type::Number;

	if (DEFINED::NAME_ELSE.find(c) != std::string::npos)
		return Type::Name;

	if (DEFINED::BLANCHCHARS.find(c) != std::string::npos)
		return Type::UNKNOWN;

	throw std::exception("Undefined charachter.");
}

bool isNewToken(const Type lastType, const char curC)
{
	if (lastType == Type::UNKNOWN)
		return true;

	if (DEFINED::BLANCHCHARS.find(curC) != std::string::npos)
		return true;

	if (lastType == Type::Operator)
		return true;

	if (lastType == Type::Name && DEFINED::NAME_ELSE.find(curC) != std::string::npos)
		return false;
		
	if (lastType == Type::Number && DEFINED::NUMBER_ELSE.find(curC) != std::string::npos)
		return false;
	else if (lastType == Type::Number && DEFINED::NAME_ELSE.find(curC) != std::string::npos)
		throw std::exception("Unexpecter name charachter after a number.");

	return true;
}

void updateLevels(std::vector<Token>& tokenList)
{
	int level = 0;
	
	for (Token& token : tokenList)
	{
		token.level = level;
		if (token.type != Type::Operator) continue; // skip if the type isn't operator

		if (DEFINED::BRACKETS::OPEN.find(token.innerText) != std::string::npos)
		{
			level++;
		}
		else if (DEFINED::BRACKETS::CLOSE.find(token.innerText) != std::string::npos)
		{
			level--;
			token.level = level;
		}
	}

	if (level != 0)
		throw std::exception("Close bracket token wasn't found.");
}

void tokenize(std::vector<Token>& tokenList, const std::vector<char>& parsed)
{
	std::string innerText;
	Type firstTokenType = Type::UNKNOWN;
	int firstIndex = 0;

	for (int i = 0; i < parsed.size(); i++)
	{
		const char curC = parsed[i];
		const Type curType = getCharType(curC);

		if (isNewToken(firstTokenType, curC) || innerText.length() == 0)
		{
			if(innerText != "")
				tokenList.push_back({ firstTokenType, innerText, firstIndex, 0 });
			innerText = curC;
			firstTokenType = curType;
			firstIndex = i;
			continue;
		}
		else
		{
			innerText += curC;
			continue;
		}
	}

	// push the last token
	if (innerText.length() != 0)
		tokenList.push_back({ firstTokenType, innerText, firstIndex, 0 });

	// updating levels for all tokens
	updateLevels(tokenList);
}