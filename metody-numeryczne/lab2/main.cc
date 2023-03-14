#include <iostream>
#include <vector>
#include <cmath>

template<typename T>
void print_stdvec(std::vector<T> vec_x, std::vector<T> vec_y) {
	for(int i=0; i<vec_x.size(); ++i) {
		std::cout << "x: " << vec_x[i] << " y: " << vec_y[i] << std::endl;
	}
 std::cout << std::endl;
}

float derivative(float y) {
	return y*y + 1.f;
}

void euler(float step) {
	std::cout << "Euler for step " << step << '\n';
	std::vector<float> vec_y, vec_x;
	float y_k_1=0;
	for(float H=0; H<1.000001; H+=step) {
		vec_x.push_back(H);
		vec_y.push_back(y_k_1);
		y_k_1 = y_k_1 + step * derivative(y_k_1);
	}
	print_stdvec<float>(vec_x, vec_y);
}

void runge_kutta(float step) {
	std::cout << "Runge-Kutta for step " << step << '\n';
	std::vector<float> vec_y, vec_x;
	float y_k_1=0;
	for(float h=0; h<1.00001; h+=step) {
		vec_x.push_back(h);
		vec_y.push_back(y_k_1);
		float y_mid = y_k_1 + step/2 * derivative(y_k_1);
		y_k_1 = y_k_1 + step * derivative(y_mid);
	}
	print_stdvec(vec_x, vec_y);
}

void analytic(float step) {
	std::cout << "Analytical solution for step " << step << '\n';
	std::vector<float> vec_x, vec_y;
	for(float x=0; x<1.0001; x+=step) {
		vec_x.push_back(x);
		vec_y.push_back(tan(x));
	}
	print_stdvec<float>(vec_x, vec_y);
}

int main(int argc, char ** argv) {
	euler(0.05);
	runge_kutta(0.05);
	analytic(0.05);
	return 0;
}
