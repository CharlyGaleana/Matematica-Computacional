#include <iostream>
#include <cmath>
#include <iomanip>
#include <vector>
#define eu 2.718281828459046
#define PI 3.14159265358979323846

using namespace std;

double biseccion( double(*f)(double), double a, double b, double tol ){
	
	double fa = f(a);
	double c = a;
	
	while( abs(b - a) > tol ){
		c = (a + b) / 2;
		double fc = f(c);
		
		if( a == c || a == b ){
			return c;
		}	
		
		if( fc * fa > 0 ){
			a = c;
			fa = fc;
		} else {
			b = c;
		}
	}	
	
	return c;
}	

double newton( double(*f)(double), double(*fp)(double), double x1, int it ){
	double xprev = x1;
	double xcurr = xprev;
	for(int i = 1; i <= it; i++){
		double aux = xcurr;
		xcurr = xprev - f(xprev) / fp(xprev);
		xprev = aux;
	}
	
	return xcurr;
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

double f1(double x){
	return pow(eu, -(x*x));
}

double f(double x){
	return sqrt(PI) / 2 + simpIntegr( &f1, 0, x, 32 ) - cos(x);
}

double fp(double x){
	return pow(eu, -(x*x)) + sin(x);
}

int main(){
	
	cout << fixed;
	cout << setprecision(15);
	
	/*
	int n = 1;
	double me = pow(10.0, -8.0);
	vector<double> aprox;
	double err = 1;
	while(err > me){
		n *= 2;
		double intgr = simpIntegr( &f1, 0, PI, n );
		aprox.push_back(intgr);
		cout << intgr << "\n";
		if(n > 2)
			err = abs( (intgr - aprox[ aprox.size() - 2 ]) / intgr );
	}
	cout << n << "\n";
	*/
	
	double x = biseccion( &f, 0.0, PI, 0.00000001 );
	cout << x << " " << f(x) << "\n";
	double x1 = newton( &f, &fp, 0, 10 );
	cout << x1 << " " << f(x1) << "\n";
	
}