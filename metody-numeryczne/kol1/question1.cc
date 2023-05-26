#include <iostream>
#include <vector>

double func(const double x, const double y) {
  return y*y + x;
}

double IE(const double xn, const double yn, const double h) {
  return yn + h/2.0 * (func(xn, yn) + func(xn+h, yn+h*func(xn, yn)));
}

void solve() {
  std::vector<double> x;
  std::vector<double> y;
  const double h = 0.1;
  const int N = 1.0/h;

  // Initial conditions
  x.push_back(0);
  y.push_back(0);

  // Calculations
  for(int i=1; i<=N; i++) {
    const double xn = x.back();
    const double yn = y.back();
    const double yn_p1 = IE(xn, yn, h);
    const double xn_p1 = i*h;
    x.push_back(xn_p1);
    y.push_back(yn_p1);
  }

  // Print results
  for(int i=0; i<=N; i++)
    std::cout << x.at(i) << ": " << y.at(i) << '\n';
}

int main() {
  solve();
  return 0;
}
