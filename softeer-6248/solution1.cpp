#include<iostream>
#include<vector>
#include<cstring>
using namespace std;

vector<vector<int>> adj;
bool visited[100010],commute[100010],returning[100010];
bool Update(int here,bool is_reachable[]) {
    visited[here] = true;
    bool ret = false;
    for (int i = 0; i < adj[here].size(); i++) {
        int there = adj[here][i];
        if (!visited[there])
            if (Update(there,is_reachable)) ret = true;
        if (is_reachable[there] && !is_reachable[here]) {
            is_reachable[here] = true;
            ret = true;
        }
    }

    return ret;
}

int main(int argc,char** argv)
{
    int n,m;
    cin >> n >> m;
    adj = vector<vector<int>>(n + 1);
    while (m--) {
        int u,v;
        cin >> u >> v;
        adj[u].push_back(v);
    }

    int home,company;
    cin >> home >> company;
    visited[company] = commute[company] = true;
    while (Update(home,commute)) {
        memset(visited,0,sizeof(visited));
        visited[company] = true;
    }

    memset(visited,0,sizeof(visited));
    visited[home] = returning[home] = true;
    while (Update(company,returning)) {
        memset(visited,0,sizeof(visited));
        visited[home] = true;
    }

    int ans = 0;
    for (int i = 1; i <= n; i++)
        if (commute[i] && returning[i]) ans++;
    cout << ans - 2;
    return 0;
}