#include <iostream>
#include <fstream>
#include <ctime>
#include <vector>
#include <algorithm>
//#include <omp.h>

using namespace std;

//const long long N = 10000;     const int SQRT = 100; const int mSIZE = 315;
//const long long N = 1000000;   const int SQRT = 1000; const int mSIZE = 31255;
//const long long N = 100000000; const int SQRT = 10000; const int mSIZE = 3125005;
const long long N = 1000000000; const long long SQRT = 31625; const int mSIZE = 31250005;

unsigned int nprime[mSIZE];

//cout << PowMod(100, 9999999967, 9999999967) << endl; // 4355329650
unsigned long long PowMod(unsigned long long a,
	unsigned long  t, unsigned long long n) {

	//cout << "\t\tPowMod" << endl;
	unsigned long long d = 1;
	if (a == 1) {
		//cout << "a == 1" << endl;
		t = 1;
	}
	while (1) {
		//cout << "\t\t# " << d << " * " << a << " ^ " << t << " mod " << n;
		if (t == 1) {
			//cout << " = " << (d  * a) % n << " (end)\n";
			return (d  * a) % n;
		}
		if ((t & 1) == 1) {
			t--;
			d = ((d % n) * (a % n)) % n;
		}
		else {
			a = ((a % n) * (a % n)) % n;
			t >>= 1;
		}
		//cout << "\n";
	}
}

unsigned long long gcd(unsigned long long a, unsigned long long b) {
	if (b == 0) {
		return a;
	}
	return gcd(b, a % b);
}


int main()
{
	int console = 0;
	if (console != 1) {
		freopen("output.txt", "wt", stdout);
	}
	cout << "**********************************************\n";
	cout << "N = " << N << ", SQRT = " << SQRT << ", SIZE = " << mSIZE << ".\n";
	cout << "**********************************************\n";

	/*
	10^10 Bits
	10^10 / 8 = 125*10^7 Bytes
	(10^10 / 8) / 1024 = 1220703 KB
	(10^10 / 8) / 1024  / 1024 = 1192 MB = 1.3 GB
	*/
	clock_t start = clock();

#pragma region Finding all composite odd numbers
	for (int i = 3; i <= SQRT; i += 2) {
		/*
		i % 32 = i & 31
		i / 32 = i >> 5
		pow(2, j) = (1 << j);
		nprime[i / 32] &= pow(2, i % 32);
		nprime[j / 32] += pow(2, j % 32);
		*/
		long long r = nprime[i >> 5] & (1 << (i & 31));
		if (r == 0) {
			for (int j = i * i, t = 2 * i; j <= N; j += t) {
				nprime[j >> 5] |= (1 << (j & 31));
			}
		}
	}

	double duration = (clock() - start) / (double)CLOCKS_PER_SEC;
	cout << "Sieve ended in " << int(duration / 60) << " minutes " << int(duration) % 60 << " seconds.\n";
#pragma endregion

	int countNumbersProcessed = 0;
	int rk[10] = { 0 };

	for (long long n = 3; n <= N; n += 2) {
		long long r = nprime[n >> 5] & (1 << (n & 31));
		if (r != 0) {
			int q = sqrt(n);
			if (q * q == n) {
				continue;
			}
			//cout << "Counted " << countNumbersProcessed << "\n";
			//cout << "Counting for " << n << "\n";
			countNumbersProcessed++;
			
			long long n_minus_one = n - 1;
			int kBag = 0;
			int A[10] = { 15, 2, 94, 11, 31, 10, 29, 22, 28, 73 };
			for (int i = 0; i < 10; i++) {
				int a = A[i];
				if (a >= n) {
					break;
				}
				bool isWitness = 0;
				if (gcd(a, n) == 1) {
					unsigned long long s = 0, t = n_minus_one;
					while ((t & 1) == 0) {
						s++;
						t >>= 1;
					}
					unsigned long long b = PowMod(a, t, n);
					if (b == 1 || b == n_minus_one) {
						isWitness = 1;
					}
					else {
						for (int f = 1; f < s; f++) { //cout << "\t\t\t s = " << i << "\n";
							if (PowMod(b, (1 << f), n) == n_minus_one) {
								isWitness = 1;
								break;
							}
						}
					}
				}
				if (!isWitness) {
					break;
				}
				kBag++;
			}
			rk[kBag]++;
		}
	}

	cout << countNumbersProcessed << " checked for primality test in the range.\n\n";
	duration = (clock() - start) / (double)CLOCKS_PER_SEC;
	cout << "Main loop ended in " << int(duration / 60) << " minutes " << int(duration) % 60 << " seconds.\n";
	
	int A[10] = { 15, 2, 94, 11, 31, 10, 29, 22, 28, 73 };
	cout << "\nResult:\n";
	for (int i = 0; i < 10; i++) {
		cout << i + 1 << ": " << A[i] << " => " << rk[i] << "\n";
	}

	duration = (clock() - start) / (double)CLOCKS_PER_SEC;
	cout << "\nEnded in " << int(duration / 60) << " minutes " << int(duration) % 60 << " seconds.\n";

	if (console) {
		cout << "Enter 1 to end: ";
		cin >> countNumbersProcessed;
	}
	return 0;
}

