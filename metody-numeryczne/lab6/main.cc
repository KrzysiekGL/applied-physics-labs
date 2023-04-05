#include <iostream>
#include <math.h>
#include <vector>

double func1(double x, double y1, double y2) {
  return -1.0 * sin(y1);
}
double func2(double x, double y1, double y2) {
  return -1.0 * sin(y1) - 0.5 * y2;
}
double func3(double x, double y1, double y2) {
  return -1.0 * sin(y1) - 0.5 * y2 + 0.9 * cos(0.45*x);
}

std::vector<double> F(double x, std::vector<double> Y, double(*f)(double, double, double)) {
  return std::vector<double> {
    Y[1],
    f(x, Y[0], Y[1])
  };
}

std::vector<double> RK(double x, std::vector<double> Y, double h, double(*f)(double, double, double)) {
  std::vector<double> F0 = F(x      , {Y[0]            , Y[1]}            , f);
  std::vector<double> F1 = F(x+h/2.0, {Y[0]+h/2.0*F0[0], Y[1]+h/2.0*F0[1]}, f);
  std::vector<double> F2 = F(x+h/2.0, {Y[0]+h/2.0*F1[0], Y[1]+h/2.0*F1[1]}, f);
  std::vector<double> F3 = F(x+h    , {Y[0]+h*F2[0]    , Y[1]+h*F2[1]}    , f);

  return std::vector<double>{
    Y[0] + h/6.0 * (F0[0] + 2*F1[0] + 2*F2[0] + F3[0]),
    Y[1] + h/6.0 * (F0[1] + 2*F1[1] + 2*F2[1] + F3[1])
  };
}

std::vector<std::pair<double, double>> solve(double(*func)(double, double, double)) {
  std::vector<std::pair<double, double>> v;
  double h = 0.1;
  // Initial conditions
  double t  = 0.0;
  std::vector<double>  Y = {1.4, 0.0};
  v.push_back({t, Y.at(0)});

  // Solve
  for(int i=1; i<25.0001/h; ++i) {
    // Increment time
    t += h;

    // Calculations
    Y = RK(t, Y, h, func);

    // Append solution for the step
    v.push_back({t, Y.at(0)});
  }

  return v;
}

int main(int argc, char ** argv, char ** env) {
  for(auto p : solve(func1))
    std::cout << p.first << "\t" << p.second << std::endl;
  std::cout << std::endl;
  // solve(func2);
  // solve(func3);
  return 0;
}
