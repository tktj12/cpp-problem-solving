#include <iostream>
#include <vector>
#include <random>
using namespace std;

class Node;
using PNN = pair<Node*, Node*>;

// Treap Node
class Node {
public:
	int val;
	int cnt, tree_size;
	int priority;
	Node* left=nullptr, *right=nullptr;

	Node(int val, int cnt=1) : val(val), cnt(cnt), tree_size(cnt) {
		priority = rand();
	}

	bool Push(int v, int c) {
		if (val == v) {
			cnt += c;
			tree_size += c;
			return true;
		}
		else if (val < v) {
			if (!right) return false;
			else {
				if (right->Push(v, c)) {
					CalcSize();
					return true;
				}
				else return false;
			}
		}
		else {
			if (!left) return false;
			else {
				if (left->Push(v, c)) {
					CalcSize();
					return true;
				}
				else return false;
			}
		}
	}

	void CalcSize() {
		tree_size = cnt;
		if (left) tree_size += left->tree_size;
		if (right) tree_size += right->tree_size;
	}

	void SetLeft(Node* new_node) { left = new_node; CalcSize(); };
	void SetRight(Node* new_node) { right = new_node; CalcSize(); };
};

PNN Split(Node* root, int val)
{
	if (root == nullptr) return { nullptr,nullptr };

	if (root->val < val) {
		PNN splitted = Split(root->right, val);
		root->SetRight(splitted.first);
		return { root, splitted.second };
	}
	else {
		PNN splitted = Split(root->left, val);
		root->SetLeft(splitted.second);
		return { splitted.first, root };
	}
}

Node* Insert(Node* root, Node* new_node)
{
	if (root == nullptr) return new_node;

	if (root->val == new_node->val) {
		root->cnt += new_node->cnt;
		root->tree_size += new_node->cnt;
		delete new_node;
		return root;
	}
	else if (root->priority > new_node->priority) {
		if(root->val < new_node->val)
			root->SetRight(Insert(root->right, new_node));
		else
			root->SetLeft(Insert(root->left, new_node));
		return root;
	}
	else {
		PNN splitted = Split(root, new_node->val);
		new_node->SetRight(splitted.second);
		new_node->SetLeft(splitted.first);
		return new_node;
	}
}

Node* Merge(Node* a, Node* b) // Assume max(a) <= min(b) 
{
	if (!a) return b;
	if (!b) return a;

	if (a->priority < b->priority) {
		b->SetLeft(Merge(a, b->left));
		return b;
	}
	else {
		a->SetRight(Merge(a->right, b));
		return a;
	}
}

Node* Erase(Node* root, int v, int c)
{
	if (root == nullptr) return nullptr;

	if (root->val == v) {
		if (root->cnt == c) {
			Node* new_root = Merge(root->left, root->right);
			delete root;
			return new_root;
		}
		else {
			root->cnt -= c;
			root->tree_size -= c;
			return root;
		}
	}
	else if (root->val < v) {
		root->SetRight(Erase(root->right, v, c));
		return root;
	}
	else {
		root->SetLeft(Erase(root->left, v, c));
		return root;
	}
}

Node* EraseKth(Node* root, int k, int& taste)
{
	if (root == nullptr) return nullptr;

	if (root->left) {
		if (root->left->tree_size < k)
			k -= root->left->tree_size;
		else {
			root->SetLeft(EraseKth(root->left, k, taste));
			return root;
		}
	}

	if (k <= root->cnt) {
		taste = root->val;
		return Erase(root, root->val, 1);
	}
	else {
		root->SetRight(EraseKth(root->right, k-root->cnt,taste));
		return root;
	}
}

int main()
{
	cin.tie(nullptr);
	cout.tie(nullptr);
	ios::sync_with_stdio(false);
	srand(1007);
	
	Node* treap = nullptr;

	int n;
	cin >> n;
	for (int i = 0; i < n; i++) {
		int a, b, c;
		cin >> a >> b;
		if (a == 1) {
			int taste;
			treap = EraseKth(treap, b, taste);
			cout << taste << '\n';
		}
		else {
			cin >> c;
			if (c > 0) {
				if (!treap) treap = Insert(treap, new Node(b, c));
				else if (!treap->Push(b, c))
					treap = Insert(treap, new Node(b, c));
			}
			else treap = Erase(treap, b, -c);
		}
	}

	return 0;
}