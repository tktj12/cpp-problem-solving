#include <iostream>
#include <vector>
using namespace std;

typedef unsigned long long ULL;

void DataToBit(vector<ULL>&, string&);
bool BigAndOper(vector<ULL>&, vector<ULL>&, int, int);
void BigBitShift(vector<ULL>&);

int main()
{
	cin.tie(nullptr);
	cout.tie(nullptr);
	ios::sync_with_stdio(false);

	int tc;
	cin >> tc;
	while (tc--) {
		vector<ULL> member_bit[64], fan_bit(3126, 0);
		for (int i = 0; i < 64; ++i) member_bit[i] = vector<ULL>(3126, 0);

		int member_sz, fan_sz;
		string str;
		cin >> str;
		member_sz = str.size();
		for (int i = 0; i < member_sz; ++i)
			if (str[i] == 'M')
				for (int shift = 0; shift < 64; ++shift)
					member_bit[shift][(i + shift) / 64] |= 1ULL << ((i + shift) & 63);
		int member_bit_sz = (member_sz + 62) / 64 + 1;

		cin >> str;
		fan_sz = str.size();
		for (int i = 0; i < fan_sz; ++i)
			if (str[i] == 'M')
				fan_bit[i / 64] |= 1ULL << (i & 63);

		int hugs(0);
		int loop = fan_sz - member_sz + 1;
		for (int i = 0; i < loop; ++i)
			hugs += BigAndOper(member_bit[i & 63], fan_bit, member_bit_sz, i / 64);

		cout << hugs << '\n';
	}
	return 0;
}

bool BigAndOper(vector<ULL>& a, vector<ULL>& b, int a_sz, int b_off)
{
	for (int i = 0; i < a_sz; ++i) {
		if (a[i] & b[i + b_off]) return false;
	}
	return true;
}