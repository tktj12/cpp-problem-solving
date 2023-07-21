#include <iostream>
#include <vector>
#include <cstring>
#include <list>
using namespace std;

struct node {
	int idx;
	node* next = nullptr;

	node(int i) : idx(i) {}
};

node* insert(node*& cur, int idx) {
	if (cur == nullptr) {
		cur = new node(idx);
		return cur;
	}

	cur->next = new node(idx);
	return cur->next;
}

void erase(node* cur) {
	node* del = cur->next;
	cur->next = del->next;
	delete del;
}

int main()
{
	cin.tie(nullptr);
	cout.tie(nullptr);
	ios::sync_with_stdio(false);

	int tc;
	cin >> tc;
	while (tc--) {
		int n, k;
		cin >> n >> k;
		int alive = n;
		node* head = nullptr;
		node* cur = insert(head, 0);
		for (int i = 1; i < n; i++)
			cur = insert(cur, i);
		cur->next = head;

		erase(cur);
		while (--alive > 2) {
			for (int i = 0; i < k - 1; i++)
				cur = cur->next;
			erase(cur);
		}
		if (cur->idx < cur->next->idx)
			cout << cur->idx+1 << ' ' << cur->next->idx + 1 << '\n';
		else
			cout << cur->next->idx + 1 << ' ' << cur->idx + 1 << '\n';

		erase(cur);
		delete cur;
	}

	return 0;
}