#include "parser.hpp"
#include "utils.hpp"
#include <string>
#include <iostream>

OperatorType char_to_operatorType(const char charachter)
{
	for (auto def : DEFINED_OPERATORS)
		if (charachter == def.charachter)
			return def.type;

	return OperatorType::UNKNOWN;
}

char operatorType_to_char(const OperatorType oType)
{
	for (auto def : DEFINED_OPERATORS)
		if (oType == def.type)
			return def.charachter;

	return '0';
}

std::vector<Token> parse_equation(std::string equation)
{
	std::string originalEquation = equation; // just for debug perpos
	int index = 0;
	std::vector<Token> temporary;
	while (equation.length() != 0)
	{
		Token token;
		token.type = TokenType::UNKNOWN;
		token.index = index;

		if (equation[0] == ' ') { index += 1; equation = equation.substr(1); } // skip spaces

																			   // Operator
		OperatorType oType = char_to_operatorType(equation[0]);
		if (oType != OperatorType::UNKNOWN)
		{
			token.type = TokenType::Operator;
			token.value.oType = oType;
			temporary.push_back(token);
			index += 1;
			equation = equation.substr(1);
			continue;
		}

		unsigned int processed;
		double number = std::stod(equation, &processed);
		if (processed != 0) // number
		{
			token.type = TokenType::Number;
			token.value.number = number;
			temporary.push_back(token);
			index += processed;
			equation = equation.substr(processed);
			continue;
		}
	}

	return temporary;
}

Node* parse_tokenList(const std::vector<Token>& tokenList)
{
	if (tokenList.size() == 0) return nullptr;

	// preparing the first node
	Node* head = new Node;
	zero_node(head);
	head->token = tokenList[0];

	for (int i = 1; i < tokenList.size(); i++)
	{
		int order = get_token_order(tokenList[i]);
		int headorder = get_token_order((const Token&)*head);
		if (order > headorder && order != 0)
		{
			// replace the head, the old head becomes a child
			Node* newhead = new Node;
			zero_node(newhead);
			head = get_lowest_parent(head, order);
			replace_node(head, newhead);
			newhead->token = tokenList[i];
			newhead->cfirst = head;
			head = newhead;
		}
		else
		{
			// become a child of the current head
			Node* newchild = new Node;
			zero_node(newchild);
			newchild->parent = head;
			newchild->token = tokenList[i];
			addchild_node(head, newchild);

			head = newchild;
		}

		{ // print the tree every loop for debugging purpose
			Node* temp = head;
			while (temp->parent)
				temp = temp->parent;
			print_node(temp);
			std::cout << "---------------------------------------" << std::endl;
		}
	}

	// go up till the origin tree
	while (head->parent)
		head = head->parent;
}

Node* get_lowest_parent(Node* curnode, int order)
{
	while (curnode->parent)
	{
		if (get_token_order(curnode->parent->token) < order)
			curnode = curnode->parent;
		else
			break;
	}

	return curnode;
}

double evaluate(std::vector<Token> tokenList)
{
	// step(1): do all multiplication and devide
	bool md_done = false;
	while (!md_done)
	{
		std::vector<Token> outPut;
		md_done = true;
		outPut.push_back(tokenList[0]);
		for (int i = 1; i < tokenList.size(); i++)
		{
			outPut.push_back(tokenList[i]);
			if (tokenList[i].type == TokenType::Operator)
			{
				if (!(tokenList[i].value.oType == OperatorType::multiply || tokenList[i].value.oType == OperatorType::devid))
					continue;
				double no1 = tokenList[i - 1].value.number;
				double no2 = tokenList[i + 1].value.number;
				double result;
				if (tokenList[i].value.oType == OperatorType::multiply)
					result = no1*no2;
				if (tokenList[i].value.oType == OperatorType::devid)
					result = no1 / no2;

				Token& lastToken = outPut.back();
				lastToken.type = TokenType::Number;
				lastToken.value.number = result;
				md_done = false;
				for (int j = i + 2; j < tokenList.size(); j++) outPut.push_back(tokenList[j]);
				break;
			}
		}
		tokenList = outPut;
	}

	return tokenList.back().value.number;
}