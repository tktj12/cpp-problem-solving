# Problem
* https://algospot.com/judge/problem/read/BLOCKGAME
* 조합 게임에서 이기는 경우가 있는지 구하기
* 난이도 : 상

# Solution

### 방법 1 : 동적 계획법
* 풀이
  * 게임판의 한 좌표의 상태를 0 또는 1로 생각. 채워져 있으면 1, 비어있으면 0으로 생각한다.

* 시간 복잡도 :
  * $O(n2^n)$ , $n$ : 칸의 수

* 함수 구현이 복잡해서 시간 초과
<br></br>

### 방법 2 : 동적 계획법
* 풀이
  * 1번 방법에서 더 나아가서 놓을 수 있는 블록을 확인하는 걸 비트 곱으로 확인한다.
   
* 시간 복잡도 :
  * $O(n2^n)$ , $n$ : 칸의 수
<br></br>
