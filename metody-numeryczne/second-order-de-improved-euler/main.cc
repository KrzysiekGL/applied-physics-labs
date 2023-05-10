#include <iostream>
#include <cmath>
#include <vector>

// Analytical solution for the pendulum (dissipation, driving force)
double theta(double t, double theta_0=1.0, double g_over_l=1.0) {
  // in radians
  return theta_0 * std::cos(std::sqrt(g_over_l)*t);
}

double theta_dot(double t, double theta_0=1.0, double g_over_l=1.0) {
  // in radians per second
  return -theta_0 * std::sqrt(g_over_l) * std::sin(std::sqrt(g_over_l)*t);
}

// Second order DE -- paramteres embeded inside
double func(double t, double y1, double y2,
	    double g_over_l=1.0, double q=0.5, double a=0.9, double omega_0=0.48)
{
  // in radians per second^2
  return -q*y2 - g_over_l*std::sin(y1) + a*std::cos(omega_0*t);
}

// Solution
void solve() {
  std::vector<double> t;
  std::vector<std::vector<double>> Y; // {y_1(t), y_2(t)}

  // Step size and number of steps to calculate (calculate from t=0 to t=10)
  const double h = 0.01;
  const int N = int(10.0/h);

  // Initial conditions
  t.push_back(0);
  Y.push_back(std::vector<double>{1,0});

  // // Calculations - Improved Euler method
  // for(int i=1; i<N; ++i) {
  //   const double T = t.back();
  //   const double y1_0 = Y.back().at(0);
  //   const double y2_0 = Y.back().at(1);
  //   const double y1_1 = y1_0+h/2*(y2_0+y2_0+h*func(T, y1_0, y2_0));
  //   const double y2_1 = y2_0+h/2*(func(T, y1_0, y2_0)+func(T+h, y1_0+h*y2_0, y2_0+h*func(T, y1_0, y2_0)));
  //   t.push_back(i*h);
  //   Y.push_back(std::vector<double>{y1_1, y2_1});
  // }

  // Calculations - Modified Euler method
  for(int i=1; i<N; ++i) {
    const double T = t.back();
    const double y1_0 = Y.back().at(0);
    const double y2_0 = Y.back().at(1);
    const double y1_1 = y1_0+h*(y2_0+h/2*func(T, y1_0, y2_0));
    const double y2_1 = y2_0+h*(func(T+h/2, y1_0+h/2*y2_0, y2_0+h/2*func(T, y1_0, y2_0)));
    t.push_back(i*h);
    Y.push_back(std::vector<double>{y1_1, y2_1});
  }

  // Print the results; compare along the analytical solution
  std::cout << "Solution (err is abs(analytical - numerical)):\n";
  std::cout << "t, y1, (a)y1, err_y1, y2, (a)y2, err_y2";
  for(int i=0; i<N; ++i) {
    const double T = t.at(i);
    const double y1 = Y.at(i).at(0);
    const double a_y1 = theta(T);
    const double err_y1 = std::fabs(a_y1 - y1);
    const double y2 = Y.at(i).at(1);
    const double a_y2 = theta_dot(T);
    const double err_y2 = std::fabs(a_y2 - y2);
    std::cout << T << ", "
	      << y1 << ", " << a_y1 << ", " << err_y1 << ", "
	      << y2 << ", " << a_y2 << ", " << err_y2 << '\n';
  }
}

int main(int argc, char ** argv, char ** env) {
  solve();
  return 0;
}
