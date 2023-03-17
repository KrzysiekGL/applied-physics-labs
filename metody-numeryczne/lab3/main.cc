#include <iostream>
#include <vector>
#include <utility>
#include <cmath>

const double m = 0.01;    // kg
const double g = 9.8;     // m.s2
const double k = 0.0001;  //kg.m-1
const double E = 0.00001; // tolerance

double func(double v) {
  return g - k/m*v*v;
}

// Runge-Kutta-Fehlberg
void rkf(double h = 0.2) {
  std::vector<std::pair<double, double>> t_v;
  double v = .0;
  for(double t = .0; t<=10.0001; t+=h) {
    // Calculate 6 degrees of the functions
    double f0 = func(v);
    double f1 = func(v + h/4.f*f0);
    double f2 = func(v + 3.f*h/32.f*f0 + 9.f*h/32.f*f1);
    double f3 = func(v +
		     1932.f*h/2197.f*f0 -
		     7200.f*h/2197.f*f1 +
		     7296.f*h/2197.f*f2);
    double f4 = func(v +
		     439.f*h/216.f*f0 -
		     8.f*h*f1 +
		     3680.f*h/513.f*f2 -
		     845.f*h/4104.f*f3);
    double f5 = func(v -
		     8.f*h/27.f*f0 +
		     2.f*h*f1 -
		     3544.f*h/2565.f*f2 +
		     1859.f*h/4104.f*f3 -
		     11.f*h/40.f*f4);
    if(!t) std::cout << "f0: " << f0 <<
	     "\nf1: " << f1 <<
	     "\nf2: " << f2 <<
	     "\nf3: " << f3 <<
	     "\nf4: " << f4 <<
	     "\nf5: " << f5 << std::endl;
    // Compare fabs(error) aginst tolerance; if <E -> compute
    double err = h*(1.f/360.f*f0 -
		    128.f/4275.f*f2 -
		    2197.f/75240.f*f3 +
		    1.f/50.f*f4 +
		    2.f/55.f*f5);
    if(!t) std::cout << "|Error|: " << std::fabs(err) << '\n';
    if(std::fabs(err) <= h*E) {
      double v_next = v + h*(16.f/135.f*f0 +
			     6656.f/12825.f*f2 +
			     28561.f/56430.f*f3 -
			     9.f/50.f*f4 +
			     2.f/55.f*f5);
      // add a pair to the vector
      t_v.push_back(std::pair<double, double>(t, v));
      v = v_next;
    }
    // skip this step
    else {
      t -= h;
    }
    // Modify step
    h = 0.9f*h * std::pow(std::fabs(h)*E/std::fabs(err), 1.f/4.f);
  }
  // Print results
  for(auto p : t_v)
    std::cout << p.first << " " << p.second << '\n';
}

int main() {
  rkf();
  return 0;
}
