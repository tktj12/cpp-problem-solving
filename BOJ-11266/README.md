# Problem
* https://www.acmicpc.net/problem/11266
* 그래프의 단절점 찾기
* 난이도 : 플레티넘 4

# Solution

### 방법 1 : DFS, 간선 분류
* 풀이
  * DFS를 하면서 단절점을 찾는다.
  * 단절점일 조건
	1. child가 있어야 한다.
	2. 자손중 하나 이상은 본인의 조상으로 가는 역방향 간선이 없어야 한다.
	3. root라면 child가 두 개 이상 있어야 한다.
  * 여기서 root는 DFS를 처음 시작한 노드이고, child는 인접 정점 중에 아직 DFS로 방문되지 않은 노드이다.

* 시간 복잡도 :
  * $O(|V| + |E|)$
<br></br>
