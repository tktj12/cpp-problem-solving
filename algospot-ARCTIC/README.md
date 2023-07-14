# Problem
* https://algospot.com/judge/problem/read/ARCTIC
* 모든 기지가 소통할 수 있는 최소한의 통신 거리 구하기
* 난이도 : 하

# Solution

### 방법 1 : 
* 풀이
  * 기지 간의 모든 거리를 미리 구해 놓는다.
  * 결정 문제로 바꾸어서 이분탐색으로 최소한의 출력을 찾는다.
  * BFS 방식으로 모든 기지에 연락이 닿는지 확인한다.

* 시간 복잡도 :
  * $O(N^2)$
<br></br>
