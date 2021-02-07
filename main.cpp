#include <iostream>
#include "DiffusionGBM.h"
#include "IRProvider.h"
#include "IRProviderConst.h"
using namespace std;
using namespace SiriusFM;

int main()
{
	IRProvider <SiriusFM::IRModeE::Const> IRP ("File.txt");
	
	double r = IRP.r(SiriusFM::CcyE::CHF, 0);
	cout << r << "\n";
	puts (CcyE2Str(SiriusFM::CcyE::CHF));
	return 0;
}

