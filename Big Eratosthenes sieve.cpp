#include <iostream>
#include <fstream>
#include <ctime>

using namespace std;

const long long N = 10000000005; // 10^10
const long long SQRT = 100000; // 10^5
const int mSIZE = 312500005;
unsigned int nprime[mSIZE]; // n/32

int main()
{
	
	freopen("output.txt", "wt", stdout);

	/* 
	10^10 Bits
	10^10 / 8 = 125*10^7 Bytes
	(10^10 / 8) / 1024 = 1220703 KB
	(10^10 / 8) / 1024  / 1024 = 1192 MB = 1.3 GB
	*/
	
	clock_t start = clock();
	
	nprime[0] += 3;	
	// nprime[0] = 0.....011 -> 0 and 1 are not prime now
	for (long long i = 2; i <= SQRT; i++) {
		/*
		cout << "\nNumber: " << i << "\n";
		i % 32 = i & 31
		i / 32 = i >> 5
		pow(2, j) = (1 << j);
		nprime[i / 32] &= pow(2, i % 32);
		nprime[j / 32] += pow(2, j % 32);
		*/
		long long r = nprime[i >> 5] & (1 << (i & 31));
		if (r == 0) {
			for (long long j = i * i; j <= N; j += i) {
				nprime[j >> 5] |= (1 << (j & 31));
			}
		}
	}

	clock_t process = clock();
	
	clock_t writer = clock();
	double duration = (process - start) / (double)CLOCKS_PER_SEC;
	cout << "Time spent to count = : " << duration << '\n';

	return 0;
}

