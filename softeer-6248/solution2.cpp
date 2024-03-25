#include<iostream>
#include<vector>
#include<stack>
#include<cstring>
using namespace std;

const int MAXN = 100'010;
vector<vector<int>> scc_group,scc_adj,adj;
int discovered[MAXN],scc[MAXN];
int scc_cnt,discover_ord;
stack<int> scc_st;

int Tarjan(int here) {
    int ret = discovered[here] = discover_ord++;
    scc_st.push(here);
    for (int there : adj[here]) {
        if (discovered[there] == -1)
            ret = min(ret,Tarjan(there));
        else if (scc[there] == -1)
            ret = min(ret,discovered[there]);
    }
    if (ret == discovered[here]) {
        scc_group.push_back({});
        while (true) {
            int t = scc_st.top(); scc_st.pop();
            scc_group[scc_cnt].push_back(t);
            scc[t] = scc_cnt;
            if (t == here)
                break;
        }
        scc_cnt++;
    }
    return ret;
}

bool visited[MAXN];
void DFS(int here,bool path[]) {
    visited[here] = true;
    for (int there : scc_adj[here]) {
        if (!visited[there])
            DFS(there,path);
        if (path[there])
            path[here] = true;
    }
}

inline void Condensation(int n,int start,int dest,bool is_way_to_dest[]) {
    memset(discovered,-1,sizeof(discovered));
    memset(scc,-1,sizeof(scc));
    scc_st = stack<int>();
    scc_group = vector<vector<int>>(1);
    scc_adj = vector<vector<int>>(n + 1);
    scc_cnt = discover_ord = 0;
    scc[dest] = scc_cnt;
    discovered[dest] = discover_ord++;
    scc_group[scc_cnt++].push_back(dest);
    Tarjan(start);
    for (int gn = 1; gn < scc_group.size(); gn++)
        for (int i : scc_group[gn])
            for (int there : adj[i])
                scc_adj[gn].push_back(scc[there]);

    memset(visited,0,sizeof(visited));
    bool path[MAXN] = { 0, };
    visited[0] = path[0] = true;
    DFS(scc_cnt - 1,path);
    for (int i = 1; i < scc_cnt; i++)
        if (path[i])
            for (int v : scc_group[i])
                is_way_to_dest[v] = true;
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
    bool is_way_to_work[MAXN] = { 0, };
    Condensation(n,home,company,is_way_to_work);

    bool is_way_to_home[MAXN] = { 0, };
    Condensation(n,company,home,is_way_to_home);

    int ans = 0;
    for (int i = 1; i <= n; i++)
        if (is_way_to_work[i] && is_way_to_home[i]) ans++;
    cout << ans;

    return 0;
}