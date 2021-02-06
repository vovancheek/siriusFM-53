#pragma once
#include <cstdio>
#include <cmath>

namespace SiriusFM
{

        class DiffusionLipton
        {
                double const m_mu;
                double const m_sigma0;
                double const m_sigma1;
		double const m_sigma2;
            public:
                DiffusionLipton (double mu, double sigma0, double sigma1, double sigma2): m_mu (mu),
                                                                       		       m_sigma0 (sigma0),
                                                                                       m_sigma1 (sigma1),
										       m_sigma2 (sigma2)
                {
                        if (m_sigma0 < 0) throw std :: invalid_argument ("Bad sigma0");
                        if (m_sigma2 < 0) throw std :: invalid_argument ("Bad sigma2");
			if (m_sigma1 * m_sigma1 - 4 * m_sigma0 * m_sigma2 >= 0) throw std :: invalid_argument ("Bad determinant");
                };

                double mu(double S_t) {return m_mu * S_t;};
                double sigma(double S_t) {return m_sigma0 + m_sigma1 * S_t + m_sigma2 * S_t * S_t;};

        };
}

