#pragma once
#include <array>
#include <string>

enum class TokenType
{
	Number,
	Operator,
	Name,
	Group,
	UNKNOWN
};

struct Token
{
	TokenType type;
	std::string innerText;
	int index;
	int level;
};


extern int get_token_order(const Token& token);