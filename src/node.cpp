#include "node.hpp"

void zero_node(Node* node)
{
	if (!node) return;

	node->parent = nullptr;
	node->cfirst = nullptr;
	node->csecond = nullptr;
}

void free_node(Node* node)
{
	if (node->cfirst)
		free_node(node->cfirst);
	if (node->csecond)
		free_node(node->csecond);

	delete node;
}

