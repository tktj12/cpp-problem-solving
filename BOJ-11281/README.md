# Problem
* https://www.acmicpc.net/problem/11281
* 2-SAT 기본 문제
* 난이도 : 플레티넘 3

# Solution

### 방법 1 : 2-SAT
* 풀이
  * 주어진 2-CNF 식을 방향 그래프로 만들고 DFS로 SCC를 확인하여 명제 X와 !X가 같은 SCC에 있는지 확인한다.
  * 하나의 절이 $A || B$ 일 때 두 간선 $!A => B$, $!B => A$ 을 만들 수 있다.
  * SCC로 묶은 그래프를 위상 정렬하여 왼쪽 노드부터 거짓으로 정하면 식$f$를 참으로 만드는 논리값을 알 수 있다.

* 시간 복잡도 :
  * $O(N+M)$
<br></br>
