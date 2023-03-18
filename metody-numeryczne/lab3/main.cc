#include <iostream>
#include <vector>
#include <utility>
#include <cmath>

const double m = 0.01;    // kg
const double g = 9.8;     // m.s2
const double k = 0.0001;  //kg.m-1
const double E = 0.00001; // tolerance

double func(double v) {
  return g - (k/m)*v*v;
}

// Runge-Kutta-Fehlberg
void rkf(double h = 0.2) {
  std::vector<std::pair<double, double>> t_v;
  double v = .0;
  double t = 0.0;
  do {
    // Calculate 6 degrees of the functions
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
    if(!t) std::cout << "f0: " << f0 <<
	     "\nf1: " << f1 <<
	     "\nf2: " << f2 <<
	     "\nf3: " << f3 <<
	     "\nf4: " << f4 <<
	     "\nf5: " << f5 << std::endl;
    // Compare fabs(error) aginst tolerance; if <E -> compute
    double err = h*(f0/360.0
		    -128.0*f2/4275.0
		    -2197.0/75240.0*f3
		    +1.0/50.0*f4
		    +2.0/55.0*f5);
    if(!t) std::cout << "|Error|: " << std::fabs(err) << '\n';

    if(std::fabs(err) <= h*E) {
      double v_next = v + h*(16.0/135.0*f0 +
			     6656.0/12825.0*f2 +
			     28561.0/56430.0*f3 -
			     9.0/50.0*f4 +
			     2.0/55.0*f5);

      // add a pair to the vector
      t_v.push_back(std::pair<double, double>(t, v));
      v = v_next;
      t += h;
    }
    // skip this step
    else {
      t -= h;
    }
    // Modify step
    h = 0.90*h * std::pow(std::fabs(h)*E/std::fabs(err), 1.0/4.0);
  } while(t<=10.0001);
  // Print results
  for(auto p : t_v)
    std::cout << p.first << " " << p.second << '\n';
}

int main() {
  rkf();
  return 0;
}
