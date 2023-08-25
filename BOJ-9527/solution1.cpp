#include <iostream>
#include <vector>
#include <cstring>
using namespace std;
using ull = unsigned long long;

// cache[i] : i+1��° �ڸ����� ������ ��� �������� 1�� ����
ull cache[54] = { 1 };

// num���� ���� ��� 1�� ���� ����
// num�� ������ 54�ڸ����� ����
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