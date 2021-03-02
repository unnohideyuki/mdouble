#include "mdouble.h"
#include <bits/stdc++.h>
using namespace decker1971;
using namespace std;

int main()
{
  mdouble a = stomdouble("1.01");
  mdouble b = 2718281;
  mdouble c = stomdouble("1.00e-02");

  cout << c << endl;
  
  mdouble x1 = (-b - mdouble::sqrt(b*b - 4*a*c)) / (2*a);
  mdouble x2 = (-b + mdouble::sqrt(b*b - 4*a*c)) / (2*a);

  // -2.6914e+06
  // -3.6788e-09
  cout << scientific << setprecision(4) << x1 << endl;
  cout << scientific << setprecision(4) << x2 << endl;
  return 0;
}
