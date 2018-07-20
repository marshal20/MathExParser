#pragma once
#include <vector>
#include "internalTypes.hpp"

extern bool isOpenBracket(const Token& token);
extern bool isCloseBracket(const Token& token);

extern void tokenize(std::vector<Token>& out, const std::vector<char>& parsed);