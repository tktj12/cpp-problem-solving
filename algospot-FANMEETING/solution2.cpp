#include <iostream>
#include <vector>
using namespace std;

typedef unsigned long long ULL;

void DataToBit(vector<ULL>&, string&);
bool BigAndOper(vector<ULL>&, vector<ULL>&);
void BigBitShift(vector<ULL>&);

int main()
{
	cin.tie(nullptr);
	cout.tie(nullptr);
	ios::sync_with_stdio(false);

	int tc;
	cin >> tc;
	while (tc--) {
		vector<ULL> member_bit, fan_bit;
		int member_sz, fan_sz;
		string str;
		cin >> str;
		member_sz = str.size();
		DataToBit(member_bit, str);
		
		cin >> str;
		fan_sz = str.size();
		DataToBit(fan_bit, str);

		int loop = fan_sz - member_sz + 1;
		int answer(0);
		for (int i = 0; i < loop; ++i) {
			answer += BigAndOper(member_bit, fan_bit);
			BigBitShift(fan_bit);
		}

		cout << answer << '\n';
	}
	return 0;
}

void DataToBit(vector<ULL>& bit, string& data)
{
	int vector_idx(-1), bit_offset(-1);
	for (int i = 0; i < data.size(); ++i) {
		if (bit_offset < 0) { 
			bit.push_back(0); 
			bit_offset = 63;
			++vector_idx;
		}
		if (data[i] == 'M')
			bit[vector_idx] |= (1ULL << bit_offset);
		--bit_offset;
	}
}

bool BigAndOper(vector<ULL>& a, vector<ULL>& b)
{
	for (int i = 0; i < a.size(); ++i) {
		if (a[i] & b[i]) return false;
	}
	return true;
}

void BigBitShift(vector<ULL>& bit)
{
	bit[0] <<= 1;
	for (int i = 1; i < bit.size(); ++i) {
		if (bit[i] & (1ULL << 63)) bit[i - 1] |= 1;
		bit[i] <<= 1;
	}
}