#pragma once
#include <cstdio>

namespace SiriusFM
{

        class DiffusionCEV
        {
                double const m_mu;
                double const m_sigma;
		double const m_beta;
            public:
                DiffusionCEV(double m, double s, double beta): m_mu(m),
                                                  	       m_sigma(s),
							       m_beta(beta)
                {
                	if (m_beta < 0) throw std :: invalid_argument ("Bad beta");
                };

                double mu(double S_t) {return m_mu * S_t;};
                double sigma(double S_t) {return m_sigma * pow(S_t, m_beta);};

        };
}

