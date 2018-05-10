/*
Con este programa generamos listas de números compuestos aleatorios para
probar la efectividad de miller-rabin
*/
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cmath>
#include <random>
#include <ctime>
using namespace std;

default_random_engine generator (time(NULL));

//implementa una criba de Eratóstenes para obtener los primeros menores
//o iguales a n.
void primeList(int n, vector<int> & primes){ 
	bool * c = new bool[n + 1]; 
	fill( c, c + n + 1, false );
	int lim = sqrt(n);
	
	for(int i = 2; i <= lim; i++)
		if( !c[i] ){ //el número es primo
			primes.push_back( i ); //agrega i a la lista de primos
			for(int j = i * i; j <= n; j += i)
				c[j] = true; //descartamos los múltiplos de i
		}
		
	for(int i = lim + 1; i <= n; i++)
		if( !c[i] )
			primes.push_back(i);
}

//verifica si un número es compuesto. Para ello intenta buscar divisores
//del número hasta su raíz cuadrada, aprovechando una lista de primos
//previamente calculada.
bool isComposite(long long int n, vector<int> &primes){
	
	int lim = sqrt(n);
	int tam = primes.size();
	
	for(int i = 0; i < tam && primes[i] <= lim; i++)
		if( n % primes[i] == 0 ) //encontramos un divisor de n
			return true;
			
	if( primes[tam - 1] < lim )
	for(int i = primes[tam - 1] + 1; i <= lim; i++)
		if( n % i == 0 ) //encontramos un divisor de n
			return true;
			
	return false; //n es primo	
}

//genera un arreglo de n números compuestos aleatorios entre l y h y lo guarda en un arreglo A
void rand_arr( long long A[], int n, long long l, long long h, vector<int> &primes ){
	uniform_int_distribution<long long> distribution(l, h);
	for(int i = 0; i < n; i++){
		A[i] = distribution(generator);	
		while( !isComposite( A[i], primes ) )
			A[i] = distribution(generator);
	}
}

void rand_arr( long long A[], int n, long long l, long long h ){
	uniform_int_distribution<long long> distribution(l, h);
	for(int i = 0; i < n; i++){
		A[i] = distribution(generator);
	}
}

int main() {
	
	vector<int> primes;
	primeList(1000000, primes);
	//generamos un arreglo de 100000 numeros compuestos hasta 10^12

	long long * A = new long long [100000];
	
	freopen("composites.txt", "w", stdout);
	//for(int i = 0; i < 1000; i++) cout << primes[i] << " ";
	int n = 100000;
	rand_arr(A, n, 2, 1000000000000, primes);
	
	cout << n << "\n";
	for(int i = 0; i < n; i++)
		cout << A[i] << "\n";
	
	fclose(stdout);
	freopen("nums.txt", "w", stdout);
	n = 100;
	rand_arr(A, n, 2, 10000000000000000);
	for(int i = 0; i < n; i++)
		cout << A[i] << "\n";
	
	return 0;
}