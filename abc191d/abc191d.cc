#include "mdouble.h"
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const double pi = 3.14159265359;

using namespace decker1971;

double to_double(const mdouble& x) { return x.x; }

mdouble cx, cy, r;
bool incircle(const mdouble& x, ll ly)
{
  mdouble y = mdouble(double(ly));
  return (x - cx) * (x - cx) + (y - cy) * (y - cy) <= r * r;
}

int main()
{
  cin >> cx >> cy >> r;
  ll ans = 0;
  for (ll i = ceil(to_double(cx - r)); i <= floor(to_double(cx + r)); i++){
    mdouble j = mdouble(double(i));
    mdouble y1 = sqrt(r*r - (j - cx)*(j - cx));
    ll uy = floor(to_double(cy + y1));
    ll ly = ceil(to_double(cy - y1));

    if (incircle(j, uy+1)) uy++;
    else if (!incircle(j, uy)) uy--;
    if (incircle(j, ly-1)) ly--;
    else if (!incircle(j, ly)) ly++;
    
    if (uy >= ly) ans += uy - ly + 1;
  }
  cout << ans << endl;
  return 0;
}
