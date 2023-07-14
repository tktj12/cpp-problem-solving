# Problem
* https://algospot.com/judge/problem/read/CANADATRIP
* K번째 표지판의 위치
* 난이도 : 중

# Solution

### 방법 1 : 최적화 문제 -> 결정 문제, 이분 탐색
* 풀이
  * $decision(dist, val)$ : $dist$까지 마주친 표지판 개수가 $val$ 보다 작은지 판별
  * $solve(k)$ : $k$ 번째 표지판의 거리를 구함

* 시간 복잡도 :
  * $O(n\log m)$, $n$ : 도시 수, $m$ : 도로 길이
<br></br>
