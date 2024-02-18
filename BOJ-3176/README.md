# Problem
* https://www.acmicpc.net/problem/3176
* 경로 상의 도로 중에서 가장 짧은 것과 가장 긴 것 구하기
* 난이도 : 플레티넘 4

# Solution

### 방법 1 : 그래프, 트리, LCA
* 풀이
  * DP, 희소배열로 LCA table을 만들 때 자신의 조상까지 가는 경로 상의 최대 길이 도로와 최소 길이 도로 또한 계산한다.
  * LCA table을 만드는 알고리즘을 이용하면 계산을 쉽게 할 수 있다.

* 시간 복잡도 :
  * $O((N+K)\log N)$
<br></br>
