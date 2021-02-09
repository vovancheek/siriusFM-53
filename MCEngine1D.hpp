#pragma once
#include <cassert>
#include "MCEngine1D.h"
#include "Time.h"
#include <random>

namespace SiriusFM
{
	template <typename Diffusion1D,
                  typename AProvider,
                  typename AssetClassA,
                  typename BProvider,
                  typename AssetClassB>
	inline void MCEngine1D <Diffusion1D,
	      	  	        AProvider,
				AssetClassA,
      	      			BProvider,
	      			AssetClassB> ::
	Simulate (time_t             a_t0, 
                  time_t             a_T,  
                  int                a_tau_min,
		  double             a_s0,
		  long               a_P,
                  Diffusion1D const* a_diff,
                  AProvider const*   a_rateA,
                  BProvider const*   a_rateB,
                  AssetClassA        a_A,
                  AssetClassB        a_B,
                  bool               a_isRN
                 )
	{
		//Checks for valid parameters
		assert (a_diff != nullptr and
			a_rateA != nullptr and
			a_rateB != nullptr and
			a_A != AssetClassA::UNDEFINED and
			a_B != AssetClassB::UNDEFINED and
			a_t0 <= a_T and 
			a_P > 0 
		       );
		double tau = double(a_tau_min) / (365.25 * 1440.0);
		time_t Tsec = a_T - a_t0;
		int tau_sec = a_tau_min * 60;
		long L = (Tsec % tau_sec == 0) ? Tsec/tau_sec : Tsec/tau_sec + 1;
		double tlast = (Tsec % tau_sec == 0) ? tau : YearFrac (Tsec - (L-1) * tau_sec);
		assert (0 < tlast && tlast <= tau);
		L++;//?????????????
		double y0 = YearFrac (a_t0);
		double yT = YearFrac (a_T);
		long P = 2 * a_P; //Antithetic variables

		if (L*P > m_MaxL * m_MaxP)
			throw std :: invalid_argument ("bad length or path num");
		
		std :: normal_distribution <> N01 (0.0, 1.0);
		std :: mt19937_64          U;
		double stau = sqrt (tau);
		double slast = sqrt (tlast);
		assert (slast <= stau and
			slast > 0);

		//Main Simulation Loop:
		for (long p = 0; p < a_P; ++p)
		{
			double* path0 = m_paths + 2 * p * L;
			double* path1 = path0 + L;
			path0[0] = a_s0;
			path1[0] = a_s0;
			double y = y0;
			double Sp0 = a_s0;
			double  Sp1 = a_s0;
			for (long l = 1; l < L; ++l)
			{
				//complete the trend
				double mu0 = 0.0;
			       	double mu1 = 0.0;
				if (a_isRN) //Risk-Neutral case
				{
					double delta_r = a_rateB -> r (a_B, y) - a_rateA -> r (a_A, y);
					mu0 = delta_r * Sp0;
					mu1 = delta_r *Sp1;
				}		 
				else
				{
					mu0 = a_diff -> mu (Sp0, y);
					mu1 = a_diff -> mu (Sp1, y);
				}
				double sigma0 = a_diff -> sigma (Sp0, y);
				double sigma1 = a_diff -> sigma (Sp1, y);

				double Z = N01(U);
		                double Sn0, Sn1;
               		        if (l == L-1)
        	                {
                               		 Sn0 = Sp0 + mu0 * tlast + sigma0 * Z * slast;
                         		 Sn1 = Sp1 + mu1 * tlast - sigma1 * Z * slast;
               		        }
                		else
                		{
                       			 Sn0 = Sp0 + mu0 * tau + sigma0 * Z * stau;
                       			 Sn1 = Sp1 + mu1 * tau - sigma1 * Z * stau;
                		}
               			path0[l] = Sn0;
               		        path1[l] = Sn1;
             	            	Sp0 = Sn0;
                                Sp1 = Sn1;

			}

		}
		
		m_L = L;
		m_P = P;


	};

}



