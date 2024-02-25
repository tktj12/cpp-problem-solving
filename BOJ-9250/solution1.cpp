#include <iostream>
#include <vector>
#include <queue>
using namespace std;

// 알파벳 대문자를 저장하는 경우 각 노드는 26개의 자손을 가질 수 있다.
const int ALPHABETS = 26;
int ToNumber(char ch) { return ch - 'a'; }

class TrieNode {
public:
	TrieNode* children[ALPHABETS] = { 0, };
	// 이 노드가 종료 노드인지
	bool terminal = false;
	// 실패 연결, 이 노드에 대응되는 문자열의 접미사이면서 트라이에 포함된 최대 문자열
	TrieNode* fail;
	// 출력 문자열이 있는지
	bool output;

	TrieNode() {}
	~TrieNode() {
		for (int i = 0; i < ALPHABETS; i++)
			if (children[i])
				delete children[i];
	}

	// 이 노드를 루트로 하는 트라이에 문자열 key를 추가한다.
	void Insert(const char* key) {
		// 문자열이 끝나면 terminal만 참으로 바꾸고 종료한다.
		if (*key == 0) terminal = true;
		else {
			int next = ToNumber(*key);
			// 해당 자식 노드가 없다면 생성한다.
			if (children[next] == nullptr)
				children[next] = new TrieNode();

			// 해당 자식 노드를 재귀 호출
			children[next]->Insert(key + 1);
		}
	}

	// 이 노드를 루트로 하는 트라이에 문자열 key와 대응되는 노드를 찾는다.
	// 없으면 nullptr 반환
	TrieNode* Find(const char* key) {
		if (*key == 0) return this;
		int next = ToNumber(*key);
		if (children[next] == nullptr) return nullptr;
		return children[next]->Find(key + 1);
	}
};

// 트라이가 주어질 때 각 노드의 실패 연결과 출력 문자열 목록을 계산한다.
// 루트에서부터 시작해 한 단계씩 내려가며 각 노드의 실패 연결을 계산한다.
void ComputeFailFunc(TrieNode* root) {
	root->fail = root;
	queue<TrieNode*> q;
	q.push(root);
	while (!q.empty()) {
		TrieNode* here = q.front();
		q.pop();
		// here의 모든 자손에 대해 실패 연결을 계산하고 이들을 큐에 넣는다.
		for (int edge = 0; edge < ALPHABETS; ++edge) {
			TrieNode* child = here->children[edge];
			if (!child) continue;

			// 1레벨 노드의 실패 연결은 항상 루트
			if (here == root)
				child->fail = root;
			else {
				// 부모의 실패 연결을 따라가면서 실패 연결을 찾는다.
				TrieNode* t = here->fail;
				while (t != root && t->children[edge] == nullptr)
					t = t->fail;
				if (t->children[edge]) t = t->children[edge];
				child->fail = t;
			}
			// 출력 문자열 목록: 실패 연결을 따라간 노드에서 복사하고
			// 해당 노드에 대응되는 바늘 문자열도 추가한다.
			child->output = child->fail->output;
			if (child->terminal)
				child->output = true;

			q.push(child);
		}
	}
}

int main()
{
	cin.tie(nullptr);
	cout.tie(nullptr);
	ios::sync_with_stdio(false);

	TrieNode root;
	int N,Q;
	cin >> N;
	char s[10001];
	while (N--) {
		cin >> s;
		root.Insert(s);
	}
	ComputeFailFunc(&root);

	cin >> Q;
	while (Q--) {
		cin >> s;
		TrieNode* state = &root;
		bool found = false;
		for (int i = 0; s[i]!=NULL; i++) {
			int chr = ToNumber(s[i]);
			while (state != &root && state->children[chr] == nullptr)
				state = state->fail;
			if (state->children[chr])
				state = state->children[chr];

			if (state->output) {
				found = true;
				break;
			}
		}
		cout << (found ? "YES" : "NO") << '\n';
	}
	
	return 0;
}