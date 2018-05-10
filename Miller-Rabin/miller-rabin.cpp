/*
Este programa implementa el algoritmo de Miller-Rabin para probar la primalidad de un número

Para compilar el programa desde la terminal se debe usar el comando: g++ -std=c++11 miller-rabin.cpp

El código principal está dividida en distintas secciones, cada una de las
cuales realiza distintas pruebas sobre el algoritmo. Las pruebas que se realizaron fueron:

	* Primera Prueba: Se corrió el algoritmo con una lista de primos,
	para verificar que respondiera correctamente en TODOS ellos.
	
	* Segunda Prueba: Se corrió el algoritmo con una lista de números
	compuestos aleatorios, para medir el porcentaje de aciertos.
	
	* Tercera Prueba: Se comparó el tiempo de ejecución de Miller-Rabin con
	el de el test de primalidad determinista.
	
	* Cuarta Prueba: Se corrió el algortimo con una lista de números de Carmichael
	
Para correr una prueba se debe descomentar la sección del código adecuada.
*/

#include <iostream>
#include <algorithm>
#include <random>
#include <ctime>
#include <cstdio>
#define ull unsigned long long int
using namespace std;

default_random_engine generator (time(NULL));

//genera un arreglo de n números aleatorios entre l y h y lo guarda en un arreglo A
void rand_arr( ull A[], int n, ull l, ull h ){
	uniform_int_distribution<ull> distribution(l, h);
	for(int i = 0; i < n; i++)
		A[i] = distribution(generator);	
}	

//exponenciacion binaria
//devuelve el resultado de elevar n a la potencia pow en modulo m
ull exp(ull n, ull pow, ull m){
	if(pow == 0)
		return 1;
	
	if(pow % 2)
		return (n * exp(n, pow - 1, m)) % m;
	ull ret = exp(n, pow / 2, m);
	return (ret * ret) % m;
}

//computa a^(n-1) e intenta encontrar
//raices no triviales para la ecuación x^2 = 1 (mod n) 
//si encuentra alguna raiz cuadrada no trivial de 1 modulo n 
//o si a^(n-1) es diferente de 1 devuelve verdadero (el número definitivamente no es primo)
//en caso contrario devuelve falso (el número puede no ser primo).
bool witness(ull a, ull n){
	//primero encontramos t y u, t >= 1, u impar tales que:
	//n - 1 = 2^t * u
	ull t = 0, u = n - 1;
	while(u % 2 == 0){
		t++;
		u /= 2;
	}
	
	vector<ull> x(t + 1);
	x[0] = exp(a, u, n); // x[0] = a^u;
	//si x[i] = x[i - 1]^2, x[t] tendrá el valor de a^(n-1)
	for(int i = 1; i <= t; i++){
		x[i] = (x[i - 1] * x[i - 1]) % n;
		if( x[i] == 1 && x[i - 1] != 1 and x[i - 1] != n - 1 ) //encontramos una solucion no trivial de x^2 = 1 mod n
			return true;
	}
	
	if( x[t] != 1 )
		return true;

	return false;
}

//Test de primalidad con el algoritmo de Miller-Rabin
//Corre la función witness con s números aleatorios
//Devuelve true si n pasa el test de primalidad
//Devuelve false en caso contrario
bool MillerRabin(ull n, int s){
	ull * A = new ull [s];
	rand_arr(A, s, 1, n - 1); //guarda s números aleatorios entre 1 y n-1
	
	//corremos la función witness con los s números aleatorios
	for(int i = 0; i < s; i++)
		if( witness( A[i], n ) )
			return false; //n no es primo
		
	return true; //muy problemente n es primo
}

//Test de primalidad determinista
//busca divisores de n uno por uno hasta llegar a la raiz cuadrada de n-1
//Si no encuentra divisores el número es primo y la función regresa true;
//en caso contrario la función devuelve false.
bool isPrime(ull n){
	ull lim = sqrt(n);
	for(ull i = 2; i <= lim; i++)
		if(n % i == 0)
			return false;
	return true;
}

int main(){
	
	/*----- Primer test -----
	//corre el algoritmo con una lista de 10^6 primos y cuenta la cantidad de errores
	//dado que Miller-Rabin no se equivoca con números primos, la cantidad de errores debería ser igual a 0
	
	//freopen("primes.txt", "r", stdin);
	
	ull p;
	vector<ull> primes;
	while(cin >> p)
		primes.push_back(p);
	
	int cont = 0;
	for(int i = 0; i < primes.size(); i++)
		if( !MillerRabin( primes[i], 1 ) )
			cont++;
	
	cout << "----- PRIMER TEST -----\n"; 
	cout << "Se probo Miller-Rabin con " << 
	     primes.size() << " primos y hubo " << cont << " errores\n";
	*/
	
	/*-----Segundo Test-----
	//Se corre el algorithmo con una lista de 100,000 números compuestos
	//y se mide el porcentaje de efectividad para distintos valores de s.
	
	freopen("composites.txt", "r", stdin);
	int n;
	cin >> n;
	vector<ull> composites(n);
	for(int i = 0; i < n; i++)
		cin >> composites[i];
	
	cout << n << "\n";
	cout << "----- SEGUNDO TEST -----\n";
	for(int s = 1; s <= 5; s++){
		
		int corrects = 0;
		for(int i = 0; i < n; i++)
			if( !MillerRabin( composites[i], s ) )
				corrects++;
			
		cout << "Para s = " << s << " se tuvo un porcentaje de aciertos de "
		<< (double)( double(corrects) / (double)(n) ) * (double)(100) << "\n";
		
	}*/
	
	/*-----Tercer Test-----
    //Se corre Miller-Rabin con una lista de números y se calcula el tiempo de ejecucion promedio
	//Comparamos este tiempo con el tiempo de ejecución del algoritmo determinista
	
	freopen("nums.txt", "r", stdin);
	vector<ull> nums;
	ull number;
	
	while(cin >> number)
		nums.push_back(number);
	
	int ntests = nums.size();
	double timeMiller = 0.0;
	double timeDet = 0.0;
	
	for(int i = 0; i < ntests; i++){
		
		clock_t begin = clock();
		MillerRabin( nums[i], 5 );
		clock_t end = clock();
		double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
		timeMiller += elapsed_secs;
		
		begin = clock();
		isPrime( nums[i] );
		end = clock();
		elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
		timeDet += elapsed_secs;
	
	}
	
	timeMiller /= double(ntests);
	timeDet /= double(ntests);
	
	cout << "----- TERCER TEST -----\n";
	cout << "El tiempo promedio de ejecucion de Miller-Rabin fue de " 
	<< timeMiller << " segs\n";
	cout << "El tiempo promedio de ejecucion del algoritmo determinista fue de " 
	<< timeDet << " segs\n";
	
	*/
	
	//-----Cuarto Test-----
	//Corre Miller-Rabin para numeros de carmichael
	
	freopen("carmichael-nums.txt", "r", stdin);
	int n;
	cin >> n;
	vector<ull> carm(n);
	for(int i = 0; i < n; i++)
		cin >> carm[i];
	
	cout << n << "\n";
	cout << "----- CUARTO TEST -----\n";
	for(int s = 1; s <= 5; s++){
		
		int corrects = 0;
		for(int i = 0; i < n; i++)
			if( !MillerRabin( carm[i], s ) )
				corrects++;
			
		cout << "Para s = " << s << " se tuvo un porcentaje de aciertos de "
		<< (double)( double(corrects) / (double)(n) ) * (double)(100) << "\n";
	}
	
	cout << MillerRabin(60977817398996785, 1);
	
	return 0;
}