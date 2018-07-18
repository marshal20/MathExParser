#include "evaluate.hpp"
#include "defined.hpp"

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
	for (int i = 1; i < node->childList.size(); i++)
		value -= evaluate(node->childList[i]);
	return value;
}

double multiply(const Node* node)
{
	double value = evaluate(node->childList[0]);
	for (int i = 1; i < node->childList.size(); i++)
		value *= evaluate(node->childList[i]);
	return value;
}

double divide(const Node* node)
{
	double value = evaluate(node->childList[0]);
	for (int i = 1; i < node->childList.size(); i++)
		value /= evaluate(node->childList[i]);
	return value;
}

double number(const Node* node)
{
	double value = node->token.value.number;
	for (int i = 0; i < node->childList.size(); i++)
		value *= evaluate(node->childList[i]);
	return value;
}

double group(const Node* node)
{
	double value = 1;
	for (int i = 0; i < node->childList.size(); i++)
		value *= evaluate(node->childList[i]);
	return value;
}

double name(const Node* node)
{
	// function
	auto ffound = definedFunc.find(node->token.innerText);
	if (ffound != definedFunc.end()) {
		Args args;
		args.push_back(evaluate(node->childList[0]));
		return ffound->second(args);
	}

	// constant
	auto cfound = definedConst.find(node->token.innerText);
	if (cfound == definedConst.end()) return 1;

	double value = cfound->second;
	for (int i = 0; i < node->childList.size(); i++)
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
			switch (node->token.value.oType)
			{
			case OperatorType::plus: return plus(node);
			case OperatorType::minus: return minus(node);
			case OperatorType::multiply: return multiply(node);
			case OperatorType::divide: return divide(node);
			}
	}
	
	return 0.0;
}