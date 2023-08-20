#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Dat {
	int original_index, card_num;
	int score = 0;
};

int main()
{
	cin.tie(nullptr);
	cout.tie(nullptr);
	ios::sync_with_stdio(false);

	int n;
	cin >> n;
	vector<Dat> arr(n);
	vector<Dat*> num_arr(1000001, nullptr);
	for (int i = 0; i < n; i++) {
		cin >> arr[i].card_num;
		arr[i].original_index = i;
		num_arr[arr[i].card_num] = &arr[i];
	}

	for (int i = 0; i < n; i++) {
		int card = arr[i].card_num;
		int now = 2*card;
		for (; now <= 1000000; now+=card)
			if (num_arr[now]) {
				num_arr[now]->score--;
				arr[i].score++;
			}
	}

	for (int i = 0; i < n; i++)
		cout << arr[i].score << ' ';

	return 0;
}