#include <iostream>
#include <stack>
using namespace std;

bool IsPrior(char a, char b) {
	if ((a == '*' || a == '/') && (b == '+' || b == '-'))
		return true;
	else return false;
}

string ans;
int FaceBracket(int idx, string& exp)
{
	stack<char> op;
	while (exp[idx] != ')' && idx < exp.size()) {
		char now = exp[idx];
		if ('A' <= now && now <= 'Z')
			ans += now;
		else {
			if (now == '(')
				idx = FaceBracket(idx + 1, exp);
			else if (op.empty() || IsPrior(now, op.top()))
				op.push(now);
			else {
				while (!op.empty() && !IsPrior(now, op.top())) {
					ans += op.top();
					op.pop();
				}
				op.push(now);
			}
		}
		idx++;
	}
	
	while (!op.empty()) {
		ans += op.top();
		op.pop();
	}
	return idx;
}

int main()
{
	string exp;
	cin >> exp;
	exp += ')';
	FaceBracket(0, exp);
	cout << ans;

	return 0;
}