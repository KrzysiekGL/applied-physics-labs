#include <iostream>
#include <vector>
#include <cmath>

double func(const double t, const double y1, const double y2) {
  const double q = 0.5;
  const double a = 0.8;
  const double w0 = 0.35;
  return -std::sin(y1) - q*y2 + a*std::cos(w0*t);
}

void solve() {
  std::vector<double> t;
  std::vector<std::vector<double>> Y;
  const double h = 0.05;
  const double N = 10.0/h;

  // Inintial conditions
  t.push_back(0);
  Y.push_back(std::vector<double>{1.4, 0});

  // Calculations
  for(int i=1; i<=N; ++i) {
    const double T = t.back();
    const double y1_0 = Y.back().at(0);
    const double y2_0 = Y.back().at(1);

    const double f0_0 = y2_0;
    const double f0_1 = func(T, y1_0, y2_0);

    const double f1_0 = y2_0 + h/2.0 * f0_1;
    const double f1_1 = func(T+h/2.0, y1_0+h/2.0*f0_0, y2_0+h/2.0*f0_1);

    const double f2_0 = y2_0+h/2.0*f1_1;
    const double f2_1 = func(T+h/2.0, y1_0+h/2.0*f1_0, y2_0+h/2.0*f1_1);

    const double f3_0 = y2_0+h*f2_1;
    const double f3_1 = func(T+h, y1_0+h*f2_0, y2_0+h*f2_1);

    const double y1_1 = y1_0 + h/6.0 * (f0_0 + 2*f1_0 + 2*f2_0 + f3_0);
    const double y2_1 = y2_0 + h/6.0 * (f0_1 + 2*f1_1 + 2*f2_1 + f3_1);

    t.push_back(i*h);
    Y.push_back(std::vector<double>{y1_1, y2_1});
  }

  // Print results
  std::cout << "t,y1,y2\n";
  for(int i=0; i<=N; ++i){
    const double T = t.at(i);
    const double y1 = Y.at(i).at(0);
    const double y2 = Y.at(i).at(1);
    std::cout << T << "," << y1 << "," << y2 << '\n';
  }
}

int main() {
  solve();
  return 0;
}
