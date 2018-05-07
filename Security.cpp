// Security.cpp: определяет точку входа консольного приложения.
//

#include <iostream>
#include <bitset>
#include <fstream>
#include <typeinfo>
#include <string>
#include <ctime>
#include <Windows.h>
#include <Psapi.h>

using namespace std;

const long long N = 10000000005; // 10^10 31250001
const int SQRT = 100000; // 100000
const int mSIZE = 312500005;
unsigned int nprime[mSIZE]; // n/32

int main()
{
	//freopen("input.txt", "rt", stdin);
	//freopen("output.txt", "wt", stdout);

	//$long long tenten = (long long)pow(10, 10);
	//int erp = 1 << 31;
	//int erpInt = tenten >> 5;
	//$long long erpLL = tenten >> 5;
	//int g = (31 & 31);
	//cout << g << endl;
	//cout << erp << " " << typeid(erp).name() << "\n" << bitset<32>(erp) << "\n" << ULONG_MAX << " " << typeid(ULONG_MAX).name() << "\n";
	/* Last checkings
	cout << typeid(pow(10, 10)).name() << ": " << pow(10, 10) << " /32 = " << pow(10, 10) / 32 << "\n";
	cout << "Natively: " << typeid(tenten >> 5).name() << " = " << (tenten >> 5) << endl;
	cout << "erpInt: " << typeid(erpInt).name() << " = " << erpInt << endl;
	cout << "erpLL: " << typeid(erpLL).name() << " = " << erpLL << endl;
	*/
	//cout << (1 << (31 && 31)) << " " << typeid(1 << (31 && 31)).name() << endl;
	//return 0;

	// 10^10 bits
	// 10^10 / 8 = 125*10^7 bytes
	// (10^10 / 8) / 1024 = 1220703 KB
	// (10^10 / 8) / 1024  / 1024 = 1192 MB = 1.3 GB

	clock_t start = clock();
	double duration;

	//string s1 = "-", s2 = "-", s3 = "-", s4 = "-", s5 = "-";
	nprime[0] += 3;	// nprime[0] = 0.....011 -> 0 and 1 are not prime now
	for (long long i = 2; i <= SQRT; i++) {
		//cout << "\nNumber: " << i << "\n";
		// i % 32 = i & 31
		// i / 32 = i >> 5
		// pow(2, j) = (1 << j);
		long long t = (1 << (i & 31)); // t = 2 ** (i % 32); // what is (i & 31) ? // check 31-32, 10^10-(10^10-1) 
		//bitset<32>f1(t);
		//s1 = f1.to_string('*');
		long long jot = i >> 5; //int jot = i >> 5; // here needed  ull maybe
		//bitset<32>f2(nprime[i/32]);
		//s2 = f2.to_string('*');
		// cout << bitset<32>(t) << " & \n";
		// cout << bitset<32>(nprime[i >> 5]) << "\n";
		long long r = nprime[jot] & (unsigned int)t; // TODO: try t as unsigned int variable initally
		// cout << bitset<32>(r) << ", result: ";
		if (r == 0) {
			//cout << i << "\n";
			for (long long j = i * i; j <= N; j += i) {
				//cout << j << " ";
				// nprime[j / 32] += pow(2, j % 32);
				long long jot2 = j >> 5; //int jot2 = j >> 5; // here needed ull
				unsigned int ttt = 1 << (j & 31);
				//bitset<32>f3(ttt);				
				//s3 = f3.to_string();
				//bitset<32>f4(nprime[j >> 5]);	
				//s4 = f4.to_string();
				nprime[jot2] |= ttt;
				/*r = nprime[i >> 5] & (unsigned int)t;
				if (r == 0) {
					nprime[j >> 5] += ttt;
				}*/
				//bitset<32>f5(nprime[j >> 5]);	s5 = f5.to_string();
			}
			//bitset<32>f(nprime[i >> 5]);
			//cout << "\n" << f << endl;
			//cout << "\n";
		}
		//cout << bitset<32>(nprime[0]) << "\n" << bitset<32>(nprime[1]) << "\n";
		//break;
	}

	clock_t process = clock();
	// Attention: Numbers folder must be empty
	string result = "Numbers\\1.txt";
	freopen(result.c_str(), "wt", stdout);
	
	long long totally = 0, countNumbersAmount = 0, countFilesAmount = 1;
	for (long long i = 2; i <= N; i++) {
		long long t = (1 << (i & 31));
		long long jot = i >> 5; 
		long long r = nprime[jot] & (unsigned int)t;
		if (r == 0) {
			cout << i << "\n";
			totally++;
			countNumbersAmount++;
			if (countNumbersAmount == 1000000) {
				cout << "\nWritten " << countNumbersAmount << " numbers to file #" << countFilesAmount;
				cout << "\nTotally " << totally << " numbers\n";
				result = "Numbers\\" + to_string(++countFilesAmount) + ".txt";
				freopen(result.c_str(), "wt", stdout);
				countNumbersAmount = 0;
			}
		}
	}
	if (countNumbersAmount != 0) {
		cout << "\nWritten " << countNumbersAmount << " numbers to file #" << countFilesAmount;
		cout << "\nLast file.";
		cout << "\nTotally " << totally << " numbers\n";
	}

	clock_t writer = clock();
	freopen("myStatistics.txt", "wt", stdout);
	cout << "Totally " << totally << " numbers\n";
	cout << "Created " << countFilesAmount << " files\n";
	duration = (process - start) / (double)CLOCKS_PER_SEC;
	cout << "Time spent to count = : " << duration << '\n';
	duration = (writer - process) / (double)CLOCKS_PER_SEC;
	cout << "Time spent to write file = : " << duration << '\n';
	duration = (writer - start) / (double)CLOCKS_PER_SEC;
	cout << "Time spent totally = : " << duration << '\n';
	
#pragma region MyRegion
	MEMORYSTATUSEX memInfo;
	memInfo.dwLength = sizeof(MEMORYSTATUSEX);
	GlobalMemoryStatusEx(&memInfo);
	DWORDLONG totalVirtualMem = memInfo.ullTotalPageFile;
	
	DWORDLONG physMemUsed = memInfo.ullTotalPhys - memInfo.ullAvailPhys;
	cout << "Physical Memory currently used: " << physMemUsed / 1073741824 << " MB\n";

	PROCESS_MEMORY_COUNTERS pmc;
	GetProcessMemoryInfo(GetCurrentProcess(), &pmc, sizeof(pmc));
	SIZE_T physMemUsedByMe = pmc.WorkingSetSize;
	cout << "Physical Memory currently used by current process: ";
	cout << physMemUsedByMe / 1073741824 << " MB";
#pragma endregion
	return 0;
}
/*
312 500 000 * 4 байта = 1250 десятичных мегабайт
312 500 000 * 4 байта = 1.25 десятичных гигабайта
*/

