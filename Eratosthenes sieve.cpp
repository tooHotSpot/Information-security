#include <iostream>
#include <iomanip>
#include <fstream>

using namespace std;

const int N = 1000000; // 10^6
const int SQRT = 1000; // 10^3
bool nprime[N + 5];

int main() {
	freopen("input.txt", "rt", stdin);
	freopen("output.txt", "wt", stdout);

	clock_t start = clock();
	double duration;

	nprime[0] = nprime[1] = 1;
	
  	for (int i = 2; i <= SQRT; i++) {
		if (nprime[i] == 0) {
			for (int j = i*i; j <= N; j += i) {
				nprime[j] = 1;
			}
		}
	}
	
  	duration = (clock() - start) / (double)CLOCKS_PER_SEC;
	cout << "All prime are counted, spent " << duration << " seconds\n";
	return 0;
}
