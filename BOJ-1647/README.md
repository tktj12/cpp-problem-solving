# Problem
* https://www.acmicpc.net/problem/1647
* 간선의 가중치가 최소가 되게끔 두 컴포넌트 만들기
* 난이도 : 골드 4

# Solution

### 방법 1 : MST, 버킷정렬
* 풀이
  * 모든 정점이 연결되어 있고, 간선의 가중치가 최소인 그래프는 MST 알고리즘으로 찾을 수 있다. 
  여기서 가중치가 가장 큰 간선 하나를 없앰으로 이 문제를 해결할 수 있다.
  * 이 풀이에서 MST는 크루스칼 알고리즘으로 만들었고 정렬은 버킷정렬로 하였다.

* 시간 복잡도 :
  * $O(|E|)$
<br></br>
