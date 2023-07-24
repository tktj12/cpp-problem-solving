#include <cstdlib>
#include <memory>
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

	int right_size = 0, left_size = 0;
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
			NodePair subtree = Split(root->left, backs - right_size - 1);
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

NodePtr Merge(NodePtr& a, NodePtr& b)
{
	if (a == nullptr) return move(b);
	if (b == nullptr) return move(a);

	if (a->priority < b->priority) {
		b->left = Merge(a, b->left);
		b->CalcSize();
		return move(b);
	}
	else {
		a->right = Merge(a->right, b);
		a->CalcSize();
		return move(a);
	}
}

NodePtr Erase(NodePtr& root, int kth)
{
	if (root == nullptr) return nullptr;

	int left_size = 0, right_size = 0;
	if (root->left) left_size = root->left->size;
	if (root->right) right_size = root->right->size;

	if (kth <= left_size) {
		root->left = Erase(root->left, kth);
		root->CalcSize();
	}
	else if (kth == left_size + 1) {
		return Merge(root->left, root->right);
	}
	else if (kth <= root->size) {
		root->right = Erase(root->right, kth - left_size - 1);
		root->CalcSize();
	}

	return move(root);
}