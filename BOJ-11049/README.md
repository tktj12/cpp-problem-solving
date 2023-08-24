# Problem
* https://www.acmicpc.net/problem/11049
* 최소한의 연산 횟수로 행렬곱하기
* 난이도 : 골드 3

# Solution

### 방법 1 : 동적 계획법
* 풀이
  * $i$번째 행렬부터 $j(> i)$번째 행렬까지의 곱을 하기 위한 최소 연산을 $DP[i][j]$라고 하자.
  $DP[i][j] = min_{i \le p < j} (DP[i][p] + DP[p+1][j] + M_{i, r}*M_{p, c}*M_{j, c} )$ 이다. 
  여기서 $M_i$는 $i번째$ 행렬이고 $r$은 행, $c$는 열이다.

* 시간 복잡도 :
  * $O(N^3)$
<br></br>
