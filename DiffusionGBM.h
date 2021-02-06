#pragma once
#include <cstdio>

namespace SiriusFM
{

	class DiffusionGBM
	{
		double const m_mu;
		double const m_sigma;
	    public:
		DiffusionGBM(double m, double s): m_mu(m),
						   m_sigma(s)
		{
			if (m_sigma <= 0)
			       printf("Bad sigma\n");	
		};

		double mu(double S_t) {return m_mu * S_t;};
		double sigma(double S_t) {return m_sigma * S_t;};
		
	};
}
