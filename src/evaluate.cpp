#include "evaluate.hpp"

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
	return node->token.value.number;
}

double evaluate(const Node* node)
{
	switch (node->token.type) {
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