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

void replace_node(Node* node, Node* with)
{
	with->parent = node->parent;
	if (node->parent)
	{
		if (node->parent->cfirst == node)
			node->parent->cfirst = with;
		else if (node->parent->csecond == node)
			node->parent->csecond = with;
	}
}

void addchild_node(Node* node, Node* child)
{
	child->parent = node;
	if (!node->cfirst)
		node->cfirst = child;
	else if (!node->csecond)
		node->csecond = child;
}
