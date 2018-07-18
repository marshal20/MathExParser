#include "defined.hpp"

const double def_pi = 3.141592653589793;

double def_sin(const Args& args)
{
	return std::sin(args[0]);
}

double def_cos(const Args& args)
{
	return std::cos(args[0]);
}

double def_tan(const Args& args)
{
	return std::tan(args[0]);
}


std::map<std::string, func> definedFunc {
	{"sin", def_sin},
	{ "cos", def_cos },
	{ "tan", def_tan }
	};

std::map<std::string, double> definedConst {
	{"pi", def_pi}
	};
