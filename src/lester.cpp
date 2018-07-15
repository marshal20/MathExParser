#include "lester.hpp"
#include "parser.hpp"
#include "utils.hpp"
#include <string>
#include <iostream>

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

int get_close_pracket(int openBracket, const std::vector<Token>& tokenList)
{
	int level = 0;
	for (int i = openBracket; i < tokenList.size(); i++)
	{
		if (tokenList[i].type != TokenType::Operator) continue;
		if (tokenList[i].value.oType == OperatorType::openBracket)
			level++;
		if (tokenList[i].value.oType == OperatorType::closeBracket)
			level--;
		if (level == 0)
			return i;
	}
	return -1;
}


Node* basic_operator_token(Node* head, const Token& token)
{
	// if it has no parent replace it and return the new head
	if (!head->parent)
	{
		Node* newnode = new_node();
		zero_node(newnode);
		newnode->token = token;
		addchild_node(newnode, head);
		return newnode;
	}

	if (head->parent->token.value.oType == token.value.oType)
		return head->parent;

	Node* newnode = new_node();
	zero_node(newnode);
	newnode->token = token;
	Node* lowestparent = get_lowest_parent(head, get_token_order(token));
	// replace it and add it as a child
	replace_node(lowestparent, newnode);
	return newnode;
}

Node* number_token(Node* head, const Token& token)
{
	if (!head)
	{
		Node* newnode = new_node();
		zero_node(newnode);
		newnode->token = token;
		return newnode;
	}

	// just become a child of the current node
	Node* newnode = new_node();
	zero_node(newnode);
	newnode->token = token;
	addchild_node(head, newnode);
	return newnode;
}

Node* parse_tokenList(const std::vector<Token>& tokenList)
{
	Node* head = nullptr;

	for (int i = 0; i < tokenList.size(); i++)
	{
		const Token& token = tokenList[i];

		if (token.type == TokenType::Operator)
			head = basic_operator_token(head, token);
		else if (token.type == TokenType::Number)
			head = number_token(head, token);
	}

	// go up till the origin tree
	while (head->parent)
		head = head->parent;
	return head;
}