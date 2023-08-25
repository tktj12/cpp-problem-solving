#include <iostream>
#include <vector>
#include <cstring>
using namespace std;
using ull = unsigned long long;

// cache[i] : i+1번째 자리까지 가능한 모든 이진수의 1의 개수
ull cache[54] = { 1 };

// num까지 나온 모든 1의 개수 리턴
// num은 이진수 54자리까지 가능
ull CntTotalOnes(ull num)
{
	ull ret = num & 1ull;
	ull bit = 2ull;
	for (int i = 0; i < 53; i++) {
		if (num & bit) ret += cache[i] + (num & (bit-1)) + 1;
		bit <<= 1;
	}

	return ret;
}

int main()
{
	cin.tie(nullptr);
	cout.tie(nullptr);
	ios::sync_with_stdio(false);
	
	ull bit = 2;
	for (int i = 1; i < 54;i++) {
		cache[i] = 2 * cache[i - 1] + bit;
		bit <<= 1;
	}

	ull a, b, ans;
	cin >> a >> b;
	ans =  CntTotalOnes(b) - CntTotalOnes(a);
	for (int i = 0; i < 64; i++) {
		ans += a & 1ull;
		a >>= 1;
	}

	cout << ans;

	return 0;
}