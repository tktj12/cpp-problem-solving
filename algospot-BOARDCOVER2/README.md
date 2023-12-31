# Problem
* https://algospot.com/judge/problem/read/BOARDCOVER2
* 게임판에 최대한 많은 블럭 채우기
* 난이도 : 중

# Solution

### 방법 1 : 완전 탐색
* 풀이
  * 블록을 놓을 수 있는 모든 경우의 수를 일일이 탐색

* 시간 복잡도 :
  * $O(4^{n}m)$, $n$ : 게임판의 크기, $m$ : 블록 크기
<br></br>

### 방법 2 : 완전 탐색, 가지치기 (종만북 풀이)
* 풀이
  * 낙관적인 휴리스틱으로 가지치기. 게임판의 남은 빈칸의 수를 고려하여 블록을 최대한 놓아도 현재까지의
best보다 낮을 경우 탐색을 중단함

* 시간 복잡도 :
  * $O(4^{n}m)$, $n$ : 게임판의 크기, $m$ : 블록 크기
<br></br>

# Learning
* `<algorithm>`헤더 파일의 `unique(begin, end)` 함수는 정렬된 배열의 중복 원소들을 배열의 뒤쪽으로 보내고,
중복이 없는 마지막 원소의 다음 포인터(중복 원소들의 첫 포인터)를 반환한다. 배열이 정렬돼있지 않다면 
올바른 실행이 보장되지 않는다.
