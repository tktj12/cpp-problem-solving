#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct node {
	int v;
	node* left, * right;
};

node* MakeTree(vector<int>& preorder, vector<int>& inorder)
{
	if (preorder.size() == 0) return nullptr;

	node* ret = new node;
	ret->v = preorder[0];

	auto root_idx = find(inorder.begin(), inorder.end(), ret->v);
	vector<int> left_inorder(inorder.begin(), root_idx);
	vector<int> right_inorder(root_idx+1, inorder.end());

	vector<int> left_preorder(preorder.begin()+1, preorder.begin() + left_inorder.size()+1);
	vector<int> right_preorder(preorder.begin()+left_inorder.size()+1, preorder.end());

	ret->left = MakeTree(left_preorder, left_inorder);
	ret->right = MakeTree(right_preorder, right_inorder);

	return ret;
}

void PrintPostOrder(node* root)
{
	if (root == nullptr) return;
	PrintPostOrder(root->left);
	PrintPostOrder(root->right);
	cout << root->v << ' ';
}

void Destroy(node* root)
{
	if (root == nullptr) return;
	Destroy(root->left);
	Destroy(root->right);
	delete root;
}

int main()
{
	cin.tie(nullptr);
	cout.tie(nullptr);
	ios::sync_with_stdio(false);

	int tc;
	cin >> tc;
	while (tc--) {
		int n;
		cin >> n;
		vector<int>preorder(n);
		vector<int>inorder(n);
		for (int i = 0; i < n; i++) cin >> preorder[i];
		for (int i = 0; i < n; i++) cin >> inorder[i];

		node* root = MakeTree(preorder, inorder);
		PrintPostOrder(root);
		cout << '\n';
		Destroy(root);
	}
	return 0;
}