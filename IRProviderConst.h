#pragma once
#include "IRProvider.h"
#include <iostream>
namespace SiriusFM
{
	template <>
        class IRProvider <IRModeE :: Const>
        {
           private:
                   double m_IRs[int(CcyE :: N)];
           public:
                   IRProvider (const char* a_file);

                   double r (CcyE a_Ccy, double a_t)
		   {	
			   return m_IRs[int(a_Ccy)];
		   };
        };

}
