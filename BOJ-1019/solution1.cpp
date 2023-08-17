#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

int main()
{
	string num;
	cin >> num;
	int n=0, e=1;
	for (int i = num.size()-1; i >= 0; i--) {
		num[i] -= '0';
		n += num[i]*e;
		e *= 10;
	}

	vector<long long> ans(10);

	// ���� �ڸ����� �� ���ڰ� �� �ڸ����� �� ���� ���� �� �ִ��� ����Ѵ�.
	// ex) num = 20�� �� 1�� ���� �ڸ����� �� �� ��Ÿ����.
	e = 1; // ���� ����� �ڸ���
	for (int i = num.size()-1; i >= 0; i--) {
		int now = num[i];
		int back = n % e;

		// �ڿ� �ִ� �� + 1 ��ŭ ���� now�� ������. 
		// ex) 87���� now�� ���� �ڸ� 8�� �� now�� 80~87���� 8�� ������
		ans[now--] += back + 1;	 

		// �ٵ� now�� 0�̾��ٸ� e�� �� �� �������� ������ e�� �̸� �������
		if (now == -1) ans[0] -= e;	

		// e�� �ڸ������� e��ŭ ������.
		// ex) 89���� �����ڸ� 7~1�� 10���� ������
		while (now > 0) ans[now--] += e;

		// e�ڸ��� ������ e�� Ŀ���� ���� num/(10*e) ��ŭ �� ����
		// ex) num = 300�� �� 0���� 300���� ���� �ڸ��� ���� 3*10 �� ����
		// ���� �ڸ��� 1�� ��� : 10~19, 110~119, 210~219
		// ��, �� ����� ��Ȯ���� 300������ �ƴ϶� 309���� 0�� ������ ����ϴµ� �� ���ܸ� ������ ó���Ͽ���
		int tp = n / e / 10;
		for (int digit = 0; digit < 10; digit++)
			ans[digit] += tp * e;
		e *= 10;
	}

	for (int i : ans)
		cout << i << ' ';

	return 0;
}