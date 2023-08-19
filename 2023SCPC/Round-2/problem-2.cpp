// Á¤´ä 200Á¡!!

#include <iostream>
#include <vector>
using namespace std;
using ull = unsigned long long;

class CharStack {
public:
	int top = -1;
	pair<char, int> st[1000010];
	CharStack() {}

	pair<char,int> Pop() {
		return st[top--];
	}

	pair<char,int> Top() {
		return st[top];
	}

	void Push(const char c, const int i) {
		st[++top] = { c,i };
	}

	void Init() {
		top = -1;
	}

	bool Empty() {
		return top < 0;
	}
}st;

class IntStack {
public:
	int top = -1;
	int st[1000010];
	IntStack() {}

	int Pop() {
		return st[top--];
	}

	char Top() {
		return st[top];
	}

	void Push(const int i) {
		st[++top] = i;
	}

	void Init() {
		top = -1;
	}

	bool Empty() {
		return top < 0;
	}

	void Add() {
		if (Empty()) Push(1);
		else st[top]++;
	}
}i_st;

inline bool IsOpenBracket(const char c) {
	if (c == '(' || c == '{') return true;
	return false;
}

inline bool IsMatched(const char a, const char b) {
	if (a == '(' && b == ')' || a == '{' && b == '}') return true;
	return false;
}

inline ull F(const ull n)
{
	return (n * (n + 1))>>1;
}

int main(int argc, char** argv)
{
	cin.tie(nullptr);
	cout.tie(nullptr);
	ios::sync_with_stdio(false);
	int T, test_case;
	cin >> T;
	for (test_case = 0; test_case < T; test_case++)
	{
		st.Init();
		i_st.Init();
		ull Answer = 0;
		int n;
		string str;
		cin >> n >> str;

		for (int i = 0; i < n; i++) {
			char now = str[i];
			if (IsOpenBracket(now))
				st.Push(now, i);
			else {
				pair<char, int> match = st.Pop();
				if (!IsMatched(match.first, now)) {
					while (!i_st.Empty()) Answer += F(i_st.Pop());

					st.Init();
					i_st.Init();
					continue;
				}

				pair<char, int> t;
				if (st.Empty()) t = { 0,-2 };
				else t = st.Top();
				
				if (match.second == i - 1) {
					if (t.second == match.second - 1)
						i_st.Push(1);
					else
						i_st.Add();
				}
				else {
					Answer += F(i_st.Pop());

					if (t.second == match.second - 1)
						i_st.Push(1);
					else
						i_st.Add();
				}
			}
		}

		while (!i_st.Empty()) Answer += F(i_st.Pop());

		cout << "Case #" << test_case + 1 << '\n';
		cout << Answer << '\n';
	}

	return 0;
}