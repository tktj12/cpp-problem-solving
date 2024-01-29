# Problem
* https://www.acmicpc.net/problem/15678
* 밟은 징검다리의 점수의 합 최대로 구하기
* 난이도 : 플레티넘 5

# Solution
### 분석
* N개의 시작점, 최대 이동거리 D
* 진행 방향을 바꿀 필요가 없다
* 갔을 때 결과적으로 이득인 곳이 여러 개 있다면 가장 가까운 걸 밟으면 된다.

### 방법 1 : DP, Segment Tree
* 재귀식 :
  * $DP[pos]$ : $pos$에서 시작하여 한 방향(이 코드는 N번에서 1번으로 가는 방향)으로 게임을 진행했을 때 얻을 수 있는 최대 점수
<br></br>

$$DP[pos]=
\begin{cases}
score[pos]+max_{1\le i \le D} (DP[pos-i]), & \mbox{if } max_{1\le i \le D} (DP[pos-i]) > 0 \\
score[pos], & \mbox{else}
\end{cases}$$

* 풀이 :
  
  
* 시간 복잡도 :   
$O(N\log N)$
<br></br>
