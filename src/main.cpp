#include <iostream>
#include <string>
#include <vector>

enum class TokenType
{
	Number,
	Operator,
	UNKNOWN
};

enum class OperatorType
{
	plus=1,
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

OperatorType char_to_operatorType(const char charachter)
{
	OperatorType oType = OperatorType::UNKNOWN;

	switch (charachter) 
	{
	case '+': oType = OperatorType::plus;		break;
	case '-': oType = OperatorType::minus;		break;
	case '/': oType = OperatorType::devid;		break;
	case '*': oType = OperatorType::multiply;	break;
	default:  oType = OperatorType::UNKNOWN;	break;
	}
	
	return oType;
}

char operatorType_to_char(const OperatorType oType)
{
	char charachter = '0';
	switch (oType)
	{
	case OperatorType::plus:		charachter = '+'; break;
	case OperatorType::minus:		charachter = '-'; break;
	case OperatorType::devid:		charachter = '/'; break;
	case OperatorType::multiply:	charachter = '*'; break;
	default:						charachter = '0'; break;
	}
}

std::vector<Token> parse_equation(std::string equation)
{
	std::vector<Token> temporary;
	while(equation.length() != 0)
	{
		Token token;
		token.type = TokenType::UNKNOWN;

		// Operator
		OperatorType oType = char_to_operatorType(equation[0]);
		if (oType != OperatorType::UNKNOWN)
		{
			token.type = TokenType::Operator;
			token.value.oType = oType;
			temporary.push_back(token);
			equation = equation.substr(1);
			continue;
		}

		unsigned int processed;
		double number = std::stod(equation, &processed);
		if (processed != 0) // number
		{
			Token curToken = {TokenType::Number, number };
			temporary.push_back(curToken);
			equation = equation.substr(processed);
			continue;
		}
	}

	return temporary;
}

void print_tokenList(const std::vector<Token>& tokenList)
{
	for (const Token& token : tokenList)
	{
		std::string typeName = (token.type == TokenType::Number)? "Number" : "Operator";
		std::cout << "- Token: type: " << typeName << ", value: ";
		if (token.type == TokenType::Number)
			std::cout << token.value.number << std::endl;
		else
			std::cout << operatorType_to_char(token.value.oType) << std::endl;
	}
}

int main()
{
	std::string equation = "2+2";
	auto tokenList = parse_equation(equation);
	print_tokenList(tokenList);

	std::cin.get();
	return 0;
}