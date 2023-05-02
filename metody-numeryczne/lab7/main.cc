#include <cmath>
#include <iostream>
#include <vector>

inline double sqr(double n) { return n*n; }

// Central Difference Expression
inline double cde(double y_ip1, double y_im1, double x_i, double const h) {
  return 1.0/(2.0-10.0*sqr(h)) * ((1.0-5.0*h/2.0)*y_ip1 + (1.0+5.0*h/2.0)*y_im1 - 10.0*sqr(h)*x_i);
}

// Error
inline double err(double y_ij, double y_ijm1) {
  return std::fabs((y_ij-y_ijm1)/y_ij);
}

// Return true if the error is greater than the epsilon
bool checkTheErr(std::vector<double> & Y_j, std::vector<double> & Y_jm1, double const eps) {
  for(int i=0; i<Y_j.size(); ++i)
    if(err(Y_j.at(i), Y_jm1.at(i)) > eps) return true;
  return false;
}

// Jacobi iteration scheme
double jis(std::vector<double> & Y_j, std::vector<double> & Y_jm1, std::vector<double> & X, int const i, double const h) {
  return cde(Y_jm1.at(i+1), Y_jm1.at(i-1), X.at(i), h);
}

// Gauss-Seidel itration scheme
double gsis(std::vector<double> & Y_j, std::vector<double> & Y_jm1, std::vector<double> & X, int const i, double const h) {
  return cde(Y_jm1.at(i+1), Y_j.at(i-1), X.at(i), h);
}

void solve(double(*iter_scheme)(std::vector<double>&, std::vector<double>&, std::vector<double>&, int const, double const)) {
  // Grid from 0 to 1, divided into N+1 iteration steps (from 0 to 1)
  // with boundry conditions y(0)=0, y(1)=100 (fixed values)
  // X_1 domain (grid of points) is X_i = 0, 0.1, 0.2, ... , 1.0 -> N = 11
  // and initial conditions Y(x_i) = Y_i0 = 0, 10, 20, ... , 100
  // the step size between values is 0.1 (for x)
  int const N = 11;
  double const h = 0.1;
  double const epsilon = 0.0005;

  std::vector<double> X_i;
  std::vector<std::vector<double>> Y_ij;

  // Populate the vector for grid of points
  for(int i=0; i<N; ++i)
    X_i.push_back(double(i)/10.0);

  // Populate initial conditions (j=0)
  Y_ij.push_back(std::vector<double>());
  for(int i=0; i<N; ++i)
    Y_ij.at(0).push_back(i*10.0);

  // Repeate calulations until the error is LE to the Epsilon
  do {
    // Add new vector for the iteration (another j)
    // Don't forget about the fix values: 0 and 100
    Y_ij.push_back(std::vector<double>());
    Y_ij.back().push_back(0.0);

    // Execute calculations for each element
    for(int i=1; i<N-1; ++i)
      Y_ij.back().push_back(iter_scheme(Y_ij.back(), Y_ij.at(Y_ij.size()-2), X_i, i, h));
    Y_ij.back().push_back(100.0);

    // Check the error to find out wheter to continue or cease calculations
  } while(checkTheErr(Y_ij.back(), Y_ij.at(Y_ij.size()-2) , epsilon));

  // Print results
  std::cout << "Iteration (count from 0): " << Y_ij.size()-1 << '\n';
  for(int i=0; i<N; ++i)
    std::cout << "x: " << X_i.at(i) << " y: " << Y_ij.back().at(i) << '\n';
}

int main(int argc, char ** argv, char ** env) {
  std::cout << "Jacobi iteration scheme:\n";
  solve(jis);

  std::cout << "Gauss-Seidel iteration scheme:\n";
  solve(gsis);

  return 0;
}
