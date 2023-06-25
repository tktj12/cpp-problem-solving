# Problem
* https://algospot.com/judge/problem/read/JUMPGAME
* $n\times n$ 게임판의 왼쪽 위에서 시작해서 오른쪽 아래로 도달할 수 있는지 판단하는 문제
* 난이도 : 하

# Solution

### 방법 1 : 동적 계획법, 재귀호출
* 풀이
  * 갈 수 있는 곳을 모두 재귀호출을 이용하여 탐색한다.
  * 이미 갔던 곳이라면 탐색하지 않는다.

* 시간 복잡도 :
  * $O(N)$
<br></br>

# Learning