#include <iostream>
#include <vector>
using namespace std;

const int ALPHABET = 26;
inline int ToNum(char c) {
	return c - 'A';
}
class TrieNode {
public:
	vector<TrieNode> children;
	bool terminal = false;
	int max_freq = 0, tap_path = -1;

	TrieNode() {}

	void Generate() {
		children = vector<TrieNode>(ALPHABET);
	}

	void Insert(const char* key, int freq)
	{
		// 단어의 끝을 만나면
		if (*key == 0) {
			terminal = true;
			if (freq >= max_freq) {
				max_freq = freq;
				tap_path = -2;
			}
			return;
		}

		int next = ToNum(*key);
		// 출현 빈도가 더 높거나, 같은데 사전순으로 빠른 경우
		// tap_path 최신화
		if (freq > max_freq || freq == max_freq && next < tap_path) {
			max_freq = freq;
			tap_path = next;
		}

		if (children.empty()) Generate();
		children[next].Insert(key + 1, freq);
	}

	// 찾는 단어가 있는지, 몇 개를 스킵할 수 있는지를 반환해야함
	// key : 현재 알파벳, skip : 현재까지 몇 개의 알파벳을 스킵했는지
	pair<bool, int> Find(const char* key, int skip, int prev_freq)
	{
		// 단어의 끝을 만나면
		if (*key == 0) {
			if (tap_path == -2)
				return { terminal, skip };
			else
				return { false,0 }; // 단어를 못 찾은 것과 같은 효과
		}
		
		if (prev_freq != max_freq) skip = 0;

		int next = ToNum(*key);
		if (next == tap_path) skip++;
		else skip = 0;

		if (children.empty()) return { false, 0 };
		else return children[next].Find(key + 1, skip, max_freq);
	}
};

int main()
{
	cin.tie(nullptr);
	cout.tie(nullptr);
	ios::sync_with_stdio(false);

	int tc;
	cin >> tc;
	while (tc--) {
		TrieNode root;
		int n, m;
		cin >> n >> m;
		while (n--) {
			char word[11];
			int freq;
			cin >> word >> freq;
			root.Insert(word, freq);
		}

		root.tap_path = -2;
		int ans = m-1;
		while (m--) {
			string word;
			cin >> word;
			ans += word.size();

			pair<bool, int> find_res = root.Find(word.c_str(), 0, -1);
			if (find_res.first && find_res.second > 1) ans -= find_res.second - 1;
		}

		cout << ans << '\n';
	}
	return 0;
}