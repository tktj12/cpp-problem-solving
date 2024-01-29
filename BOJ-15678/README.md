# Problem
* https://www.acmicpc.net/problem/15678
* 밟은 징검다리의 점수의 합 최대로 구하기
* 난이도 : 플레티넘 5

# Solution
### 분석
* N개의 시작점, 최대 이동거리 D
* 왔다 갔다 할 필요가 없다 == 방향을 바꿀 필요가 없다
* 갈 수 있는 곳 중 0이상이 있다면 가장 가까운 걸 밟으면 된다.

### 방법 1 : DP, Segment Tree
* 재귀식 :   

$$DP(pos)=
\begin{cases}
score[pos]+max_{1\le i \le D} (DP(pos-i)), & \mbox{if } max_{1\le i \le D} (DP(pos-i)) > 0 \\
score[pos], & \mbox{else}
\end{cases}$$

* 풀이 :
  * 
  
* Time Complexity :   
$O(N\log N)$
<br></br>
