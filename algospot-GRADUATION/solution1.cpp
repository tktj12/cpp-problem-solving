#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

int popcnt(int bit) {
	bit = ((bit >> 1) & 0x55555555) + (bit & 0x55555555);
	bit = ((bit >> 2) & 0x33333333) + (bit & 0x33333333);
	bit = ((bit >> 4) & 0x0F0F0F0F) + (bit & 0x0F0F0F0F);
	bit = ((bit >> 8) & 0x00FF00FF) + (bit & 0x00FF00FF);
	bit = ((bit >> 16) & 0x0000FFFF) + (bit & 0x0000FFFF);
	return bit;
}

int cache[10][1 << 12]; // �޸������̼�, DP() ����
int can_take[1 << 12]; // PreProcess() ����
// ���� ��, �����ϴ� ���� ��, ���� �б� ��, �� �б�� �ִ� ���� ���� ��
int major_sz, K, semester_sz, limit; 
// i�� ������ �� ���� ����, i�� �б⿡ ������ ����
int pre_learning[12], open_subject[12];

// learned �� ��Ʈ����ŷ�� ������� ����� ��
// ������ ���� �� �ִ� ������� �̸� ����ؼ� can_take�� ����
void PreProcess()
{
	for (int learned = (1 << 12) - 1; learned>=0; learned--)
		for (int i = 0; i < major_sz; i++)
			if ((learned & 1 << i) == 0 && (learned & pre_learning[i]) == pre_learning[i])
				can_take[learned] |= 1 << i;
}

// ���� �бⰡ semester, ���� ������ learned�� �� �ּҷ� �� �б⸦ �� ���� ���� �����Ѱ�
// ä���� �ϴ� ������ K��, �� �б⿡ �ִ� ���� ���� ������ limit
int Graduate(int semester, int learned)
{
	if (popcnt(learned) >= K) return 0;
	else if (semester == semester_sz) return 987654321;
	
	int& ret = cache[semester][learned];
	if (ret != -1) return ret;
	ret = 987654321;

	// �̹� �б⿡ ��� ����
	int take = can_take[learned] & open_subject[semester];

	// �̹� �б⿡ ���� �� �ִ� ������ ������
	if (take) {
		// �ִ��� ���� ������ ��´� (�׸���)
		if (popcnt(take) <= limit) 
			ret = Graduate(semester + 1, learned | take )+1;
		else {
			// take �߿��� limit�� ����
			for (int select = take; select; select = (select - 1) & take)
				if (popcnt(select) == limit)
					ret = min(ret, Graduate(semester + 1, learned | select)+1);
		}
	}

	// �̹� �б⸦ �н��ϴ� ���� ��
	return ret = min(ret, Graduate(semester + 1, learned));
}

int main()
{
	cin.tie(nullptr);
	cout.tie(nullptr);
	ios::sync_with_stdio(false);

	int tc;
	cin >> tc;
	while (tc--) {
		memset(cache, -1, sizeof(cache));
		memset(can_take, 0, sizeof(can_take));
		cin >> major_sz >> K >> semester_sz >> limit;

		for (int i = 0; i < major_sz; i++) {
			pre_learning[i] = 0;
			int n;
			cin >> n;
			for (int j = 0; j < n; j++) {
				int subject;
				cin >> subject;
				pre_learning[i] |= 1 << subject;
			}
		}
		for (int i = 0; i < semester_sz; i++) {
			open_subject[i] = 0;
			int n;
			cin >> n;
			for (int j = 0; j < n; j++) {
				int subject;
				cin >> subject;
				open_subject[i] |= 1 << subject;
			}
		}

		PreProcess();
		int ans = Graduate(0, 0);
		if (ans <= semester_sz)
			cout << ans << '\n';
		else
			cout << "IMPOSSIBLE\n";
	}
	return 0;
}