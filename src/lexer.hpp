#pragma once
#include <vector>
#include "internalTypes.hpp"

extern OperatorType getOperatorType(const Token& token);
extern MathOperationType getMathOperationType(const Token& token);

extern void tokenize(std::vector<Token>& out, const std::vector<char>& parsed);