#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

class UnionFind {
public:
	int parent[100010];
	UnionFind() {}
	void Init(int n) {
		for (int i = 0; i < n; i++)
			parent[i] = i;
	}

	int Find(int u) {
		if (u == parent[u])
			return u;
		else
			return parent[u] = Find(parent[u]);
	}

	// v의 집합이 u의 집합 아래로 들어감
	void Merge(int u,int v) {
		parent[Find(v)] = Find(u);
	}
}dset;

struct Node {
	int relative_weight=0;
	vector<int> chileren;
	int size = 1;
};

int n_sample, n_exp;
vector<Node> samples;

// node를 루트로 하는 서브트리의 모든 노드의 relative_weight를 dif만큼 변화시킨다.
void Update(int node,int dif) {
	samples[node].relative_weight += dif;
	for (int& c : samples[node].chileren)
		Update(c,dif);
}

int main()
{
	cin.tie(nullptr);
	cout.tie(nullptr);
	ios::sync_with_stdio(false);

	while (true) {
		cin >> n_sample >> n_exp;
		if (n_sample == 0) break;
		dset.Init(n_sample + 1);
		samples = vector<Node>(n_sample + 1);

		char task;
		int a,b,dif;
		while (n_exp--) {
			cin >> task;
			if (task == '!') {
				cin >> a >> b >> dif;
				int pa = dset.Find(a);
				int pb = dset.Find(b);
				if (pa == pb) continue;
				int dif_ab = samples[a].relative_weight - samples[b].relative_weight;

				if (samples[pa].size < samples[pb].size) {
					// a가 b보다 dif만큼 작아지게 해야한다.
					Update(pa, -dif_ab-dif);
				}
				else {
					// b가 a보다 dif만큼 커지게 해야한다.
					Update(pb,dif_ab+dif);
				}

				if (samples[pa].relative_weight < samples[pb].relative_weight)
					swap(pa,pb);
				samples[pa].chileren.push_back(pb);
				samples[pa].size += samples[pb].size;
				dset.Merge(pa,pb);
			}
			else {
				cin >> a >> b;
				int pa = dset.Find(a);
				int pb = dset.Find(b);
				if (pa != pb) {
					cout << "UNKNOWN\n";
					continue;
				}
				cout << samples[b].relative_weight - samples[a].relative_weight << '\n';
			}
		}
	}

	return 0;
}