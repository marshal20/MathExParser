#pragma once
#include "internalTypes.hpp"
#include "node.hpp"
#include <vector>

extern void print_token(const Token& token);
extern void print_tokenList(const std::vector<Token>& tokenList);
extern void print_node(Node* node, std::string offset = "");