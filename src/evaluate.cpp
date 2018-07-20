#include "evaluate.hpp"
#include "defined.hpp"
#include "lexer.hpp"
#include "grammer.hpp"
#include <string>

double plus(const Node* node)
{
	double value = 0;
	for (const Node* node : node->childList)
		value += evaluate(node);
	return value;
}

double minus(const Node* node)
{
	double value = evaluate(node->childList[0]);
	for (unsigned int i = 1; i < node->childList.size(); i++)
		value -= evaluate(node->childList[i]);
	return value;
}

double multiply(const Node* node)
{
	double value = evaluate(node->childList[0]);
	for (unsigned int i = 1; i < node->childList.size(); i++)
		value *= evaluate(node->childList[i]);
	return value;
}

double divide(const Node* node)
{
	double value = evaluate(node->childList[0]);
	for (unsigned int i = 1; i < node->childList.size(); i++)
		value /= evaluate(node->childList[i]);
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
	if (ffound != definedFunc.end()) {
		Args args;
		if (node->childList.size() == 0) return 1; // return if we have no groups
		for(const Node* cnode : node->childList[0]->childList)
			args.push_back(evaluate(cnode));
		return ffound->second(args);
	}

	// constant
	auto cfound = definedConst.find(node->token.innerText);
	if (cfound == definedConst.end()) return 1;

	double value = cfound->second;
	for (unsigned int i = 0; i < node->childList.size(); i++)
		value *= evaluate(node->childList[i]);
	return value;
}

double evaluate(const Node* node)
{
	switch (node->token.type) {
		case TokenType::Group: return group(node);
		case TokenType::Name: return name(node);
		case TokenType::Number: return number(node);
		case TokenType::Operator:
			switch (getMathOperationType(node->token))
			{
			case MathOperationType::Plus: return plus(node);
			case MathOperationType::Minus: return minus(node);
			case MathOperationType::Multiply: return multiply(node);
			case MathOperationType::Divide: return divide(node);
			}
		default:
			throw std::exception("Can't evaluate node");
	}
	
	return 0.0;
}