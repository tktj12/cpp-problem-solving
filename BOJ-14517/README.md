# Problem
* https://www.acmicpc.net/problem/14517
* 팰린드롬이 되는 부분수열의 개수 구하기
* 난이도 : 플레티넘 5

# Solution

### 방법 1 : DP (시간 초과)
* 풀이
  * $Search(be gin, end)$ : $[be gin, end]$ 구간에서 만들 수 있는 팰린드롬 부분수열의 개수 반환.
  * 시간초과 : $Search$ 함수 안에 있는 이중  for문 안에 또 $Search$함수가 있는 비효율적인 구조.

* 시간 복잡도 :
  * $O(N^4)$
<br></br>

### 방법 2 : DP, 포함 배제의 원리
* 풀이

$$DP(be gin, end)=
\begin{cases}
0, & \mbox{if }begin > end \\
1, & \mbox{if }begin == end \\
DP(be gin, end-1)+DP(be gin+1,end), & \mbox{if }S[begin] == S[end] \\
DP(be gin, end-1)+DP(be gin+1,end)-DP(be gin+1,end-1), & \mbox{else}
\end{cases}$$

* 시간 복잡도 :
  * $O(N^2)$
<br></br>
