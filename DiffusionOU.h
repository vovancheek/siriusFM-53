#pragma once
#include <cstdio>
#include <cmath>

namespace SiriusFM
{

        class DiffusionOU
        {
                double const m_kappa;
                double const m_theta;
                double const m_sigma;
            public:
                DiffusionOU (double kappa, double theta, double sigma): m_kappa (kappa),
                                                                        m_theta (theta),
                                                                        m_sigma (sigma)
                {
                        if (m_kappa <= 0) throw std :: invalid_argument ("Bad kappa");
                };

                double mu(double S_t) {return m_kappa * (m_theta - S_t);};
                double sigma(double S_t) {return m_sigma * S_t;};

        };
}
