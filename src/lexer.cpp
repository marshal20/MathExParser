#include "lexer.hpp"
#include "grammer.hpp"
#include <exception>


void updateLevels(std::vector<Token>& tokenList)
{
	int level = 0;
	
	for (Token& token : tokenList)
	{
		token.level = level;
		if (token.type != TokenType::Operator) continue; // skip if the type isn't operator

		
		if (get_operatorType(token) == OperatorType::OpenBracket)
		{
			level++;
		}
		else if (get_operatorType(token) == OperatorType::CloseBracket)
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
	TokenType firstTokenType = TokenType::UNKNOWN;
	int firstIndex = 0;

	for (unsigned int i = 0; i < parsed.size(); i++)
	{
		const char curC = parsed[i];
		const TokenType curType = get_charType(curC);

		if (is_new_token(firstTokenType, curC) || innerText.length() == 0)
		{
			if(innerText != "")
				tokenList.push_back({ firstTokenType, innerText, firstIndex, 0 });
			innerText.clear();
			if (curType != TokenType::UNKNOWN) // only set the new charachter if not Blanc
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