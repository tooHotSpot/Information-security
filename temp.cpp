// Security.cpp: определяет точку входа для консольного приложения.
//

#include <iostream>
#include <bitset>
#include <fstream>
#include <string>
#include <ctime>

using namespace std;

const int N = 10005;
const int SQRT = 100;
unsigned int nprime[N];

int main()
{
	freopen("input.txt", "rt", stdin);
	freopen("output.txt", "wt", stdout);

	// 10^10 bits
	// 10^10 / 8 = 125*10^7 bytes
	// (10^10 / 8) / 1024 = 1220703 KB
	// (10^10 / 8) / 1024  / 1024 = 1192 MB = 1.3 GB

	clock_t start = clock();
	double duration;


	long long t = 0, count = 0;
	nprime[0] += 3;	// nprime[0] = 0.....011 -> 0 and 1 are not prime now
	for (long long i = 2; i <= 5; i++) {
		// i % 32 = i & 31
		// i / 32 = i >> 5
		// pow(2, j) = (1 << j);
		t = (i & 31); // t = 2 ** (i % 32); 
		cout << bitset<32>(t) << " = " << t << " is compared to \n";
		
		
		if ((~nprime[i >> 5]) &  t == 0) {
			cout << bitset<32>(~nprime[i >> 5]) << " which is inversion of " << bitset<32>(nprime[i >> 5]);
			cout << "\n" << i << " is simple then\n";
			// i is simple then
			for (long long j = i * i; j <= 25; j += i) {
				cout << j << " ";
				// nprime[j / 32] += pow(2, j % 32);
				nprime[j >> 5] += (1 << (j & 31));
			}
			bitset<32>f(nprime[i >> 5]);
			cout << "\n" << f << endl;
		}
		
	}
	duration = (clock() - start) / (double)CLOCKS_PER_SEC;
	cout << "Time spent: "  << duration << '\n';



	return 0;
}

