# Problem
* https://www.acmicpc.net/problem/7579
* 최소한의 비용으로 앱을 종료해서 메모리 확보하기
* 난이도 : 골드 3

# Solution

### 방법 1 : 동적 계획법
* 풀이
  * $DP(app, cost)$ : $app$번째 앱까지 확인했을 때 $cost$의 비용으로 얻을 수 있는 최대의 메모리

* 시간 복잡도 :
  * $O(N^2C)$, $N$ : 앱의 개수, $C$ : cost의 범위
<br></br>

# Learning
* 풀이 https://cocoon1787.tistory.com/319