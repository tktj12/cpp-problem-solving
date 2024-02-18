#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

typedef int KeyType;
// treap의 한 노드를 저장한다.
class Node {
public:
	KeyType key;  // 노드에 저장된 원소
	int priority; // 이 노드의 우선순위
	int size;     // 이 노드를 루트로 하는 서브트리의 크기
	Node* left,* right; // 두 자식 노드의 포인터

	Node() {};
	void SetLeft(Node* new_left) { left = new_left; CalcSize(); }
	void SetRight(Node* new_right) { right = new_right; CalcSize(); }
	// size 멤버를 갱신한다.
	void CalcSize() {
		size = 1;
		if (left) size += left->size;
		if (right) size += right->size;
	}
};

typedef pair<Node*,Node*> NodePair;
//root를 루트로 하는 트립을 key 미만의 값과 이상의 값을 갖는 두 개의 트립으로 분리한다.
NodePair Split(Node* root,KeyType key) {
	if (root == nullptr) return NodePair(nullptr,nullptr);
	// 루트가 key 미만이면 오른쪽 서브트리를 쪼갠다.
	if (root->key < key) {
		NodePair rs = Split(root->right,key);
		root->SetRight(rs.first);
		return NodePair(root,rs.second);
	}
	// 루트가 key 이상이면 왼쪽 서브트리를 쪼갠다.
	NodePair ls = Split(root->left,key);
	root->SetLeft(ls.second);
	return NodePair(ls.first,root);
}

// root를 루트로 하는 트립에 새 노드 node를 삽입한 뒤 결과 트립의 루트를 반환한다.
Node* Insert(Node* root,Node* new_node) {
	if (root == nullptr) return new_node;

	if (root->priority < new_node->priority) {
		// node가 루트를 대체해야 한다.
		// 해당 서브트리를 반으로 잘라 각각 자손으로 한다.
		NodePair splitted = Split(root,new_node->key);
		new_node->SetLeft(splitted.first);
		new_node->SetRight(splitted.second);
		return new_node;
	}
	else if (new_node->key < root->key)
		root->SetLeft(Insert(root->left,new_node));
	else
		root->SetRight(Insert(root->right,new_node));
	return root;
}

// a와 b가 두 개의 트립이고, max(a) < min(b)를 만족함은 전제 조건으로 한다.
Node* Merge(Node* a,Node* b) {
	if (a == nullptr) return b;
	if (b == nullptr) return a;

	if (a->priority < b->priority) {
		b->SetLeft(Merge(a,b->left));
		return b;
	}
	else {
		a->SetRight(Merge(a->right,b));
		return a;
	}
}

// root를 루트로 하는 트립에서 key를 지우고 결과 트립의 루트를 반환한다.
pair<int, Node*> Erase(Node* root,KeyType key) {
	if (root == nullptr) return { 0,root };

	int less_nums=0;
	if (root->key == key) {
		// root를 지우고 양 서브트리를 합친 뒤 반환한다.
		if(root->left) less_nums = root->left->size;
		Node* ret = Merge(root->left,root->right);
		return { less_nums, ret };
	}

	if (key < root->key) {
		pair<int,Node*> tp = Erase(root->left,key);
		less_nums = tp.first;
		root->SetLeft(tp.second);
	}
	else {
		less_nums = 1;
		if (root->left) less_nums += root->left->size;

		pair<int,Node*> tp = Erase(root->right,key);
		less_nums += tp.first;
		root->SetRight(tp.second);
	}
	return { less_nums,root };
}

int N,M;
int DVD2Key[100001];
Node new_nodes[200010];
int node_cnt;

Node* NewNode(const KeyType& _key) {
	Node* ret = &new_nodes[node_cnt++];
	ret->key = _key;
	ret->priority = rand();
	ret->left = ret->right = nullptr;
	ret->size = 1;
	return ret;
}

int main()
{
	cin.tie(nullptr);
	cout.tie(nullptr);
	ios::sync_with_stdio(false);

	int tc;
	cin >> tc;
	while (tc--) {
		Node* root = nullptr;
		node_cnt = 0;

		cin >> N >> M;
		for (int i = 1; i <= N; i++) {
			DVD2Key[i] = i;
			root = Insert(root,NewNode(i));
		}

		for(int i=0;i<M;i++){
			int q; cin >> q;
			pair<int,Node*> tp = Erase(root,DVD2Key[q]);
			cout << tp.first << ' ';
			root = tp.second;

			DVD2Key[q] = -i;
			root = Insert(root,NewNode(-i));
		}
		cout << '\n';
	}

	return 0;
}