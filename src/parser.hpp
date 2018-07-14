#pragma once
#include "internalTypes.hpp"
#include <vector>

extern OperatorType char_to_operatorType(const char charachter);
extern char operatorType_to_char(const OperatorType oType);
extern std::vector<Token> parse_equation(std::string equation);
extern void print_token(const Token& token);
extern void print_tokenList(const std::vector<Token>& tokenList);
extern double evaluate(std::vector<Token> tokenList);