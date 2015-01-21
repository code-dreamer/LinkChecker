#include "stdafx.h"
#include "Tools/Numeric.h"

namespace Tools {
namespace Numeric {

double round(const double value, const int digitsAfterDecimal)
{
	return floor(value * pow(10., digitsAfterDecimal) + .5) / pow(10., (int)digitsAfterDecimal);
}

} // namespace Numeric
} // namespace Tools