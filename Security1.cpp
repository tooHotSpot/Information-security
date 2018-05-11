// Security.cpp: определяет точку входа консольного приложения.
//

#include <iostream>
#include <bitset>
#include <fstream>
#include <algorithm>
#include <typeinfo>
#include <string>
#include <ctime>
#include <vector>
#include <Windows.h>
#include <Psapi.h>
#include <omp.h>

using namespace std;

const long long N = 100; // 10^10 31250001
const int SQRT = 10; // 100000
//const int mSIZE = 312500005;
unsigned int nprime[N]; // n/32
vector<unsigned long long> bases(105);


unsigned long long gcd(unsigned long long a, unsigned long long b) {
	if (b == 0) {
		return a;
	}
	return gcd(b, a%b);
}

unsigned long long PowMod(unsigned long long a,
	unsigned long  b, unsigned long long n) {
	
	//cout << "PowMod" << endl;
	unsigned long long d = 1;
	while (1) {
		//cout << d << " " << a << " " << b << " " << n << endl;
		if (b == 1) {
			return (d  * a) % n;
		}
		if ((b & 1) == 1) {
			b--;
			d = ((d % n) * (a % n)) % n;
		}
		else {
			a = ((a % n) * (a % n)) % n;
			b >>= 1;
		}
	}
}


int checkIfWitness(unsigned long long a, unsigned long long n) {
	if (gcd(a, n) == 1) {
		int s = 0, t = a - 1;
		while ((t & 1) == 0) {
			s++;
			t >>= 1;
		}
		unsigned long long n_minus_one = n - 1;
		unsigned long long b = PowMod(a, t, n);
		if (b == 1 || b == n_minus_one)
			return 1;
		else 
			for (int i = 1; i < s; i++) 
				if (PowMod(b, (1 >> i), n) == n_minus_one) 
					return 1;
	}
	return 0;
}

int main()
{
	freopen("input.txt", "rt", stdin);
	freopen("output.txt", "wt", stdout);

	long long s = 0;
	int t = 1025;
	//cout << PowMod(100, 9999999967, 9999999967) << endl; // 4355329650

	clock_t start = clock();
	double duration;
	int a[105] = { 0 };
	unsigned long long kSPP[10] = { 0 };
	int kNUMS[5] = { 2, 3, 5, 7, 11 };

	nprime[0] = nprime[1] = 1;
	for (int i = 2; i <= SQRT; i++) {
		if (nprime[i] == 0) {
			for (int j = i*i; j <= N; j += i) {
				nprime[i] = 1;
			}
		}
	}
	duration = (clock() - start) / (double)CLOCKS_PER_SEC / 60;
	cout << "All prime are counted, spent " << int(duration) << " minutes\n";
	start = clock();

#pragma omp parallel for reduction(+:bases)
	for (int n = 0; n <= N; n++) {
		if (nprime[n] == 0) {
			// n is prime
			
			for (int f = 0; f < 5; f++) {
				if (checkIfWitness(kNUMS[f], n) == 0) {
					if (f > 0)
						kSPP[f] += 1;
					break;
				}
			}
			for (int a = 2; a <= 100; a++) {
				bases[a] += checkIfWitness(a, n);
			}
		}
	}
	duration = (clock() - start) / (double)CLOCKS_PER_SEC / 60;
	cout << "Main loop ended\n" << int(duration) << " minutes\n";
	start = clock();

	/*vector<pair<int, int>> results;
	for (int i = 2; i <= 100; i++) {
		results.push_back(make_pair(bases[i].size(), i));
	}*/

	sort(results.begin(), results.end());
	cout << "BEST" << endl;
	cout << results[0].second << " " << results[1].second << " " << results[2].second;
	cout << "WORST" << endl;
	cout << results[99].second << " " << results[98].second << " " << results[97].second;
	
	int wait;
	cin >> wait;
	return 0;
}
/*
312 500 000 * 4 байта = 1250 десятичных мегабайт
312 500 000 * 4 байта = 1.25 десятичных гигабайта
*/

