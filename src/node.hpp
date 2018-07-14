#pragma once
#include "internalTypes.hpp"

struct Node
{
	Node* parent;
	Token token;
	Node* cfirst;
	Node* csecond;
};

extern void zero_node(Node* node);
extern void free_node(Node* node);
