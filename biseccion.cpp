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