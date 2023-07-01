# Problem
* https://algospot.com/judge/problem/read/POLY
* 세로 단조인 N 폴리오미노의 개수
* 난이도 : 중

# Solution

### 방법 1 : 동적 계획법
* 풀이
  * 세로 단조인 점을 생각하면, 바로 위쪽 줄에 블럭이 몇 개 있는지와 남은 블럭이 몇 개 있는지에 따라 
아래쪽 블럭의 경우의 수가 결정된다.
  * 이것을 토대로 $DP(upstair$ $blocks, remainder)$ 함수를 구현한다.

* 시간 복잡도 :
  * $O(N^3)$
