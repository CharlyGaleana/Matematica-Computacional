#include <iostream>
#include <cmath>
#include <iomanip>
#include <vector>
#define PI 3.14159265358979323846

using namespace std;

double sen(double x){
	return sin(x);
}

double f1(double x){
	return sin(3 * x) * pow( cos(2 * x), 2.0 ) - pow( sin(4 * x), 4.0 ); 
}

double f2(double x){
	return log(x) / (1.0 + x);
}

double f3(double x){
	return sqrt( 2 + sqrt(1 + x) );
}

double trapIntegr( double (*f)(double), double a, double b, int n ){
	double h = (b - a) / ( (double) n );
	double sum = f(a)/2.0 + f(b)/2.0;
	
	double x = a;
	for(int i = 1; i < n; i++){
		x += h;
		sum += f(x); 
	}
	sum *= h;
	
	return sum;
	
}

double simpIntegr( double (*f)(double), double a, double b, int n ){
	double h = (b - a) / ( (double) n );
	double sum = (f(a) + f(b)) / 2.0;
	
	double x = a;
	for(int i = 1; i < n; i++){
		x += h;
		sum += f(x);
	}
	
	x = a;
	for(int i = 1; i <= n; i++){
		sum += 2.0 * f(x + h/2.0);
		x += h;
	}
	
	sum *= (h / 3.0);
	return sum;
}

int main() {
	cout << fixed;
	cout << setprecision(15);
	//cout << trapIntegr( &sen, 0, PI, 100 ) << "\n";
	//cout << simpIntegr( &sen, 0, PI, 100 ) << "\n";
	
	/*int n = 1;
	for(int i = 1; i <= 7; i++){
		n *= 10;
		double integr = trapIntegr( &sen, 0, PI, n );
		cout << integr << " " << 2.0 - integr << "\n";
	}
	
	cout << "\n\n";
	
	n = 1;
	for(int i = 1; i <= 7; i++){
		n *= 10;
		double integr = simpIntegr( &sen, 0, PI, n );
		cout << integr << " " << 2.0 - integr << "\n";
	}*/
	
	int n = 1;
	double me = pow(10.0, -6.0);
	vector<double> aprox;
	double err = 1;
	while(err > me){
		n *= 2;
		double intgr = simpIntegr( &f3, 0, 4, n );
		aprox.push_back(intgr);
		cout << intgr << "\n";
		if(n > 2)
			err = abs( (intgr - aprox[ aprox.size() - 2 ]) / intgr );
	}
	cout << n << "\n";
	
	return 0;
}
