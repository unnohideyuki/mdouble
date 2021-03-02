namespace decker1971 {
  class mdouble {
  public:
    double x, xx;
    static void mul12(const double x, const double y, double& z, double& zz)
    {
      const double C = double(1LL << (DBL_MANT_DIG - DBL_MANT_DIG/2)) + 1.0;
      double p = x * C;
      double hx = x - p + p; double tx = x - hx;
      p = y * C;
      double hy = y - p + p; double ty = y - hy;
      p = hx * hy;
      double q = hx * ty + tx * hy;
      z = p + q;
      zz = p - z + q + tx * ty;
    }
    mdouble() : x{0.0}, xx{0.0} {}
    mdouble(const double y) : x{y}, xx{0.0} {}
    mdouble(const double y, const double yy) : x{y}, xx{yy} {}
    mdouble(const mdouble& other) = default;
    mdouble& operator=(const mdouble& other) = default;
    bool operator==(const mdouble& rhs) const { return (x == rhs.x && xx == rhs.xx); }
    bool operator!=(const mdouble& rhs) const { return !(*this == rhs); }
    bool operator<=(const mdouble& rhs) const { return (x < rhs.x || (x == rhs.x && xx <= rhs.xx)); }
    bool operator>(const mdouble& rhs) const { return !(*this <= rhs); }
    bool operator>=(const mdouble& rhs) const { return (*this > rhs || *this == rhs); }
    bool operator<(const mdouble& rhs) const { return !(*this >= rhs); }
    friend mdouble operator+(const mdouble& a, const mdouble& b)
    {
      double r = a.x + b.x;
      double s =
	std::fabs(a.x) > std::fabs(b.x) ? a.x - r + b.x + b.xx + a.xx : b.x - r + a.x + a.xx + b.xx;
      double z = r + s;
      double zz = r - z + s;
      return mdouble(z, zz);
    }
    friend mdouble operator-(const mdouble& a, const mdouble& b)
    {
      double r = a.x - b.x;
      double s =
	std::fabs(a.x) > std::fabs(b.x) ? a.x - r - b.x - b.xx + a.xx : - b.x - r + a.x + a.xx - b.xx;
      double z = r + s;
      double zz = r - z + s;
      return mdouble(z, zz);
    }
    friend mdouble operator*(const mdouble& a, const mdouble& b)
    {
      double c, cc;
      mul12(a.x, b.x, c, cc);
      cc = a.x * b.xx + a.xx * b.x + cc;
      double z = c + cc;
      double zz = c - z + cc;
      return mdouble(z, zz);
    }
    friend mdouble operator/(const mdouble& a, const mdouble& b)
    {
      double c = a.x / b.x;
      double u, uu;
      mul12(c, b.x, u, uu);
      double cc = (a.x - u - uu + a.xx - c * b.xx) / b.x;
      double z = c + cc;
      double zz = c - z + cc;
      return mdouble(z, zz);
    }
    mdouble operator-() const{ return mdouble(-x, -xx); }
    mdouble operator+=(const mdouble& rhs){ return (*this = *this + rhs); }
    mdouble operator-=(const mdouble& rhs){ return (*this = *this - rhs); }
    mdouble operator*=(const mdouble& rhs){ return (*this = *this * rhs); }
    mdouble operator/=(const mdouble& rhs){ return (*this = *this / rhs); }
    static mdouble sqrt(const mdouble& a)
    {
      if (a.x <= 0) return mdouble(0.0);
      double c = std::sqrt(a.x);
      double u, uu;
      mul12(c, c, u, uu);
      double cc = (a.x - u - uu + a.xx) * 0.5 / c;
      double y = c + cc;
      double yy = c - y + cc;
      return mdouble(y, yy);
    }
  };
  mdouble sqrt(const mdouble& a) { return mdouble::sqrt(a); }
  mdouble stomdouble(const std::string& s)
  {
    int epos = -1;
    int pos = -1;
    std::string t;
    for (int i = 0; i < s.size(); i++){
      if (s[i] == 'e' || s[i] == 'E'){ epos = i; break; }
      if (s[i] == '.') pos = i;
      else t += s[i];
    }
    mdouble r = std::stod(t);
    if (pos >= 0){
      r /= std::pow(10, t.size() - pos);
    }
    if (epos >= 0){
      r *= std::pow(10, std::stol(s.substr(epos+1)));
    }
    return r;
  }
  std::ostream& operator<<(std::ostream& os, const mdouble& a){ return (os << a.x); }
  std::istream& operator>>(std::istream& is, mdouble& a)
  {
    std::string s;
    is >> s;
    a = stomdouble(s);
    return is;
  }
} // namespace decker1971
