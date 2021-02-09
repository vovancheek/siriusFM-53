#pragma once

namespace SiriusFM
{
	inline double YearFrac (time_t a_t)
	{
		//Avg year in seconds
		constexpr double SecY = 365.25 * 86400.0;
		return 1970.0 + double(a_t)/SecY;
	}
}
