#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <iomanip>
#define eu 2.718281828459046
#define PI 3.14159265358979323846

using namespace std;

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

double reglaConPeso( double (*f)(double), double h ){
	return (h/15) * ( 19 * f(h/4) - 13 * sqrt(2) * f(h/2) + 9 * sqrt(3) * f( (3 * h) / 4 ) );
}

double reglaConPesp2( double (*f)(double), double h ){
	return (1 / ( 3 * sqrt(6) - 6 ) ) * ( -4 * sqrt(3) * f(PI/4) + 8 * f(PI/3) - 4 * f(PI/2) );
}

double integracionMixta( double (*f)(double), int n){
	double h = (1.0) / ( (double) n );
	double sum = 0;
	
	sum += reglaConPeso( f, h );
	sum += simpIntegr( f, h, 1, n - 1 );
	return sum;
}

double f( double x ){
	return ( pow(eu, x) / sqrt(x) );
}


double derv( double (*f)(double), double x, double h ){
	return ( f(x + h) - f(x - h) ) / (2 * h);
}

double fp( double x ){
	return ( (4.0/3.0) * pow(x, 1.5) * pow(eu, x) );
}

double f1( double x ){
	return sqrt(x);
}

double f2( double x ){
	return sin(2 * x) * cos(3 * x) + 5 * sin(3 * x) * cos(2 * x);
}

int main(){
	
	cout << fixed;
	cout << setprecision(10);
	
	/*
	int n = 1;
	double me = pow(10.0, -6.0);
	vector<double> aprox;
	double err = 1;
	
	cout << fixed;
	cout << setprecision(10);
	
	while(err > me){
		n *= 2;
		double intgr = integracionMixta( f, n );
		aprox.push_back(intgr);
		cout << intgr << "\n";
		if(n > 2)
			err = abs( (intgr - aprox[ aprox.size() - 2 ]) / intgr );
	}
	cout << n << "\n";
	*/
	
	/*
	int n = 1;
	double me = pow(10.0, -6.0);
	vector<double> aprox;
	double err = 1;
	
	cout << fixed;
	cout << setprecision(10);
	
	
	while(err > me){
		n *= 2;
		double intgr = (2 * eu) / 3 + simpIntegr( fp, 0, 1, n );
		aprox.push_back(intgr);
		cout << intgr << "\n";
		if(n > 2)
			err = abs( (intgr - aprox[ aprox.size() - 2 ]) / intgr );
	}
	cout << n << "\n";*/

	/*
	double h = 2;
	double me = pow(10.0, -6.0);
	vector<double> aprox;
	double err = 1;
	
	while(err > me){
		h /= 2.0;
		double de = derv( sqrt, 2, h );
		aprox.push_back(de);
		cout << de << "\n";
		if(h < 1.0)
			err = abs( (de - aprox[ aprox.size() - 2 ]) / de );
	}
	cout << h << "\n";*/

	cout << reglaConPeso( f2, PI ) << "\n";
	
	int n = 1;
	double me = pow(10.0, -6.0);
	vector<double> aprox;
	double err = 1;
	
	cout << fixed;
	cout << setprecision(10);
	
	
	while(err > me){
		n *= 2;
		double intgr = simpIntegr( f2, 0, PI, n );
		aprox.push_back(intgr);
		cout << intgr << "\n";
		if(n > 2)
			err = abs( (intgr - aprox[ aprox.size() - 2 ]) / intgr );
	}
	cout << n << "\n";
	
	return 0;
}
	