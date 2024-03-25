#include <iostream>
#include <set>
using namespace std;

int main()
{
	int item,big,small;
	cin >> item >> big >> small;
	if (big < small) swap(big,small);

	set<int> remainders;
	int max_remainder = item%small;
	if (max_remainder == 0) {
		cout << item;
		return 0;
	}

	int part_big = item / big;
	while (part_big>0) {
		int remainder = (item - part_big * big) % small;
		if (remainders.find(remainder) != remainders.end())
			break;
		if (remainder == 0) {
			cout << item;
			return 0;
		}

		remainders.insert(remainder);
		max_remainder = max(max_remainder,remainder);
		part_big--;
	}

	int add = min(small - max_remainder,big - item % big);
	cout << item + add;

	
	return 0;
}