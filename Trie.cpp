// 알파벳 대문자를 저장하는 경우 각 노드는 26개의 자손을 가질 수 있다.
const int ALPHABETS = 26;
int ToNumber(char ch) { return ch - 'A'; }

class TrieNode {
	TrieNode* children[ALPHABETS] = { 0, };
	// 이 노드가 종료 노드인지
	bool terminal = false;
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