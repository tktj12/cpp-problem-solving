#include <iostream>
#include <vector>
#include <map>
using namespace std;

map<int, int> lis_num_position[1000000];
map<int, int> lis;

// lis의 마지막 요소부터 만들면 됨
vector<int> FindLis(int last_idx)
{
    vector<int> ret;
    int n = lis.size();

    for (int i = n - 1; i >= 0; i--) {
        auto iter = --lis_num_position[i].upper_bound(last_idx);
        ret.push_back(iter->second);
        last_idx = iter->first;
    }

    return ret;
}

int main()
{
    cin.tie(nullptr);
    cout.tie(nullptr);
    ios::sync_with_stdio(false);

    int n;
    cin >> n;

    for (int i = 0; i < n; i++) {
        int e;
        cin >> e;
        auto iter = lis.lower_bound(e);
        if (iter == lis.end()) {
            lis_num_position[lis.size()][i] = e;
            lis[e] = lis.size();
        }
        else {
            lis_num_position[iter->second][i] = e;
            if (e < iter->first) {
                lis[e] = iter->second;
                lis.erase(iter);
            }
        }
    }

    vector<int> answer = FindLis(n);
    cout << answer.size() << '\n';
    for (int i = answer.size() - 1; i >= 0; i--)
        cout << answer[i] << ' ';

    return 0;
}