#include <iostream>
using namespace std;

const int ALPHABET_NUM = 26;
int ToNum(char ch) { return ch - 'a'; }

class Node {
public:
	bool terminal = false;
	char children_size = 0;
	Node* children[ALPHABET_NUM] = { 0, };
	Node() {}
	~Node() {
		for (int i = 0; i < ALPHABET_NUM; i++)
			if (children[i])
				delete children[i];
	}

	// 이 노드를 루트로 하는 트라이에 문자열 key를 추가한다.
	void Insert(const char* key) {
		// 문자열이 끝나면 terminal만 참으로 바꾸고 종료한다.
		if (*key == 0) terminal = true;
		else {
			int next = ToNum(*key);
			// 해당 자식 노드가 없다면 생성한다.
			if (children[next] == nullptr) {
				children_size++;
				children[next] = new Node();
			}

			// 해당 자식 노드를 재귀 호출
			children[next]->Insert(key + 1);
		}
	}
};

int typings;
void DFS(Node* root, int n)
{
	if (root->terminal) typings += n;
	if (root->terminal || root->children_size > 1 || n==0) n++;
	for (int i = 0; i < ALPHABET_NUM; i++)
		if (root->children[i])
			DFS(root->children[i],n);
}

int main()
{
	cin.tie(nullptr);
	cout.tie(nullptr);
	ios::sync_with_stdio(false);

	cout << fixed;
	cout.precision(2);

	int N;
	while (cin >> N) {
		Node root;
		typings = 0;

		char s[81];
		for (int i = 0; i < N; i++) {
			cin >> s;
			root.Insert(s);
		}

		DFS(&root,0);
		cout << (double)typings / N << '\n';
	}
	return 0;
}