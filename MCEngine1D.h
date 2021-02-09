#pragma once
#include <cmath>
#include <stdexcept>
#include <ctime>
#include <tuple>
namespace SiriusFM
{
	template <typename Diffusion1D,
		  typename AProvider, 
		  typename AssetClassA,
		  typename BProvider,
		  typename AssetClassB>
	class MCEngine1D
	{
	
	private:
		long const m_MaxL; //Max PathLength
		long const m_MaxP; //Max NPaths
		double* const m_paths;
		
		double m_s0;
		long m_L; //m_L <= m_MaxL;                ЧТО ТАКОЕ long??
		long m_P; //m_P <= m_MaxP;
		double m_tau; //TimeStep as YearFraction
		double m_t0; //2021.xxxx
		Diffusion1D const* m_diff;
		AProvider const* m_rateA;
		BProvider const* m_rateB;
		AssetClassA m_A; //asset A
		AssetClassB m_B; //asset B
		bool m_RN; //Risk-Neutral Trend
	public:
		MCEngine1D (long a_MaxL, long a_MaxP)
		: m_MaxL (a_MaxL),
		  m_MaxP (a_MaxP),
		  m_paths (new double [m_MaxL * m_MaxP]),
		 
		  m_s0 (0),
		  m_L (0),
		  m_P (0),
		  m_tau (nan),
		  m_t0 (nan),
		  m_diff (nullptr),
		  m_rateA (nullptr),
		  m_rateB (nullptr),
		  m_A (AssetClassA :: UNDEFINED),
		  m_B (AssetClassB :: UNDEFINED),
		  m_RN (false)
		{
			if (m_MaxL <= 0 || m_MaxP <= 0) throw std :: invalid_argument ("bad size");

			for (long p = 0; p < m_MaxP; ++p)
			{
				for (long l = 0; l < m_MaxL; ++l)
				{
					m_paths[p * m_MaxL + l] = 0;
				}
			}

		};
		
		double *Access_to_last ()
		{
			return m_paths + (m_MaxL * m_MaxP - 1);
		}
		
		void Simulate (time_t a_t0, //Curr(pricing) Time
			       			 time_t a_T, //Expir.Time 
			       			 int a_tau_min,
			       			 double a_s0,
			       			 long a_P,
			       		 	 Diffusion1D const* a_diff,
			        		 AProvider const* a_rateA,
			       		 	 BProvider const* a_rateB,
			       		 	 AssetClassA a_A,
			       			 AssetClassB a_B,
			       		 	 bool a_isRN
			      			);
		
		~ MCEngine1D ()
		{
			delete [] m_paths;
		}

		std::tuple <long, long, double const*>
		GetPaths () const
		{
			return
			(m_L <= 0 || m_P <= 0)
			? std::make_tuple (0, 0, nullptr)
			: std::make_tuple (m_L, m_P, m_paths);
		}

		MCEngine1D (MCEngine1D const&) = delete;
                MCEngine1D& operator = (MCEngine1D const&) = delete;


	};
}
