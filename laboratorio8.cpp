#include <iostream>
#include <vector>
#include <cmath>
#define PI 3.14159265358979323846
using namespace std;

struct poly{
	int n;
	vector<double> x;
	vector<double> f;
	
	poly(int _n, vector<double> _x, vector<double> _f){
		x = _x;
		f = _f;
		n = _n;
	}
	
	double lagrangePolynomial(int j, double t){
		double ret = 1.0;
		int i;
		for(i = 0; i <= n; i++)
			if(i != j)
				ret *= (t - x[i]) / (x[j] - x[i]);
			
		return ret;
	}
	
	double evaluate(double t){
		double ret = 0.0;
		int i;
		for(i = 0; i <= n; i++){
			//cout << lagrangePolynomial(i, t) << "\n";
			ret += f[i] * lagrangePolynomial(i, t);
		}
		
		return ret;
	}
	
};

double func(double x){
	return (1.0) / (1.0 + (x * x));
}

double point(int i, int n){
	return 5.0 * cos( ( (2 * (double)(n - i) + 1) / (2 * n + 2) ) * PI );
}

int main(){
	
	int n;
	int i;
	
	for(n = 2; n <= 256; n *= 2){
		
		double l = -5.0, r = 5.0;
		
		vector<double> x(n + 1);
		vector<double> f(n + 1);
		
		vector<double> x1(n + 1);
		vector<double> f1(n + 1);
		
		double h = (r - l) / (double)n;
		for(i = 0; i <= n; i++){
			x[i] = l + (double)(i) * h;
			f[i] = func( x[i] );
			
			x1[i] = point(i, n);
			f1[i] = func( x1[i] );
		}
		
		poly * p = new poly(n, x, f);
		poly * p1 = new poly(n, x1, f1);
		
		double maxabs = 0.0, maxrel = 0.0;
		for(i = 0; i < n; i++){
			double pm = (x[i] + x[i + 1]) / 2;
			double abserr = abs(func(pm) - p->evaluate(pm));
			//cout << p->evaluate(pm) << " " << func(pm) << "\n";
			
			maxabs = max( maxabs, abserr );
			maxrel = max( maxrel, abs( abserr / func(pm) ) );
		}
		
		double maxabs1 = 0.0, maxrel1 = 0.0;
		for(i = 0; i < n; i++){
			double pm = (x1[i] + x1[i + 1]) / 2;
			double abserr = abs(func(pm) - p1->evaluate(pm));
			//cout << p->evaluate(pm) << " " << func(pm) << "\n";
			
			maxabs1 = max( maxabs1, abserr );
			maxrel1 = max( maxrel1, abs( abserr / func(pm) ) );
		}
		
		cout << n << "\n:\n";
		cout << "maxerror " << maxabs << " "<< maxrel <<"\n";
		cout << "maxerror " << maxabs1 << " "<< maxrel1 <<"\n";
		cout << "\n";
		
	}
	
	return 0;
}