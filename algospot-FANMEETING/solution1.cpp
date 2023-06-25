#include <iostream>
#include <vector>
using namespace std;

vector<int> Karatsuba(vector<int>&, vector<int>&, int, int);
vector<int> BigMultiply(vector<int>&, vector<int>&, int, int);
void BigAddTo(vector<int>&, vector<int>&, int);
void BigSubFrom(vector<int>&, vector<int>&);

vector<int> member(200001, 0), fan(200001,0);
int main()
{
	cin.tie(nullptr);
	cout.tie(nullptr);
	ios::sync_with_stdio(false);

	int tc;
	cin >> tc;
	while (tc--) {
		string str;
		cin >> str;
		int member_sz = str.size()-1;
		for (int i = 0; i <= member_sz; ++i) 
			member[i] = (str[member_sz-i] == 'M');
		++member_sz;

		cin >> str;
		int fan_sz = str.size();
		for (int i = 0; i < fan_sz; ++i) 
			fan[i] = (str[i] == 'M');

		vector<int> multiply_res = Karatsuba(fan,member, fan_sz, member_sz);
		int answer(0);
		for (int i = member_sz-1; i < fan_sz; ++i)
			answer += (multiply_res[i] == 0);
		cout << answer << '\n';
	}
	return 0;
}

vector<int> Karatsuba(vector<int>& a, vector<int>& b, int a_sz, int b_sz)
{
	if (a_sz <= 0 || b_sz <= 0) return vector<int>();
	if (a_sz < b_sz) return Karatsuba(b, a, b_sz, a_sz);
	if (a_sz <= 100) return BigMultiply(a, b, a_sz, b_sz);

	int half = a_sz>>1;
	vector<int> a0(a.begin(), a.begin() + half);
	vector<int> a1(a.begin()+half, a.begin()+a_sz);
	vector<int> b0(b.begin(), b.begin() + min(half, b_sz));
	vector<int> b1(b.begin() + min(half,b_sz), b.begin()+b_sz);

	vector<int> z0 = Karatsuba(a0, b0, a0.size(), b0.size());
	vector<int> z2 = Karatsuba(a1, b1, a1.size(), b1.size());
	BigAddTo(a0, a1, 0);
	BigAddTo(b0, b1, 0);

	vector<int> z1 = Karatsuba(a0, b0, a0.size(), b0.size());
	BigSubFrom(z1, z0);
	BigSubFrom(z1, z2);

	vector<int> ret = z0;
	BigAddTo(ret, z1, half);
	BigAddTo(ret, z2, half << 1);
	return ret;
}

vector<int> BigMultiply(vector<int>& a, vector<int>& b, int a_sz, int b_sz)
{
	vector<int> ret(a_sz + b_sz - 1, 0);
	for(int i=0;i<a_sz;++i)
		for (int j = 0; j < b_sz; ++j)
			ret[i + j] += (a[i] * b[j]);

	return ret;
}

void BigAddTo(vector<int>& a, vector<int>& b, int k)
{
	a.resize(max(a.size(), b.size()+k));
	for (int i = 0; i < b.size(); ++i)
		a[i+k] += b[i];
}

void BigSubFrom(vector<int>& a, vector<int>& b)
{
	for (int i = 0; i < b.size(); ++i)
		a[i] -= b[i];
}