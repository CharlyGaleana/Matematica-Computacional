#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

struct formaInterpolante{
	
	vector<double> c;
	vector<double> x;
	double ** F;
	int n;
	
	formaInterpolante( vector<double> _x, vector<double> f ){
		x = _x;
		n = x.size();
		F = new double * [n];
		int i, j;
		
		for(i = 0; i < n; i++)
			F[i] = new double[n];
			
		for(i = 0; i < n; i++)
			F[i][i] = f[i];
			
		for(j = 1; j < n; j++)
			for(i = j - 1; i >= 0; i--)
				F[i][j] = (F[i + 1][j] - F[i][j - 1]) / (x[j] - x[i]);
	
		for(i = 0; i < n; i++)
			c.push_back( F[0][i] );
	
	}
	
	double evaluate(double t){
		double ret = 0.0;
		int i;
		
		for(i = n - 2; i >= 0; i--){
			ret += c[i];
			if(i) ret *= (t - x[i - 1]);
		}
		
		return ret;
	}
	
};

struct interpolacionLagrange{
	
	vector<double> x, f;
	int n;
	
	interpolacionLagrange(vector<double> _x, vector<double> _f){
		x = _x;
		f = _f;
		n = x.size();
	}
	
	double polinomioLagrange(double t, int j){
		double ret = 1.0;
		int i;
		
		for(i = 0; i < n; i++)
			if(i != j)
				ret *= (t - x[i]) / (x[j] - x[i]);
		
		return ret;
	}
	
	double evaluate(double t){
		double ret = 0.0;
		int i;
		
		for(i = 0; i < n; i++)
			ret += f[i] * polinomioLagrange(t, i);
		return ret;
	}
		
};

double coef[11] = {1, -10, 45, -120, 210, -252, 210, -120, 45, -10, 1};

double poli(double x){
	double ret = 0.0;
	for(int i = 0; i <= 10; i++)
		ret += coef[i] * pow(x, (double)(i));
	return ret;
}

double poli10(double x){
	return pow(x - 1.0, 10.0);
}

int main() {

	int n;
	vector<double> x, f;
	n = 6;
	
	x.resize(n); f.resize(n);
	for(int i = 0; i < n; i++){
		x[i] = 0.99 + 0.004 * (double)(i);
		f[i] = poli10( x[i] );
	}
	
	formaInterpolante * fp = new formaInterpolante(x, f);
	cout << fp->evaluate(0.991) << endl;
	
	interpolacionLagrange * lp = new interpolacionLagrange(x, f);
	cout << lp->evaluate(0.991) << endl;
	
	double tam = 1000;
	double h = (1.01 - 0.99) / tam;
	double maxerr1 = 0, maxerr2 = 0;
	
	for(int i = 0; i <= tam; i++){
		double t = x[0] + h * (double)(i);
		cout << t << " ";
		double real = poli10(t);
		if(real != 0){
			//cout << t << " " << real << " " << fp->evaluate(t) << " " << lp->evaluate(t) << "\n";
			maxerr1 = max( maxerr1, abs ( ( real - fp->evaluate(t) )  ) );
			maxerr2 = max( maxerr2, abs ( ( real - lp->evaluate(t) )  ) );
		}
	}
	
	cout << maxerr1 << " " << maxerr2 << "\n";
	
	//cout << poli(1) << endl;
	return 0;
}
