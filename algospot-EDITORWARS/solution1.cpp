#include <iostream>
#include <vector>
using namespace std;

class UnionFind {
public:
	vector<int> parent, rank, adverse, size;
	UnionFind(int n) : parent(n), rank(n, 1), adverse(n, -1), size(n, 1) 
	{
		for (int i = 0; i < n; i++) parent[i] = i;
	}

	int find(int n)
	{
		if (parent[n] == n) return n;
		else return parent[n] = find(parent[n]);
	}

	void mergeRoot(int& u, int& v)
	{
		if (u == v) return;
		if (rank[ u] > rank[ v]) swap( u,  v); // v�� �׻� u �̻���
		parent[ u] =  v;
		size[ v] += size[ u]; // ��Ʈ���� ������ ����
		if (rank[ u] == rank[ v]) rank[ v]++;
	}

	// ������ ��ġ�� rank�� ����� �����
	// ��ġ���� ������ ���� adverse��� false�� ����
	// ������ adverse�� ���� ������
	bool merge(int u, int v)
	{
		int root_u = find(u);
		int root_v = find(v);
		if (root_u == root_v) return true;
		else if (adverse[root_u] != -1 && find(adverse[root_u]) == root_v) return false;

		mergeRoot(root_u, root_v);

		// adverse ���� merge
		if (adverse[root_u] != -1) {
			if (adverse[root_v] != -1) {
				int ad_root_u = find(adverse[root_u]);
				int ad_root_v = find(adverse[root_v]);
				mergeRoot(ad_root_v, ad_root_u);
			}
			else
				adverse[root_v] = adverse[root_u]; // ��Ʈ���� adverse ����
		}
		return true;
	}

	// u, v ������ ������ adverse�� ���
	// ���� ���� ���տ� �����ִٸ� false ���� ����
	// �̹� adverse ������ ���� �ִٸ� adverse ���հ� ����� ������ ������
	// �̹� adverse��� �ƹ� �ϵ� �Ͼ�� ����
	bool dislike(int u, int v)
	{
		int root_u = find(u);
		int root_v = find(v);
		if (root_u == root_v) return false;
		else if (adverse[root_u] != -1 && find(adverse[root_u]) == root_v) return true;

		if (adverse[root_u] != -1) merge(adverse[root_u], root_v);
		else if (adverse[root_v] != -1) merge(adverse[root_v], root_u);

		adverse[root_u] = root_v;
		adverse[root_v] = root_u;

		return true;
	}
};

int main()
{
	cin.tie(nullptr);
	cout.tie(nullptr);
	ios::sync_with_stdio(false);

	int tc;
	cin >> tc;
	while (tc--) {
		int n, q;
		cin >> n >> q;
		UnionFind relation(n);

		bool contradiction = false;
		int occured;
		for (int i = 0; i < q;i++) {
			string state;
			int u, v;
			cin >> state >> u >> v;

			if (contradiction == true) continue;
			if (state == "ACK") {
				if (relation.merge(u, v) == false)
					contradiction = true, occured = i + 1;
			}
			else {
				if (relation.dislike(u, v) == false)
					contradiction = true, occured = i + 1;
			}
		}

		if (contradiction) {
			cout << "CONTRADICTION AT " << occured << '\n';
			continue;
		}

		int max_size = 0;
		vector<bool> check(n, 0);
		for (int i = 0; i < n; i++) {
			int party = relation.find(i);
			if (check[party] == true) continue;
			
			check[party] = true;
			int adverse = relation.adverse[party];
			if (adverse != -1) {
				adverse = relation.find(adverse);
				check[adverse] = true;
				max_size += max(relation.size[party], relation.size[adverse]);
			}
			else
				max_size += relation.size[party];
		}

		cout << "MAX PARTY SIZE IS " << max_size << '\n';
	}
	return 0;
}