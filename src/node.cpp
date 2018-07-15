#include "node.hpp"

void zero_node(Node* node)
{
	if (!node) return;

	node->parent = nullptr;
	node->childList.clear();
}

void free_node(Node* node)
{
	// free every child first
	for(Node* child : node->childList)
		if(child)
			free_node(child);

	delete node;
}

void replace_node(Node* node, Node* with)
{
	with->parent = node->parent;
	addchild_node(with, node);
	// replace the child in the parent
	if (node->parent)
		for (auto& child : with->parent->childList)
			if (child == node)
				child = with;
}

void addchild_node(Node* node, Node* child)
{
	child->parent = node;
	node->childList.push_back(child);
}
