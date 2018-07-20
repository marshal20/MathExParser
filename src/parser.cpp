#include "parser.hpp"

void parse(std::vector<char>& out, const std::string& equation)
{
	out.reserve(equation.length());
	for (const char c : equation)
		out.push_back(c);
}
