#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

using query = pair<pair<int,int>,int>;

int block_size;
bool Compare(const query& a,const query& b) {
	int b1 = a.first.first / block_size;
	int b2 = b.first.first / block_size;
	if (b1 != b2) return b1 < b2;
	if (b1 % 2 == 0) return a.first.second < b.first.second;
	return a.first.second > b.first.second;
}

class DLL;
class Node {
public:
	int cnt = 0;
	Node *left, *right;
	DLL* head;

	Node() {
		head = nullptr;
		left = right = nullptr;
	}
}nums[100001];

class DLL {
public:
	Node* last=nullptr;
	DLL() {}
}dll[100001];

int NodeOut(Node& node) {
	DLL* head = node.head;
	if (head == nullptr) return node.cnt;

	if (node.right) {
		node.right->left = node.left;
	}
	else {
		head->last = node.left;
	}

	if (node.left) {
		node.left->right = node.right;
	}

	node.left = node.right = nullptr;
	node.head = nullptr;
	return node.cnt;
}

void NodeIn(Node& node, int group) {
	node.head = &dll[group];
	node.left = node.head->last;
	if (node.left) {
		node.left->right = &node;
	}
	node.head->last = &node;
}

inline int Move(Node& node, int offset) {
	int next = NodeOut(node) + offset;
	if (next > 0) NodeIn(node,next);
	return node.cnt = next;
}

int arr[100000], answer[100000];
vector<query> mo;

int main()
{
	cin.tie(nullptr);
	cout.tie(nullptr);
	ios::sync_with_stdio(false);

	int N; cin >> N;
	block_size = (int)sqrt(N);
	int k = (int)(N / block_size) + (N%block_size > 0);
	for (int i = 0; i < N; i++) cin >> arr[i];

	int Q; cin >> Q;
	mo.resize(Q);
	for (int i = 0; i < Q; i++) {
		int l,r; cin >> l >> r;
		l--,r--;
		mo.push_back({ { l,r },i });
	}
	sort(mo.begin(),mo.end(),Compare);

	int start = 0,end = -1, ans=0;
	for (query& q : mo) {
		int i = q.first.first;
		int j = q.first.second;

		int it;
		while (end < j) {
			it = arr[++end];
			ans = max(ans,Move(nums[it],1));
		}
		while (end > j) {
			it = arr[end--];
			Move(nums[it],-1);
		}

		while (start < i) {
			it = arr[start++];
			Move(nums[it],-1);
		}
		while (start > i) {
			it = arr[--start];
			ans = max(ans,Move(nums[it],1));
		}

		while (dll[ans].last == nullptr) ans--;
		answer[q.second] = ans;
	}

	for (int i = 0; i < Q; i++)
		cout << answer[i] << '\n';

	return 0;
}