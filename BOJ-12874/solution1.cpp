#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

const int MOD = 1'000'000'007;
int cache[102][102];
string S;

int DP(int open, int close)
{
	int& ret = cache[open][close];
	if (ret > 0) return ret;

	for(int i=open+1;i<close;i++)
		

	return ret = (ret + 1) % MOD;
}

int main()
{
	cin >> S;
	S = '.' + S;
	cout << (DP(0, S.size()) + MOD -1) % MOD;
	return 0;
}