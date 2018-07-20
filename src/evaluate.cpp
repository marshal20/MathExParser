#include "evaluate.hpp"
#include "defined.hpp"
#include "lexer.hpp"
#include "grammer.hpp"
#include <string>

void check_operator_values(const Node* node)
{
	if (node->childList.size() < 2)
	{
		std::string error_msg =
			std::string("Operator [") + node->token.innerText + "] can't be evaluated with less than 2 values, index: "
			+ std::to_string(node->token.index);
		throw std::runtime_error(error_msg.c_str());
	}
	
}

double plus(const Node* node)
{
	check_operator_values(node);

	double value = 0;
	for (const Node* node : node->childList)
		value += evaluate(node);
	return value;
}

double minus(const Node* node)
{
	check_operator_values(node);

	double value = evaluate(node->childList[0]);
	for (unsigned int i = 1; i < node->childList.size(); i++)
		value -= evaluate(node->childList[i]);
	return value;
}

double multiply(const Node* node)
{
	check_operator_values(node);

	double value = evaluate(node->childList[0]);
	for (unsigned int i = 1; i < node->childList.size(); i++)
		value *= evaluate(node->childList[i]);
	return value;
}

double divide(const Node* node)
{
	check_operator_values(node);

	double value = evaluate(node->childList[0]);
	for (unsigned int i = 1; i < node->childList.size(); i++)
		value /= evaluate(node->childList[i]);
	return value;
}

double exponent(const Node* node)
{
	check_operator_values(node);

	double value = evaluate(node->childList[0]);
	for (unsigned int i = 1; i < node->childList.size(); i++)
		value = std::pow(value, evaluate(node->childList[i]));
	return value;
}

double number(const Node* node)
{
	double value = std::stod(node->token.innerText);
	for (unsigned int i = 0; i < node->childList.size(); i++)
		value *= evaluate(node->childList[i]);
	return value;
}

double group(const Node* node)
{
	double value = 1;
	for (unsigned int i = 0; i < node->childList.size(); i++)
		value *= evaluate(node->childList[i]);
	return value;
}

double name(const Node* node)
{
	// function
	auto ffound = definedFunc.find(node->token.innerText);
	if (ffound != definedFunc.end() && node->childList.size() != 0) {
		Args args;

		for(const Node* cnode : node->childList[0]->childList)
			args.push_back(evaluate(cnode));
		return ffound->second(args);
	}

	// constant
	auto cfound = definedConst.find(node->token.innerText);
	if (cfound != definedConst.end())
	{
		double value = cfound->second;
		for (unsigned int i = 0; i < node->childList.size(); i++)
			value *= evaluate(node->childList[i]);
		return value;
	}

	std::string error_msg = std::string("Undefined function or constant name: ")
		+ node->token.innerText + ", index: " + std::to_string(node->token.index);
	throw std::runtime_error(error_msg.c_str());
}

double evaluate(const Node* node)
{
	switch (node->token.type) {
		case TokenType::Group: return group(node);
		case TokenType::Name: return name(node);
		case TokenType::Number: return number(node);
		case TokenType::Operator:
			switch (get_mathOperationType(node->token))
			{
			case MathOperationType::Plus: return plus(node);
			case MathOperationType::Minus: return minus(node);
			case MathOperationType::Multiply: return multiply(node);
			case MathOperationType::Divide: return divide(node);
			case MathOperationType::Exponent: return exponent(node);
			}
		default:
			std::string error_msg = std::string("Can't evaluate node: ") + node->token.innerText 
				+ ", index: " + std::to_string(node->token.index);
			throw std::runtime_error(error_msg.c_str());
	}
	
	return 0.0;
}