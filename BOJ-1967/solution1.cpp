#include <iostream>
#include <vector>
using namespace std;

class Node {
public:
	vector<int> children;
	vector<int> weight;

	Node() {}

	void Insert(int n, int w)
	{
		children.push_back(n);
		weight.push_back(w);
	}
}nodes[10001];

int answer;
// node번 노드에서 갈 수 있는 길 중 가장 긴 길 반환
int FindDiameter(int node)
{
	Node& now = nodes[node];
	int ret = 0;
	for (int i = 0; i < now.children.size(); i++) {
		int temp = FindDiameter(now.children[i]) + now.weight[i];
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
	for (int i = 1; i < n; i++) {
		int parent, child, weight;
		cin >> parent >> child >> weight;
		nodes[parent].Insert(child, weight);
	}

	FindDiameter(1);
	cout << answer;

	return 0;
}