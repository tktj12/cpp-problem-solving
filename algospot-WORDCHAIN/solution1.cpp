#include <iostream>
#include <vector>
#include <cstring>
#include <map>
#include <queue>
using namespace std;

const int ALPHABET = 26;
int graph[ALPHABET][ALPHABET]; // graph[i][j] : i->j 인 간선의 개수

inline int ToNum(char c) {
	return c - 'a';
}

// graph가 오일러 서킷 혹은 오일러 트레일을 갖고있다면 그 시작점을 반환
// 둘 다 없다면 음수 반환
int IsPossible()
{
	int random_start;
	int out_is_one_more = -1; // 나가는 간선이 하나 더 많은 알파벳
	int in_is_one_more = -1; // 들어오는 간선이 하나 더 많은 알파벳
	for (int i = 0; i < ALPHABET; i++) {
		int in_edge = 0, out_edge = 0;
		for (int j = 0; j < ALPHABET; j++) {
			in_edge += graph[j][i];
			out_edge += graph[i][j];
		}
		if (abs(in_edge - out_edge) >= 2)
			return -1;
		else if (in_edge + 1 == out_edge) {
			if (out_is_one_more != -1) return -1;
			out_is_one_more = i;
		}
		else if (out_edge + 1 == in_edge) {
			if (in_is_one_more != -1) return -1;
			in_is_one_more = i;
		}
		else if (in_edge) {
			random_start = i;
		}
	}

	if (out_is_one_more != -1) {
		if (in_is_one_more == -1) return -1;
		return out_is_one_more;
	}
	else if (in_is_one_more != -1)
		return -1;
	else
		return random_start;
}

void WordChain(map<int, map<int, queue<string> > >& edge_to_str, int vertex, vector<string>& chain)
{
	for (int i = 0; i < ALPHABET; i++) {
		while (graph[vertex][i]-- > 0) {
			WordChain(edge_to_str, i, chain);
			chain.push_back(edge_to_str[vertex][i].front());
			edge_to_str[vertex][i].pop();
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
		memset(graph, 0, sizeof(graph));
		int n;
		cin >> n;
		map<int, map<int, queue<string> > > edge_to_str;
		for (int i = 0; i < n; i++) {
			string word;
			cin >> word;
			int first = ToNum(word[0]);
			int last = ToNum(word.back());
			graph[first][last]++;
			edge_to_str[first][last].push(word);
		}

		int start = IsPossible();
		if (start == -1) {
			cout << "IMPOSSIBLE\n";
			continue;
		}

		vector<string> chain;
		WordChain(edge_to_str, start, chain);

		bool impossible = false;
		for (int i = 0; i < ALPHABET; i++)
			for (int j = 0; j < ALPHABET; j++)
				if (graph[i][j] > 0)
					impossible = true;

		if (impossible) {
			cout << "IMPOSSIBLE\n";
			continue;
		}
		
		for (int i = chain.size() - 1; i >= 0; i--)
			cout << chain[i] << ' ';
		cout << '\n';
	}
	return 0;
}