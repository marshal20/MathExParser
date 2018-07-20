#include "lester.hpp"
#include <exception>

namespace DEFINED
{
	const std::string OPERATORS = "(),+-*/";
	const std::string BLANCHCHARS = " \t";
}



bool isCharNumber(const char c)
{
	return (c - '0' >= 0 && c - '0' <= 9);
}

Type getCharType(const char c)
{
	if (DEFINED::OPERATORS.find(c) != std::string::npos)
		return Type::Operator;

	if (isCharNumber(c))
		return Type::Number;

	return Type::Name;
}

void lexer(std::vector<Token>& out, const std::vector<char>& parsed)
{
	std::string innerText;
	Type firstTokenType;
	int firstIndex = 0;
	int level = 0;

	for (int i = 0; i < parsed.size(); i++)
	{
		const char curC = parsed[i];
		const Type curType = getCharType(curC);

		// handle Blanck charachters
		if (DEFINED::BLANCHCHARS.find(curC) != std::string::npos)
		{
			if(innerText.length() != 0)
				out.push_back({ firstTokenType, innerText, firstIndex, level });
			innerText.clear();
			continue;
		}

		// this is the start of a new token
		if (innerText.length() == 0)
		{
			innerText += curC;
			firstTokenType = curType;
			firstIndex = i;
			continue;
		}
		
		switch (firstTokenType)
		{

		case Type::Number:
			if (curType == Type::Number)
			{
				innerText += curC;
				continue;
			}
			else if (curC == '.')
			{
				innerText += curC;
				continue;
			}
			else if (curType == Type::Name)
			{
				throw std::exception("Unexpecter charachter after a number.");
			}
			break;

		case Type::Name:
			if (curType == Type::Name || curType == Type::Number)
			{
				innerText += curC;
				continue;
			}
			break;

		case Type::Operator:
			break;

		default:
			break;
		}

		// if nothing continued it means the current token is done
		// so we push the token to out, then we reanalize the curC
		out.push_back({ firstTokenType, innerText, firstIndex, level });
		innerText.clear();
		i--;
	}
}