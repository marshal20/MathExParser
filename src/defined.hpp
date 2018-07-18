#pragma
#include <map>
#include <string>
#include <functional>
#include <vector>

typedef std::vector<double> Args;
typedef std::function<double(const Args&)> func;

extern std::map<std::string, func> definedFunc;
extern std::map<std::string, double> definedConst;
