#pragma once
#include <cstdio>
#include <cmath.h>

namespace SiriusFM
{

        class DiffusionCIR
        {
                double const m_kappa;
                double const m_theta;
		double const m_sigma
            public:
                DiffusionCIR(double kappa, double theta, double sigma): m_kappa (kappa),
                                                  		        m_sigma (sigma),
									m_theta (theta)
                {
                        if (m_kappa <= 0) throw std :: invalid_argument ("Bad kappa");
			if (m_theta <= 0) throw std :: invalid_argument ("Bad theta");
                };

                double mu(double S_t) {return m_kappa * (m_theta - S_t);};
                double sigma(double S_t) {return m_sigma * sqrt(S_t);};

        };
}

