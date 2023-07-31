#include <iostream>
#include <vector>
#include <queue>
using namespace std;

const int ALPHABET = 26;
inline int ToNum(char c) {
	return c - 'a';
}

class TrieNode {
public:
	TrieNode* children[ALPHABET] = { nullptr, };
	TrieNode* path[ALPHABET] = { nullptr, };	// 알파벳 별로 다음 노드를 알려줌
	TrieNode* fail = nullptr;
	bool terminal = false;
	int num_of_case[2] = { 0, 0}; // 해당 노드일 경우의 수

	TrieNode() {}

	void destroy()
	{
		for (int i = 0; i < ALPHABET; i++) 
			if (children[i]) {
				children[i]->destroy();
				delete children[i];
			}
	}

	void Insert(const char* key)
	{
		if (*key == 0) {
			terminal = true;
			return;
		}
		
		int next = ToNum(*key);
		if (children[next] == nullptr) children[next] = new TrieNode;
		children[next]->Insert(key + 1);
	}
	
	// TrieNode* find(const char* key)

	// 모든 path의 !s에 s인 case들을 전파
	void ForwardCase(bool s)
	{
		if (terminal) return;

		bool not_s = !s;
		for (int i = 0; i < ALPHABET; i++) {
			path[i]->num_of_case[not_s] += num_of_case[s];
			if(children[i])children[i]->ForwardCase(s);
		}
	}

	// s인 case 값 초기화
	void InitCase(bool s)
	{
		if (terminal) return;

		num_of_case[s] = 0;
		num_of_case[!s] %= 10007;
		for (int i = 0; i < ALPHABET; i++) {
			if (children[i])children[i]->InitCase(s);
		}
	}

	// 이 노드를 루트로 하는 서브트리의 case들을 계산
	int CountCase(bool s)
	{
		if (terminal) return 0;

		int ret = num_of_case[s];
		for (int i = 0; i < ALPHABET; i++) {
			if (children[i]) ret += children[i]->CountCase(s);
		}
		return ret;
	}
};

// 트라이에 존재하고 가장 길이가 긴, 자신의 진 접미사의 위치를 구함
// 실패함수를 통해 갈 수 있는 접미사 중에 terminal이 있다면 해당 노드 또한 terminal이 된다.
void ComputeFailFunc(TrieNode* root)
{
	queue<TrieNode*> q;
	root->fail = root;
	for (int i = 0; i < ALPHABET; i++) {
		if (root->children[i]) {
			root->children[i]->fail = root;
			q.push(root->children[i]);
		}
	}

	while (!q.empty()) {
		TrieNode* now = q.front(); q.pop();
		
		for (int i = 0; i < ALPHABET; i++) {
			if (now->children[i] == nullptr) continue;
			
			TrieNode* t = now->fail;
			while (t != root && t->children[i] == nullptr)
				t = t->fail;
			if (t->children[i]) t = t->children[i];
			
			now->children[i]->fail = t;
			if (t->terminal) now->children[i]->terminal = true;

			q.push(now->children[i]);
		}
	}
}

// 얕은 노드 먼저 path를 계산
// 다음 노드가 없을 경우 실패시 연결되는 노드의 path를 따라가면 됨
void CalcPath(TrieNode* root)
{
	for (int i = 0; i < ALPHABET; i++) {
			root->path[i] = root;
	}

	queue<TrieNode*> q;
	q.push(root);
	while (!q.empty()) {
		TrieNode* now = q.front(); q.pop();
		TrieNode* fail = now->fail;
		for (int i = 0; i < ALPHABET; i++) {
			if (now->children[i]) {
				now->path[i] = now->children[i];
				q.push(now->children[i]);
			}
			else
				now->path[i] = fail->path[i];
		}
	}
}

int main()
{
	cin.tie(nullptr);
	cout.tie(nullptr);
	ios::sync_with_stdio(false);

	int tc;
	cin >> tc;
	while (tc--) {
		int n, m;
		cin >> n >> m;

		TrieNode root;
		for (int i = 0; i < m; i++) {
			char word[20];
			cin >> word;
			root.Insert(word);
		}

		ComputeFailFunc(&root);
		CalcPath(&root);

		root.num_of_case[0] = 1;

		for (int i = 0; i < n; i++) {
			bool s = i % 2;
			root.ForwardCase(s);
			root.InitCase(s);
		}
		
		cout << root.CountCase(n % 2) % 10007 << '\n';
		root.destroy();
	}
	return 0;
}