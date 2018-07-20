#include "defined.hpp"

const double def_pi = 3.141592653589793;
const double def_e  = 2.718281828459045;

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

double def_max(const Args& args)
{
	double greatest = 0;
	for (double num : args)
		if (num > greatest)
			greatest = num;

	return greatest;
}

double def_min(const Args& args)
{
	double minimum = args[0];
	for (double num : args)
		if (num < minimum)
			minimum = num;

	return minimum;
}

std::map<std::string, func> definedFunc {
	{"sin", def_sin},
	{ "cos", def_cos },
	{ "tan", def_tan },
	{ "max", def_max},
	{ "min", def_min }
	};

std::map<std::string, double> definedConst {
	{"pi", def_pi},
	{"e", def_e}
	};
