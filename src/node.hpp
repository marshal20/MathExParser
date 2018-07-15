#pragma once
#include "internalTypes.hpp"
#include <vector>

struct Node
{
	Node* parent;
	Token token;
	std::vector<Node*> childList;
};

extern void zero_node(Node* node);
extern void free_node(Node* node);
extern void replace_node(Node* node, Node* with);
extern void addchild_node(Node* node, Node* child);
