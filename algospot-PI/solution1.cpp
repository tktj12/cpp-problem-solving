#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

int CalLowestLevel(int);

const int INF = 0x0FFFFFFF;
int cache[10003];
string numbers;
int main()
{
	cin.tie(nullptr);
	cout.tie(nullptr);
	ios::sync_with_stdio(false);

	int tc;
	cin >> tc;
	while (tc--) {
		cin >> numbers;
		memset(cache, -1, sizeof(cache));
		cache[numbers.size()] = 0;
		for (int i = 1; i <= 2; ++i)
			cache[numbers.size()-i] = cache[numbers.size() + i] = INF;

		cout << CalLowestLevel(0) << '\n';
	}
	return 0;
}

int CalLowestLevel(int left)
{
	int& ret = cache[left];
	if (ret > -1) return ret;

	int level(10);
	int dif = numbers[left+1] - numbers[left];
	int dif2 = numbers[left+2] - numbers[left + 1];

	if (dif == dif2) {
		if (dif == 0) level = 1;
		else if (abs(dif) == 1) level = 2;
		else level = 5;
	}
	else if (dif == -dif2) {
		level = 4;
	}
	ret = level + CalLowestLevel(left + 3);

	for (int i = 3; i <= 4; ++i) {
		switch (level) {
		case 1: case 2: case 5:
			if (numbers[left + i] - numbers[left + i - 1] != dif) 
				level = 10;
			break;
		case 4:
			dif = -dif;
			if (numbers[left + i] - numbers[left + i - 1] != -dif) 
				level = 10;
			break;
		}
		ret = min(ret, level + CalLowestLevel(left + i + 1));
	}
	
	return ret;
}