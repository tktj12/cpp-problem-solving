# Problem
* https://www.acmicpc.net/problem/16946
* NxM 맵에서 어떤 벽을 기준으로 벽을 부수고 이동할 수 있는 칸의 개수를 모든 벽마다 세기
* 난이도 : 골드 2

# Solution

### 방법 1 : DFS
* 풀이
  * 인접해있는 0들을 하나의 그룹으로 묶어서 각 그룹별로 크기를 잰다.
  * 벽 별로 인접해있는 그룹을 확인하여 이동할 수 있는 칸을 센다.

* 시간 복잡도 :
  * $O(N*M)$
<br></br>

# Learning
* `<algorithm>` 헤더 파일의 unique 함수는 정렬돼있는 배열에만 정상 동작한다.