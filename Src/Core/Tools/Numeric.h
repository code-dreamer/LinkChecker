#pragma once

#include "Bugs/Checks.h"

namespace Tools {
namespace Numeric {

double round(double value, int digitsAfterDecimal);

template<typename Target, typename Source>
Target saturationCast(Source value) 
{
	try {
		return boost::numeric_cast<Target>(value);
	}
	catch (const boost::numeric::negative_overflow&) {
		DCHECK_MSG(false, "Negative overflow detected");
		return std::numeric_limits<Target>::min();
	}
	catch (const boost::numeric::positive_overflow&) {
		DCHECK_MSG(false, "Positive overflow detected");
		return std::numeric_limits<Target>::max();
	}

	catch (const boost::numeric::bad_numeric_cast&) {
		DCHECK_MSG(false, "Numeric cast failed");
		return Target();
	}
}

} // namespace Process
} // namespace Tools
