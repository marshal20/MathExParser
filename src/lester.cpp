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

/*Node* parse_tokenList(const std::vector<Token>& tokenList)
{
	if (tokenList.size() == 0) return nullptr;

	// preparing the first node
	Node* head = new Node;
	zero_node(head);
	head->token = tokenList[0];

	for (int i = 1; i < tokenList.size(); i++)
	{
		const Token& curtoken = tokenList[i];
		// handle bracket
		if (curtoken.type == TokenType::Operator && curtoken.value.oType == OperatorType::openBracket)
		{
			int closebracket = get_close_pracket(i, tokenList);
			std::vector<Token> newExpression; //newExpression.reserve(closebracket - i);
			for (int j = i + 1; j < closebracket; j++)
				newExpression.push_back(tokenList[j]);

			Node* newexp = parse_tokenList(newExpression);
			Node* newgroup = new Node;
			zero_node(newgroup);
			newexp->token.index = i;
			newexp->token.type = TokenType::Group;
			newexp->parent = newgroup;
			addchild_node(newgroup, newexp);
			if (head)
			{
				newgroup->parent = head;
				addchild_node(head, newgroup);
			}

			head = newgroup;
			i = closebracket + 1;
			continue;
		}

		int order = get_token_order(curtoken);
		int headorder = get_token_order((const Token&)*head);
		if (order > headorder && order != 0)
		{
			// replace the head, the old head becomes a child
			Node* newhead = new Node;
			zero_node(newhead);
			head = get_lowest_parent(head, order);
			replace_node(head, newhead);
			newhead->token = curtoken;
			newhead->cfirst = head;
			head = newhead;
		}
		else
		{
			// become a child of the current head
			Node* newchild = new Node;
			zero_node(newchild);
			newchild->parent = head;
			newchild->token = curtoken;
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
}*/

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