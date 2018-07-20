#include "tree.hpp"
#include "lexer.hpp"
//#include "utils.hpp"
//#include <string>
//#include <iostream>

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
	int curLevel = tokenList[openBracket].level;
	std::string openBracketstr = tokenList[openBracket].innerText;
	for (unsigned int i = openBracket; i < tokenList.size(); i++)
	{
		if (tokenList[i].type != TokenType::Operator) continue;
		if (getOperatorType(tokenList[i]) == OperatorType::CloseBracket && tokenList[i].level == curLevel)
			return i;
	}

	throw std::exception("Expected close bracket.");
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

	if (getMathOperationType(head->parent->token) == getMathOperationType(token))
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

Node* handleGroup(const std::vector<Token>& tokenList, Node* head, int openBracket, int closeBracket)
{
	const Token& token = tokenList[openBracket];

	std::vector<std::vector<Token>> grouptokenLists;
	grouptokenLists.push_back(std::vector<Token>());
	// from first token inside the brackets to the last
	
	int curLevel = tokenList[openBracket + 1].level;
	for (int j = openBracket + 1; j < closeBracket; j++)
	{
		if (tokenList[j].level == curLevel && tokenList[j].type == TokenType::Operator && getOperatorType(tokenList[j]) == OperatorType::Dividor)
		{
			grouptokenLists.push_back(std::vector<Token>());
			continue;
		}
		grouptokenLists.back().push_back(tokenList[j]);
	}
		
	Node* group = new_node();
	zero_node(group);
	group->token.index = token.index;
	group->token.type = TokenType::Group;
	// add all the children which are separated with commas
	for (const std::vector<Token>& sGroup : grouptokenLists)
	{
		Node* groupHead = parse_tokenList(sGroup);
		addchild_node(group, groupHead);
	}
		
	if (head) addchild_node(head, group);

	return group;
}

Node* name_token(Node* head, const Token& token)
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

	for (unsigned int i = 0; i < tokenList.size(); i++)
	{
		const Token& token = tokenList[i];
		
		// check if we have a group inside brackets
		if (token.type == TokenType::Operator && getOperatorType(token) == OperatorType::OpenBracket)
		{
			int closebracket = get_close_pracket(i, tokenList);
			head = handleGroup(tokenList, head, i, closebracket);
			i = closebracket;
			continue;
		}

		if (token.type == TokenType::Operator)
			head = basic_operator_token(head, token);
		else if (token.type == TokenType::Number)
			head = number_token(head, token);
		else if (token.type == TokenType::Name)
			head = number_token(head, token);
	}

	// go up till the origin tree
	while (head->parent)
		head = head->parent;
	return head;
}