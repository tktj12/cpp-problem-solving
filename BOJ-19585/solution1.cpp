#include <iostream>
#include <cstring>
#include <map>
using namespace std;

const int COLOR_TER = 0,NAME_TER= 1;
int ToNumber(char c) { return c - 'a'; }

class TrieNode {
public:
	map<int,TrieNode> children;
	// 이 노드가 종료 노드인지
	bool terminal[2] = { 0, };
	TrieNode() {}

	// 이 노드를 루트로 하는 트라이에 문자열 key를 추가한다.
	void Insert(const char* key, char type) {
		if (*key == 0) {
			terminal[type] = true;
		}
		else {
			int next = ToNumber(*key);

			if (type == NAME_TER)
				children[next].Insert(key - 1,type);
			else
				children[next].Insert(key + 1,type);
		}
	}

	static int mark[2001];
	void FindColor(const char* key,int q, int idx) {
		if (terminal[COLOR_TER]) mark[idx] = q;

		int next = ToNumber(*key);
		if (*key == 0 || children.find(next) == children.end()) return;

		children[next].FindColor(key + 1,q,idx + 1);
	}

	bool FindName(const char* key,int q,int color_last_idx) {
		if (color_last_idx < 0) return false;
		else if (terminal[NAME_TER] && mark[color_last_idx] == q) return true;

		int next = ToNumber(*key);
		if (*key == 0 || children.find(next) == children.end()) return false;
		
		return children[next].FindName(key - 1,q,color_last_idx-1);
	}
};

int TrieNode::mark[2001];

int main()
{
	cin.tie(nullptr);
	cout.tie(nullptr);
	ios::sync_with_stdio(false);

	memset(TrieNode::mark,-1,sizeof(TrieNode::mark));
	TrieNode trie;

	int n_color,n_name,query;
	cin >> n_color >> n_name;
	string s;
	for (int c = 0; c < n_color; c++) {
		cin >> s;
		trie.Insert(s.c_str(),COLOR_TER);
	}
	for(int n=0;n<n_name;n++) {
		cin >> s;
		s = '0' + s;
		s[0] = 0;
		trie.Insert(&s.back(),NAME_TER);
	}

	cin >> query;
	while (query--) {
		cin >> s;
		if (s.size() < 2) {
			cout << "No\n";
			continue;
		}

		trie.FindColor(s.c_str(),query,-1);
		cout << (trie.FindName(&s.back(),query,s.size() - 1) ? "Yes\n" : "No\n");
	}

	return 0;
}