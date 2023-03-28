#include <iostream>
#include <vector>

// given equation for y''
double func(double y) {
  return -4.0*y;
}

// Simple Euler method
double SE(double y_k, double h, double expression) {
  return y_k + h * expression;
}

// Improved Euler method
double IE(double y_k, double h, double expression) {
  return y_k + h/2.0 * expression;
}

void solve(double(*method)(double, double, double)) {
  const double h = 0.2;
  std::vector<double> x;
  std::vector<double> y;
  // initial conditions
  double y_1 = 1;
  double y_2 = 0;

  x.push_back(0);
  y.push_back(y_1);

  for(int i=1; i<=6.0001/h; ++i) {
    // Calculations
    double exp_1, exp_2;
    if(method == SE) {
      exp_1 = y_2;
      exp_2 = func(y_1);
    }
    else if(method == IE) {
      exp_1 = 2.0*y_2 + h*func(y_1);
      exp_2 = func(y_1) + func(y_1 + h*y_2);
    }
    else {
      std::cout << "Error: non method provided\n";
      return;
    }

    double y_1_next = method(y_1, h, exp_1);
    double y_2_next = method(y_2, h, exp_2);

    y_1 = y_1_next;
    y_2 = y_2_next;

    // Save the results
    x.push_back(i*h);
    y.push_back(y_1);
  }

  // print results
  for(int i=0; i<x.size(); ++i)
    std::cout << "x: " << x.at(i) << " y: " << y.at(i) << '\n';
}

int main(int argc, char ** argv, char ** env) {
  std::cout << "Simple Euler method with step 0.2\n";
  solve(SE);
  std::cout << "\nImproved Euler method with step 0.2\n";
  solve(IE);
  return 0;
}
