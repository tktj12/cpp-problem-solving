# Problem
* https://www.acmicpc.net/problem/12100
* 2048 게임의 한 상태에서 5번 더 진행해서 얻을 수 있는 최대 점수 구하기
* 난이도 : 골드 2

# Solution

### 방법 1 : 브루트포스, 구현
* 풀이
  * 한 상태에서 갈 수 있는 다음 상태는 최대 4가지이다.
  * 브루트포스로 5번 했을 때 갈 수 있는 모든 상태를 살펴본다.

* 시간 복잡도 :
  * $O(4^5N^2)$
<br></br>
