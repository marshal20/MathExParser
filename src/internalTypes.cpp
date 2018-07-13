#include "internalTypes.hpp"

std::array<OperatorDefinition, 4> DEFINED_OPERATORS{ {
	{ '+', OperatorType::plus },
	{ '-', OperatorType::minus },
	{ '/', OperatorType::devid },
	{ '*', OperatorType::multiply }
} };