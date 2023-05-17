#include <iostream>
#include <vector>
#include <cmath>
#include <numbers>

double analytical_w(int n, double L, double T, double mu) {
  return n*std::numbers::pi/L * std::sqrt(T/mu);
}

std::vector<double> sub(std::vector<double> A, double lambda) {
  std::vector<double> m;
  int side = std::sqrt(A.size());

  m = A;
  for(int i=0; i<side; ++i) {
    m.at(i*side+i) -= lambda;
  }

  return m;
}

double det(std::vector<double> matrix, int iteration=0, double D_jm1=0, double D_jm2=0) {
  double D_j;
  int side = std::sqrt(matrix.size());

  // Calculte the determint
  if(iteration == 0)
    D_j = matrix.at(0);
  else if(iteration == 1)
    D_j = matrix.at(side+1)*D_jm1 - matrix.at(side)*matrix.at(1);
  else {
    D_j = matrix.at(iteration*side+iteration)*D_jm1 -
      matrix.at(iteration*side+(iteration-1))*matrix.at((iteration-1)*side+iteration)*D_jm2;
  }

  // If there are still elements, convey the calculations further
  if(iteration<side-1)
    D_j = det(matrix, iteration+1, D_j, D_jm1);

  return D_j;
}

void matrix_A_prep(std::vector<double> & A, const int N,
		 const double T, const double mu)
{
  for(int i=0; i<N; ++i)
    for(int j=0; j<N; ++j)
      A.push_back(0);

  for(int i=0; i<N; ++i) {
    if(i==0) {
      A.at(0) = 2*T/mu;
      A.at(1) = -T/mu;
    }
    else if(i==N-1) {
      A.at(i*N+i) = 2*T/mu;
      A.at(i*N+i-1) = -T/mu;
    }
    else {
      A.at(i*N+i-1) = -T/mu;
      A.at(i*N+i) = 2*T/mu;
      A.at(i*N+i-1) = -T/mu;
    }
  }
}

double bisection(std::vector<double> & A, double lambda_l, double lambda_r, const double h) {
  double lambda_m = (lambda_l+lambda_r)/2;
  for(int i=0; i<100; ++i) {
    if(det(sub(A, lambda_l)) * det(sub(A, lambda_m)) >= 0)
      lambda_l = lambda_m;
    else
      lambda_r = lambda_m;
    lambda_m = (lambda_l+lambda_r)/2;
  }
  return std::sqrt(lambda_m)/h;
}

int main(int argc, char ** argv, char ** env) {
  const double T = 1.0, L=1.0, h=0.01, N=100, mu = 1.0;
  std::vector<double> A;

  // 2)
  matrix_A_prep(A, N, T, mu);
  std::cout << det(A) << std::endl;
  // // n = 1
  // double lambda_l = h*h*std::pow(analytical_w(1, L, T, mu), 2)-0.0001;
  // double lambda_r = h*h*std::pow(analytical_w(1, L, T, mu), 2)+0.0001;
  // std::cout << "Omega for n=1: " << bisection(A, lambda_l, lambda_r, h) <<" "<< analytical_w(1, L, T, mu) << '\n';
  // // n = 2
  // lambda_l = h*h*std::pow(analytical_w(2, L, T, mu), 2)-0.0001;
  // lambda_r = h*h*std::pow(analytical_w(2, L, T, mu), 2)+0.0001;
  // std::cout << "Omega for n=1: " << bisection(A, lambda_l, lambda_r, h) <<" "<< analytical_w(2, L, T, mu) << '\n';
  // // n = 3
  // // n = 4
  // // n = 5

  return 0;
}
