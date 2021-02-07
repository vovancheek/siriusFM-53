#include "IRProvider.h"
#include "IRProviderConst.h"
#include <cstdio>
#include <iostream>

#define IR_SIZE 1024
#define CCY_SIZE 3

namespace SiriusFM
{
	IRProvider <IRModeE :: Const> :: IRProvider 
		(const char* a_file)
	{
		FILE *fp = fopen (a_file, "r");

		char ir[IR_SIZE];
		char ccy[CCY_SIZE+1];	

		if (fp == nullptr) throw std :: invalid_argument ("cannot open file"); else
		{
			while (fgets (ccy, CCY_SIZE+1, fp))
			{
				fgets (ir, IR_SIZE, fp);
				m_IRs[int(Str2CcyE(ccy))] = atof (ir);
			}
			fclose (fp);
		}	
	};

}
