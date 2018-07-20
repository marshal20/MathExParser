#pragma once
#include <array>
#include <string>

enum class Type
{
	Number,
	Operator,
	Name
};

struct Token
{
	Type type;
	std::string innerText;
	int index;
	int level;
};

/*struct OperatorDefinition
{
	char charachter;
	OperatorType type;
};

extern std::array<OperatorDefinition, 7> DEFINED_OPERATORS;
*/
extern int get_token_order(const Token& token);