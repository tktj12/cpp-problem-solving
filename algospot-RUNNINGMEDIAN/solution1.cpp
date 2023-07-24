#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

inline int next(long long n, int a, int b) {
	return (n * a + b) % 20090711;
}

const int MAX = 0;
const int MIN = 1;
bool IsHigher(int a, int b, int mode) {
	if (mode == MAX) return a > b;
	else return a < b;
}

void Insert(vector<int>& heap, int n, int mode)
{
	int here = heap.size();
	heap.push_back(n);
	while (here > 1) {
		int parent = here / 2;
		if (IsHigher(heap[parent], heap[here], mode)) break;

		swap(heap[parent], heap[here]);
		here = parent;
	}
}

int Pop(vector<int>& heap, int mode)
{
	int ret = heap[1];
	heap[1] = heap.back();
	heap.erase(heap.end() - 1);

	int size = heap.size();
	if (size == 1) return ret;
	int here = 1;
	while (1) {
		int cand = here;
		int left = here * 2;
		int right = here * 2+1;

		if (left >= size) break;
		if (IsHigher(heap[left], heap[cand], mode))
			cand = left;
		if (right < size && IsHigher(heap[right], heap[cand], mode))
			cand = right;

		if (cand == here) break;
		swap(heap[here], heap[cand]);
		here = cand;
	}
	return ret;
}

int main()
{
	cin.tie(nullptr);
	cout.tie(nullptr);
	ios::sync_with_stdio(false);

	int tc;
	cin >> tc;
	while (tc--) {
		int n, a, b;
		cin >> n >> a >> b;

		vector<int> max_heap(1), min_heap(1);
		int A = 1983;
		int mid = A, sum=A;
		for (int i = 1; i < n; i++) {
			A = next(A, a, b);
			if (A > mid) Insert(min_heap, A, MIN);
			else Insert(max_heap, A, MAX);

			int biggers = min_heap.size();
			int lowers = max_heap.size();

			if (biggers == lowers + 2) {
				Insert(max_heap, mid, MAX);
				mid = Pop(min_heap,MIN);
			}
			else if (biggers + 1 <= lowers) {
				Insert(min_heap, mid, MIN);
				mid = Pop(max_heap, MAX);
			}

			sum = (sum + mid) % 20090711;
		}
		cout << sum << '\n';
	}
	return 0;
}