#include <iostream>
#include <vector>
#include <cmath>

#define PI 3.14159265

// Matrix reprezented only by it's diagonal (three lines)
class Diagonal {
public:
  Diagonal(){}

  void initialize(double T, double(*mu)(double x), int N) {
    for(int i=0; i<N; i++) {
      // First row
      if(i==0) {
	diagonal.push_back(2*T/mu(i));
	diagonal.push_back(-T/mu(i));
      }
      // Last row
      else if(i==N-1) {
	diagonal.push_back(-T/mu(i));
	diagonal.push_back(2*T/mu(i));
      }
      // Everyting else in between
      else {
	diagonal.push_back(-T/mu(i));
	diagonal.push_back(2*T/mu(i));
	diagonal.push_back(-T/mu(i));
      }
    }
  }

  void clear() {
    diagonal.clear();
  }

  double det(double lambda) {
    //int N = (diagonal.size()+2)/3;
    int size = diagonal.size();
    double d1, d2;
    for(int i=0; i<size;) {
      if(i==0){
	d1 = diagonal.at(i);
	i+=2;
      }
      else if(i==2) {
	d2 = (diagonal.at(i+1)-lambda)*d1 - diagonal.at(i)*diagonal.at(i-1);
	i+=3;
      }
      else {
	double d3 = (diagonal.at(i+1)-lambda)*d2 - diagonal.at(i)*diagonal.at(i-1)*d1;
	d1 = d2;
	d2 = d3;
	i+=3;
      }
    }
    return d2;
  }
private:
  std::vector<double> diagonal;
};

// Bisection method
double bisection(Diagonal & d, double lL, double lR) {
  double lM;
  for(int i=0; i<100; ++i) {
    lM = (lL + lR)/2;
    if(d.det(lL)*d.det(lM)>=0)
      lL = lM;
    else
      lR = lM;
  }
  return (lL + lR)/2;
}

// Constant mu
double const_mu(double x) {
  return 1.0;
}

// Variating mu
double mu(double x) {
  return 1.0 + (x-0.5);
}

// Analytical solution for the omaega, w
double analytical_omega(double n, double L, double T, double(*mu)(double x), double x=0) {
  return n*PI/L*std::sqrt(T/mu(x));
}

double omega(double lambda, double h) {
  return std::sqrt(lambda)/h;
}

double lambda(double omega, double h) {
  return h*h*omega*omega;
}

int main(int argc, char ** argv, char ** env) {
  const double T=1.0, L=1.0, h=0.01, N=100;
  Diagonal A;
  int n = argc > 1 ? atoi(argv[1]) : 1;

  // 2) mu is constant
  A.initialize(T, const_mu, N);
  // for(int i=1; i<=5; ++i) {
  //   double l = bisection(A,
  // 			 lambda(analytical_omega(i, L, T, const_mu), h)-0.0000001,
  // 			 lambda(analytical_omega(i, L, T, const_mu), h)+0.0000001);
  //   std::cout << "Omega: " << omega(l, h)
  // 	      << " omega: " << analytical_omega(i, L, T, const_mu)
  // 	      << '\n';
  // }
  double l = lambda(analytical_omega(n, L, T, const_mu), h);
  std::cout << "lambda: " << l << " det: " << A.det(l) <<'\n';

  // 3) mu = mu_0 + (x-0.5)
  A.clear();
  A.initialize(T, mu, N);

  return 0;
}
