#include <iostream>
#include <vector>

double y_prim(double y) {
	return y*y+1.0;
}

// only to calculate x1 for AB2
double RK2(double h, double y_p) {
	double f0 = y_prim(y_p);
	return y_p + h * y_prim(y_p + h/2.0 * f0);
}

void AB2(double h=0.05) {
	std::vector<double> x;
	std::vector<double> y;

	// initial condition and second value (x1)
	x.push_back(0.0);
	y.push_back(0.0);

	x.push_back(h);
	y.push_back(RK2(h, y.back()));

	// AB
	double X = 2*h;
	do {
		double size = y.size();
		double y_2p = y.at(size-2);
		double y_1p = y.at(size-1);
		double y_next = y_1p + h/2.0 * (3*y_prim(y_1p) - y_prim(y_2p));
		x.push_back(X);
		y.push_back(y_next);
		X += h;
	} while(X<=1.0001);

	// Print the results
	std::cout << "Adams-Bashforth method 2nd order\n";
	for(int i=0; i<x.size(); ++i)
		std::cout << "x: " << x[i] << " y:" << y[i] << '\n';
}

// only to calculate x1, x2 and x3 for AB4
double RK4(double h, double y_p) {
	double f0 = y_prim(y_p);
	double f1 = y_prim(y_p + h/2.0*f0);
	double f2 = y_prim(y_p + h/2.0*f1);
	double f3 = y_prim(y_p + h*f2);
	return y_p + h/6.0*(f0 + 2.0*f1 + 2.0*f2 + f3);
}

void AB4(double h=0.05) {
	std::vector<double> x;
	std::vector<double> y;

	// initial condition and x1, x2, and x3
	x.push_back(0.0);
	y.push_back(0.0);

	x.push_back(h);
	y.push_back(RK4(h, y.back()));

	x.push_back(2*h);
	y.push_back(RK4(h, y.back()));

	x.push_back(3*h);
	y.push_back(RK4(h, y.back()));

	// AB
	double X = x.back()+h;
	do {
		double size = y.size();
		double y_4p = y.at(size-4);
		double y_3p = y.at(size-3);
		double y_2p = y.at(size-2);
		double y_1p = y.at(size-1);
		double y_next = y_1p + h/24.0 * (
																		 55*y_prim(y_1p)
																		 -59*y_prim(y_2p)
																		 +37*y_prim(y_3p)
																		 -9*y_prim(y_4p)
																		 );

		x.push_back(X);
		y.push_back(y_next);
		X += h;
	} while(X<=1.0001);

	// Print the results
	std::cout << "Adams-Bashforth method 4th order\n";
	for(int i=0; i<x.size(); ++i)
		std::cout << "x: " << x[i] << " y:" << y[i] << '\n';
}

int main(int argc, char ** argv, char ** env) {
	AB2();
	AB4();
	return 0;
}
