#include "node.hpp"

void zero_node(Node* node)
{
	if (!node) return;

	node->parent = nullptr;
	node->cfirst = nullptr;
	node->csecond = nullptr;
}

