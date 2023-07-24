#include <iostream>
#include <vector>
#include <cstdlib>
#include <memory>
#include <algorithm>
using namespace std;

class Node;
typedef unique_ptr<Node> NodePtr;
typedef pair<NodePtr, NodePtr> NodePair;
class Node {
public:
	int idx;
	int priority;
	int size;
	NodePtr left;
	NodePtr right;

	Node(int idx) : idx(idx), priority(rand()) {
		left = nullptr;
		right = nullptr;
		size = 1;
	}

	void CalcSize() {
		size = 1;
		if (left) size += left->size;
		if (right) size += right->size;
	}

	void SetLeft(NodePtr& new_node) { left = move(new_node); CalcSize(); }
	void SetRight(NodePtr& new_node) { right = move(new_node); CalcSize(); }
};

NodePair Split(NodePtr& root, int backs)
{
	if (root == nullptr) return { nullptr, nullptr };

	int right_size = 0, left_size = 0;
	if (root->right) right_size = root->right->size;
	if (root->left) left_size = root->left->size;

	if (right_size >= backs) {
		NodePair subtree = Split(root->right, backs);
		root->SetRight(subtree.first);
		return { move(root), move(subtree.second) };
	}
	else {
		NodePair subtree = Split(root->left, backs - right_size - 1);
		root->SetLeft(subtree.second);
		return { move(subtree.first), move(root) };
	}
}

NodePtr Insert(NodePtr& root, NodePtr& new_node, int backs)
{
	if (root == nullptr) return move(new_node);

	int right_size=0, left_size=0;
	if (root->right) right_size = root->right->size;
	if (root->left) left_size = root->left->size;

	if (root->priority < new_node->priority) {
		if (right_size >= backs) {
			NodePair subtree = Split(root->right, backs);
			root->SetRight(subtree.first);
			new_node->SetLeft(root);
			new_node->SetRight(subtree.second);
		}
		else {
			NodePair subtree = Split(root->left, backs - right_size-1);
			root->SetLeft(subtree.second);
			new_node->SetRight(root);
			new_node->SetLeft(subtree.first);
		}
		return move(new_node);
	}

	if (right_size >= backs) {
		root->right = Insert(root->right, new_node, backs);
		root->SetRight(root->right);
	}
	else {
		root->left = Insert(root->left, new_node, backs - right_size - 1);
		root->SetLeft(root->left);
	}

	return move(root);
}

vector<pair<int, int> > answer;
void MakeAnswer(NodePtr& root)
{
	if (root == nullptr) return;
	
	MakeAnswer(root->left);
	answer.push_back({ root->idx, answer.size() + 1 });
	MakeAnswer(root->right);
}

int main()
{
	cin.tie(nullptr);
	std::cout.tie(nullptr);
	ios::sync_with_stdio(false);

	int tc;
	cin >> tc;
	srand(1007);
	while (tc--) {
		int n;
		cin >> n;

		NodePtr treap;
		for (int i = 0; i < n; i++) {
			int backs;
			cin >> backs;
			NodePtr new_node(new Node(i));
			treap = Insert(treap, new_node, backs);
		}

		answer.clear();
		MakeAnswer(treap);
		std::sort(answer.begin(), answer.end());
		for (int i = 0; i < n; i++)
			std::cout << answer[i].second << ' ';
		std::cout << '\n';
	}

	return 0;
}