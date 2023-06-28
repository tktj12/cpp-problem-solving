#include <iostream>
#include <vector>

using namespace std;
void BinarySearchAndDetermine(vector<int>& C, int n, int left, int right);

int main()
{
	cin.tie(nullptr);
	cout.tie(nullptr);
	ios::sync_with_stdio(false);

	int tc;
	cin >> tc;
	while (tc--) {
		int n, now;
		cin >> n;
		vector<int> C(2); // C[i] = (���ݱ��� ����) �κ� �迭�� ���� ���� i�� ���� �κ� ���� �� �ּ��� ������ ��
		
		n--;
		cin >> now;
		C[1] = now;
		
		while (n--) {
			cin >> now;
			BinarySearchAndDetermine(C, now, 1, C.size()-1);
		}
		cout << C.size()-1 << '\n';
	}

	return 0;
}

void BinarySearchAndDetermine(vector<int>& C, int n, int left, int right)
{
	int i = left + (right-left) / 2;
	
	if (n < C[i]) {
		if (i == 1)	C[i] = n;
		else BinarySearchAndDetermine(C, n, left, i-1);
	}
	else if (n > C[i]) {
		if (i == C.size() - 1) C.push_back(n);
		else if (n < C[i + 1]) C[i + 1] = n;
		else BinarySearchAndDetermine(C, n, i+1,right);
	}
}