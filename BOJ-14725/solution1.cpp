#include <iostream>
#include <vector>
#include <cstring>
#include <map>
using namespace std;

class Node {
public:
	string name;
	map<string,Node> children;

	Node(string name = "") : name(name) {}

	void Insert(int depth, vector<string>& dat) {
		if (dat.size() == depth) return;

		auto iter = children.find(dat[depth]);
		if (iter == children.end()) {
			Node new_node(dat[depth]);
			new_node.Insert(depth + 1, dat);
			children[dat[depth]] = new_node;
		}
		else
			iter->second.Insert(depth + 1, dat);
	}
};

void DfsPrintNodes(int depth, Node& root)
{
	if (depth > 0) {
		for (int i = 0; i < depth-1; i++)
			cout << "--";
		cout << root.name << '\n';
	}

	for (auto iter = root.children.begin(); iter != root.children.end(); iter++)
		DfsPrintNodes(depth + 1, iter->second);
}

int main()
{
	cin.tie(nullptr);
	cout.tie(nullptr);
	ios::sync_with_stdio(false);

	Node root(".");

	int n;
	cin >> n;
	for (int i = 0; i < n; i++) {
		int k;
		cin >> k;
		vector<string> dat(k);
		for (int j = 0; j < k; j++) cin >> dat[j];
		root.Insert(0, dat);
	}

	DfsPrintNodes(0, root);

	return 0;
}