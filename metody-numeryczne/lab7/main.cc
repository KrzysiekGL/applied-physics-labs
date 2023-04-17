#include <cmath>
#include <iostream>
#include <vector>

inline double sqr(double n) { return n*n; }

// Central Difference Expression
inline double cde(double y_ip1, double y_im1, double x_i, double h=0.1) {
  return 1/(2-10*sqr(h)) * ((1-5*h/2)*y_ip1 + (1+5*h/2)*y_im1 - 10*sqr(h)*x_i);
}

// Error
inline double err(double y_ij, double y_ijm1, double eps=0.0005) {
  return std::fabs((y_ij-y_ijm1)/y_ij);
}

// Jacobi iteration scheme
void jis() {}

// Gauss-Seidel itration scheme
void gsis() {}

void solve() {
  // Grid from 0 to 1, divided into N+1 iteration steps (from 0 to 1)
  // with boundry conditions y(0)=0, y(1)=100 (fixed values)
  // X_1 domain (grid of points) is X_i = 0, 0.1, 0.2, ... , 1.0
  // and initial conditions Y(x_i) = Y_i0 = 0, 10, 20, ... , 100
  // the step size between values is 0.1 (for x)
  std::vector<double> X_i;
  std::vector<std::vector<double>> Y_ij;

  // Populate the vector for grid of points
  for(int i=0; i<11; ++i)
    X_i.push_back(double(i)/10);

  // Populate initial conditions (j=0)
  Y_ij.push_back(std::vector<double>());
}

int main(int argc, char ** argv, char ** env) {
  solve();
  return 0;
}
