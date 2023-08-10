# Problem
* https://algospot.com/judge/problem/read/LAN
* 좌표평면에 건물들과 이미 설치된 케이블들이 있을 때, 모든 건물을 잇기 위해 최소한으로 더 케이블을 설치하는 방법 찾기
* 난이도 : 중

# Solution

### 방법 1 : Kruskal의 MST 알고리즘
* 풀이
  * 이미 연결되있는 건물들의 집합을 UnionFind 자료구조로 확인하고 연결되어있지 않은 건물들을 이을 수 있는 
  거리 중 가장 짧은 것부터 연결하여 최소한으로 모든 건물을 연결한다.

* 시간 복잡도 :
  * $O(|E|\log |E|)$
<br></br>
