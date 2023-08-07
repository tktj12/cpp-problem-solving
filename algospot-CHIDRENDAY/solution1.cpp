#include <iostream>
#include <vector>
#include <cstring>
#include <queue>
using namespace std;

class Toy {
public:
	vector<int> nums;
	bool exceeded;
	int mod;
	int remainder;

	Toy(int mod) : mod(mod) {
		remainder = exceeded = 0;
	}

	void Insert(int n) {
		nums.push_back(n);
		int prev = remainder;
		remainder = (remainder * 10 + n);
		if (!exceeded && remainder >= mod)
			exceeded = true;
		remainder %= mod;
	}

	int Size() const {
		return nums.size();
	}

	bool operator<(const Toy& rhs) const
	{
		if (Size() != rhs.Size()) return Size() > rhs.Size();
		
		for (int i = 0; i < Size(); i++) {
			if (nums[i] != rhs.nums[i])
				return nums[i] > rhs.nums[i];
		}
		return false;
	}
};

vector<int> BFS(string available, int children, int greedy)
{
	int n = available.size();
	for (int i = 0; i < n; i++)
		available[i] -= '0';

	vector<bool> discovered(children, false);
	vector<bool> exceeded_discovered(children, false);
	priority_queue<Toy> pq;
	pq.push(Toy(children));
	while (!pq.empty()) {
		Toy now = pq.top(); pq.pop();

		for (char num : available) {
			Toy next = now;
			next.Insert(num);
			if (!next.exceeded) {
				if (discovered[next.remainder] == false) {
					discovered[next.remainder] = true;
					pq.push(next);
				}
			}
			else if (exceeded_discovered[next.remainder] == false) {
				if (next.remainder == greedy)
					return next.nums;
				pq.push(next);
				exceeded_discovered[next.remainder] = true;
			}
		}
	}

	return {};
}

int main()
{
	cin.tie(nullptr);
	cout.tie(nullptr);
	ios::sync_with_stdio(false);

	int tc;
	cin >> tc;
	while (tc--) {
		string available;
		int children, greedy;
		cin >> available >> children >> greedy;

		vector<int> ans = BFS(available, children, greedy);
		if (ans.size() == 0)
			cout << "IMPOSSIBLE";
		else
			for (int i = 0; i < ans.size(); i++)
				cout << ans[i];
		cout << '\n';
	}
	return 0;
}