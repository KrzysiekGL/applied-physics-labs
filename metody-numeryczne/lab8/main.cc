#include <cmath>
#include <iostream>
#include <stdexcept>
#include <vector>
#include <numbers>

inline double sqr(double n) { return n*n; }

// Analytical solution for the equation
double analytical(double x) {
  double e = std::numbers::e;
  static const double C =
    1/(2.0*std::pow(e,5.0/2.0)*std::sin(std::sqrt(15.0)/2.0)) *
    (197.0 + std::pow(e,5.0/2.0) * std::cos(std::sqrt(15.0)/2.0));
  return std::pow(e,(5.0/2.0)*x) *
    (-0.5 * std::cos((std::sqrt(15.0)/2.0)*x) +
     C * std::sin((std::sqrt(15.0)/2.0)*x)) +
     x + 0.5;
}

// Error
inline double err(double y_ij, double y_ijm1) {
  return std::fabs((y_ij-y_ijm1)/y_ij);
}

// Return true if the error is greater than the epsilon
bool checkTheErr(std::vector<double> const & Y_j, std::vector<double> const & Y_jm1, double const eps) {
  for(int i=0; i<Y_j.size(); ++i)
    if(err(Y_j.at(i), Y_jm1.at(i)) > eps) return true;
  return false;
}

// Central Difference Expressions (for i=2,..,N-2; i=1; i=N-1 respectively)
inline double cdeN(double y_im4, double y_im3, double y_im2, double y_im1,
		   double y_ip1, double y_ip2, double y_ip3, double y_ip4,
		   double x_i, double h)
{
  return 1.0/(-30.0 + 120.0 * sqr(h)) *
    ((1.0 - 5.0*h)*y_ip2 +
     (-16.0 + 40.0*h)*y_ip1 +
     (-16.0 - 40.0*h)*y_im1 +
     (1.0 + 5.0*h)*y_im2 +
     120.0*sqr(h)*x_i);
}

inline double cdeNe1(double y_im4, double y_im3, double y_im2, double y_im1,
		   double y_ip1, double y_ip2, double y_ip3, double y_ip4,
		   double x_i, double h)
{
  return 1.0/(-15.0 + 50.0*h + 120.0*sqr(h)) *
    (-y_ip4 +
     (6.0 + 5.0*h)*y_ip3 +
     (-14.0 - 30.0*h)*y_ip2 +
     (4.0 + 90.0*h)*y_ip1 +
     (-10.0 - 15.0*h)*y_im1 +
     120.0*sqr(h)*x_i);
}

inline double cdeNm1(double y_im4, double y_im3, double y_im2, double y_im1,
		   double y_ip1, double y_ip2, double y_ip3, double y_ip4,
		   double x_i, double h)
{
  return 1.0/(-15.0 - 50.0*h + 120.0*sqr(h)) *
    (-y_im4 +
     (6.0 - 5.0*h)*y_im3 +
     (-14.0 + 30.0*h)*y_im2 +
     (4.0 - 90.0*h)*y_im1 +
     (-10.0 + 15.0*h)*y_ip1 +
     120.0*sqr(h)*x_i);
}

// Gauss-Seidel itration scheme
double gsis(std::vector<double> & Y_j, std::vector<double> & Y_jm1, std::vector<double> & X, int const i, double const h, int const N) {
  const int vjs = Y_j.size();
  const int vms = Y_jm1.size();
  // In
  double y_im4, y_im3, y_im2, y_im1, y_ip1, y_ip2, y_ip3, y_ip4;
  y_im4 = vjs>4 ? Y_j.at(i-4) : 0;
  y_im3 = vjs>3 ? Y_j.at(i-3) : 0;
  y_im2 = vjs>2 ? Y_j.at(i-2) : 0;
  y_im1 = vjs>1 ? Y_j.at(i-1) : 0;
  y_ip1 = vms>i+1 ? Y_jm1.at(i+1) : 0;
  y_ip2 = vms>i+2 ? Y_jm1.at(i+2) : 0;
  y_ip3 = vms>i+3 ? Y_jm1.at(i+3) : 0;
  y_ip4 = vms>i+4 ? Y_jm1.at(i+4) : 0;
  // Out
  double y_i;
  if(1==i)
    y_i = cdeNe1(y_im4, y_im3, y_im2, y_im1,
		 y_ip1, y_ip2, y_ip3, y_ip4,
		 X.at(i), h);
  else if(N-1==i)
    y_i = cdeNm1(y_im4, y_im3, y_im2, y_im1,
		 y_ip1, y_ip2, y_ip3, y_ip4,
		 X.at(i), h);
  else if(1 < i && i < N-1)
    y_i = cdeN(y_im4, y_im3, y_im2, y_im1,
		 y_ip1, y_ip2, y_ip3, y_ip4,
		 X.at(i), h);
  else
    y_i = 0;
  return y_i;
}

void solve(double(*iter_scheme)(std::vector<double>&, std::vector<double>&, std::vector<double>&, int const, double const, int const)) {
  // Grid from 0 to 1, divided into N+1 iteration steps (from 0 to 1)
  // with boundry conditions y(0)=0, y(1)=100 (fixed values)
  // X_1 domain (grid of points) is X_i = 0, 0.1, 0.2, ... , 1.0 -> N = 11
  // and initial conditions Y(x_i) = Y_i0 = 0, 10, 20, ... , 100
  // the step size between values is 0.1 (for x)
  constexpr double const h = 0.05;
  constexpr int N = int(1.0/h);
  const double epsilon = 0.0000005;

  std::vector<double> X_i;
  std::vector<std::vector<double>> Y_ij;

  // Populate the vector for grid of points
  for(int i=0; i<=N; ++i)
    X_i.push_back(double(i)*h);

  // Populate initial conditions (j=0)
  Y_ij.push_back(std::vector<double>());
  for(int i=0; i<=N; ++i)
    Y_ij.at(0).push_back(i*h*100.0);

  // Repeate calulations until the error is LE to the Epsilon
  do {
    // Add new vector for the iteration (another j)
    // Don't forget about the fix values: 0 and 100
    Y_ij.push_back(std::vector<double>());
    Y_ij.back().push_back(0.0);

    // Execute calculations for each element
    for(int i=1; i<N; ++i)
      Y_ij.back().push_back(iter_scheme(Y_ij.back(), Y_ij.at(Y_ij.size()-2), X_i, i, h, N));

    // Fix value as the last element
    Y_ij.back().push_back(100.0);

    // Check the error to find out wheter to continue or cease calculations
  } while(checkTheErr(Y_ij.back(), Y_ij.at(Y_ij.size()-2) , epsilon));

  // Print results compared with the analytical solution
  std::cout << "Iteration (count from 0): " << Y_ij.size()-1 << '\n';
  for(int i=0; i<=N; ++i) {
    const double x = X_i.at(i);
    const double y = analytical(x);
    const double Y = Y_ij.back().at(i);
    std::cout << "x: " << X_i.at(i) << " Y: " << Y
	      << " \t\tanalytical y("<<x<<"): " << y
	      << " \tdifference (y-Y): " << y-Y << '\n';
  }
}

int main(int argc, char ** argv, char ** env) {
  std::cout << "Gauss-Seidel iteration scheme:\n";
  solve(gsis);
  return 0;
}
