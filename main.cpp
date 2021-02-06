#include <iostream>
#include "DiffusionGBM.h"

using namespace std;
using namespace SiriusFM;

int main()
{
	double m = 0;
	double s = 0;
	double S_t = 0;

	cin >> m;
	cin >> s;
	DiffusionGBM A(m, s);
	cin >> S_t;

	cout << A.mu(S_t) << "\n";	
	cout << A.sigma(S_t) << "\n";
	return 0;
}

