#include <iostream>
#include <vector>
#include <utility>
#include <cmath>
#include <tuple>

const double m = 0.01;    // kg
const double g = 9.8;     // m.s2
const double k = 0.0001;  // kg.m-1
const double E = 0.00001; // tolerance

double func(double v) {
  return g - (k/m)*v*v;
}

std::tuple<double, double> RKF(double v, double h) {
  double f0 = func(v);
  double f1 = func(v + h/4.0*f0);
  double f2 = func(v + 3.0*h/32.0*f0 + 9.0*h/32.0*f1);
  double f3 = func(v +
		   1932.0*h/2197.0*f0 -
		   7200.0*h/2197.0*f1 +
		   7296.0*h/2197.0*f2);
  double f4 = func(v +
		   439.0*h/216.0*f0 -
		   8.0*h*f1 +
		   3680.0*h/513.0*f2 -
		   845.0*h/4104.0*f3);
  double f5 = func(v -
		   8.0*h/27.0*f0 +
		   2.0*h*f1 -
		   3544.0*h/2565.0*f2 +
		   1859.0*h/4104.0*f3 -
		   11.0*h/40.0*f4);

  double err = h*(f0/360.0
		  -128.0*f2/4275.0
		  -2197.0/75240.0*f3
		  +1.0/50.0*f4
		  +2.0/55.0*f5);

  double v_next = v + h*(16.0/135.0*f0 +
			 6656.0/12825.0*f2 +
			 28561.0/56430.0*f3 -
			 9.0/50.0*f4 +
			 2.0/55.0*f5);

  return {v_next, err};
}

// Runge-Kutta-Fehlberg
void solve(double h = 0.2) {
  std::vector<std::pair<double, double>> t_v;
  double v = 0.0;
  double t = 0.0;

  // initial condition
  t_v.push_back(std::pair<double, double>(t, v));

  // Increment time
  t += h;

  do {
    auto [v_next, err] = RKF(t_v.back().second, h);

    // Compare fabs(error) aginst tolerance; if <E -> compute
    if(std::fabs(err) <= h*E) {
      // add a pair to the vector
      t+=h;
      v = v_next;
      t_v.push_back(std::pair<double, double>(t, v));
      std::cout << t_v.back().first << '\t' << t_v.back().second << '\t' << h << '\n';
    }
    else {
      // skip this step
      std::cout << t_v.back().first << '\t' << t_v.back().second << '\t' << h << " rejected\n";
    }

    // Modify step
    h = 0.90*h * std::pow(std::fabs(h)*E/std::fabs(err), 1.0/4.0);
  } while(t<10.0);
}

int main() {
  solve();
  return 0;
}
