#include <iostream>
#include <vector>
#include <cmath>

std::vector<double> sub(std::vector<double> & A, double lambda) {
  std::vector<double> m;
  int side = std::sqrt(A.size());

  m = A;
  for(int i=0; i<side; ++i) {
    m.at(i*side+i) -= lambda;
  }

  return m;
}

double det(std::vector<double> & matrix, int iteration=0, double D_jm1=0, double D_jm2=0) {
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

int main(int argc, char ** argv, char ** env) {
  const double T = 1.0, L=1.0, h=0.01, N=100, mu = 1.0;
  std::vector<double> A;

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

  return 0;
}
