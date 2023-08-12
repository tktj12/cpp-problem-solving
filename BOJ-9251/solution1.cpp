#include <iostream>
#include <vector>
#include <map>
using namespace std;

inline int ToNum(char c) {
	return c - 'A';
}

map<int, int> end_idx;
void PutOrder(int order)
{
	auto iter = end_idx.lower_bound(order);
	if (iter == end_idx.end()) {
		end_idx[order] = end_idx.size();
	}
	else if (order < iter->first) {
		end_idx[order] = iter->second;
		end_idx.erase(iter);
	}
}

void CalcNewOrder(vector<int>& positions)
{
	if(positions.empty()) return;

	for (int i = positions.size() - 1; i >= 0; i--)
		PutOrder(positions[i]);
}

int main()
{
	cin.tie(nullptr);
	cout.tie(nullptr);
	ios::sync_with_stdio(false);

	string a, b;
	cin >> a >> b;

	vector<int> positions[26];
	for (int i = 0; i < a.size();i++) {
		char now = ToNum(a[i]);
		positions[now].push_back(i);
	}

	for (int i = 0; i < b.size(); i++)
		CalcNewOrder(positions[ToNum(b[i])]);

	cout << end_idx.size();

	return 0;
}