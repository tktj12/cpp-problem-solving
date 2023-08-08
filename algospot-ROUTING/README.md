# Problem
* https://algospot.com/judge/problem/read/ROUTING
* 1 이상의 실수 가중치가 있는 네트워크에서 가중치의 곱이 최소가 되는 경로 찾기
* 난이도 : 하

# Solution

### 방법 1 : 다익스트라 최단경로 알고리즘 (dijkstra)
* 풀이
  * 우선순위 큐와 인접리스트로 표현한 양방향 그래프로 다익스트라 알고리즘을 구현하여 문제를 해결

* 시간 복잡도 :
  * $O(|E|\log |V|)$
<br></br>
