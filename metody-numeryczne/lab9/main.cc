#include <iostream>
#include <vector>
#include <cmath>

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

  return 0;
}
