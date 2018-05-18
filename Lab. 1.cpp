#include <iostream>
#include <fstream>
#include <ctime>
#include <vector>
#include <algorithm>
#include <omp.h>

using namespace std;

//const long long N = 10000;     const int SQRT = 100; const int mSIZE = 315;
const long long N = 1000000;   const int SQRT = 1000; const int mSIZE = 31255;
//const long long N = 100000000; const int SQRT = 10000; const int mSIZE = 3125005;
//const long long N = 1000000000; const long long SQRT = 31625; const int mSIZE = 31250005;
//const long long N = 10000000000; const long long SQRT = 100000; const int mSIZE = 312500005;

unsigned int nprime[mSIZE];

//cout << PowMod(100, 9999999967, 9999999967) << endl; // 4355329650
unsigned long long PowMod(unsigned long long a,
	unsigned long  t, unsigned long long n) {

	//cout << "\t\tPowMod" << endl;
	unsigned long long d = 1;
	/*
	if (a == 1) {
		cout << "a == 1" << endl;
		t = 1;
	}
	*/
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
	}
}

unsigned long long gcd(unsigned long long a, unsigned long long b) {
	if (b == 0) {
		return a;
	}
	return gcd(b, a % b);
}

unsigned long long myBases[105] = {};

int main()
{
	freopen("output.txt", "wt", stdout);

	/*
	10^10 Bits
	10^10 / 8 = 125*10^7 Bytes
	(10^10 / 8) / 1024 = 1220703 KB
	(10^10 / 8) / 1024  / 1024 = 1192 MB = 1.3 GB
	*/
	unsigned long long t, q, i, j, r, last = 0,
		countNumbersAmount = 0, countNumbersProcessed = 0;
	long long l = 0, a, n, n_minus_one;
	clock_t start = clock();
	double duration;

	for (i = 3; i <= SQRT; i += 2) {
		/*
		i % 32 = i & 31
		i / 32 = i >> 5
		pow(2, j) = (1 << j);
		nprime[i / 32] &= pow(2, i % 32);
		nprime[j / 32] += pow(2, j % 32);
		*/
		r = nprime[i >> 5] & (1 << (i & 31));
		if (r == 0) {
			for (j = i * i, t = 2 * i; j <= N; j += t) {
				nprime[j >> 5] |= (1 << (j & 31));
			}
		}
	}

	duration = (clock() - start) / (double)CLOCKS_PER_SEC;
	cout << "Sieve ended in " << int(duration / 60) << " minutes ";
	printf("%.2f seconds.\n\n", duration);
	unsigned long long countSquares = 0;
	for (n = 3; n <= 1000000; n += 2) {
		r = nprime[n >> 5] & (1 << (n & 31));
		if (r != 0) {
			q = sqrt(n);
			if (q * q == n) {
				countSquares++; // Miller-Rabin test is not dedicated for squares
				continue;
			}
			//cout << "Counted " << countNumbersProcessed << "\n";
			//cout << "Counting for " << n << "\n";
			countNumbersProcessed++;
			last = n;
			n_minus_one = n - 1;
			l = min(100ll, n_minus_one);
#pragma omp parallel for shared(l, n, n_minus_one, myBases)
			for (a = 2; a <= l; a++) {
				if (gcd(a, n) == 1) {
					int s = 0;
					unsigned long long t = n_minus_one;
					while ((t & 1) == 0) {
						s++;
						t >>= 1;
					}
					unsigned long long b = PowMod(a, t, n);
					if (b == 1ull || b == n_minus_one) {
						myBases[a] += 1; //cout << "\tInstantly: b = " << b << "\n";
					}
					else { //cout << "\t\tTrying 2 case" << endl;
						for (int f = 1; f < s; f++) { //cout << "\t\t\t s = " << i << "\n";
							if (PowMod(b, (1ull << f), n) == n_minus_one) {
								myBases[a] += 1; //printf("\t\tOK: b=%lld ^(2 ^ i=%lld) mod n=%lld", b, i, n);
								break;
							}
						}
					}
				}
			}
		}
	}

	countNumbersAmount = countSquares + countNumbersProcessed;
	cout << countNumbersAmount << " composite odd in the range.\n";
	cout << countSquares << " composite odd squares in the range. Minusing them.\n";
	cout << countNumbersProcessed << " checked for primality test in the range. Those are all we need.\n";
	cout << last << " is last composite odd.\n";
	duration = (clock() - start) / (double)CLOCKS_PER_SEC;
	cout << "Main loop ended in " << int(duration / 60) << " minutes ";
	printf("%.2f seconds.\n\n", duration);


	cout << "Unsorted bases with values:\n";
	for (a = 2; a <= 100; a++) {
		cout << a << ": " << myBases[a] << "\n";
	}

	vector<pair<unsigned long long, int>> h;
	for (int a = 2; a <= 100; a++) {
		//cout << "BASE [" << a << "]: " << bases[a] << "\n";
		h.push_back(make_pair(myBases[a], a));
	}
	sort(h.begin(), h.end());
	cout << "Sorted bases with values:\n";
	for (int i = 0; i < 98; i++) {
		cout << h[i].second << ": " << h[i].first << "\n";
	}
	cout << "\nBest bases:\n";
	for (int i = 0; i < 3; i++) {
		cout << h[i].second << ": " << h[i].first << " numbers.\n";
	}
	cout << "\nWorst bases:\n";
	for (int i = 97; i >= 95; i--) {
		cout << h[i].second << ": " << h[i].first << " numbers.\n";
	}

	duration = (clock() - start) / (double)CLOCKS_PER_SEC;
	cout << "Ended in " << int(duration / 60) << " minutes " << int(duration) % 60 << " seconds.\n";

	cout << "\n10 best bases for the second part:\n";
	for (int i = 0; i < 10; i++) {
		cout << h[i].second << " ";
	}

	return 0;
}

