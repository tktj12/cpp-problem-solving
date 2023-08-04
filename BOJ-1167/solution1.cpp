#include <iostream>
#include <vector>
#include <set>
using namespace std;

class Node {
public:
	vector<int> edge;
	vector<int> weight;

	Node() {}

	void Insert(int n, int w)
	{
		edge.push_back(n);
		weight.push_back(w);
	}
}nodes[100001];

int answer;
bool visit[100001];
// node번 노드에서 갈 수 있는 길 중 가장 긴 길 반환
int FindDiameter(int node)
{
	Node& now = nodes[node];
	int ret = 0;
	for (int i = 0; i < now.edge.size(); i++) {
		if (visit[now.edge[i]]) continue;
		visit[now.edge[i]] = true;
		int temp = FindDiameter(now.edge[i]) + now.weight[i];
		answer = max(answer, ret + temp);
		ret = max(ret, temp);
	}

	return ret;
}

int main()
{
	cin.tie(nullptr);
	cout.tie(nullptr);
	ios::sync_with_stdio(false);

	int n;
	cin >> n;
	set<pair<int, int> > appear;
	int start=1;
	for (int i = 1; i <= n; i++) {
		int vertex, child, weight;
		cin >> vertex;

		while (1) {
			cin >> child;
			if (child == -1) break;
			cin >> weight;
			
			nodes[vertex].Insert(child, weight);
		}
	}

	visit[1] = true;
	FindDiameter(1);
	cout << answer;

	return 0;
}