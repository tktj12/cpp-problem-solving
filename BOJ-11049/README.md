# Problem
* https://www.acmicpc.net/problem/11049
* 최소한의 연산 횟수로 행렬곱하기
* 난이도 : 골드 3

# Solution

### 방법 1 : 동적 계획법
* 풀이
  * $i$번째 행렬부터 $j(\ge i)$번째 행렬까지의 곱을 하기 위한 최소 연산을 $DP[i][j]$라고 하자.
  $DP[i][j] = min_{i \le p < j} (DP[i][p] + DP[p+1][j] + M_{i, r}*M_{p, c}*M_{j, c} )$ 이다. 
  여기서 $M_i$는 $i$번째 행렬이고 $r$은 행, $c$는 열이다.

* 시간 복잡도 :
  * $O(N^3)$
<br></br>

### 방법 2 : 동적 계획법
* 풀이
  * 재귀 함수가 아닌 반복문으로 구현

* 시간 복잡도 :
  * $O(N^3)$
<br></br>

# Learning
* 이 문제를 $O(N\log N)$ 시간에 푸는 루비 1 난이도의 Hu-Shing 알고리즘이 있다.
* https://singun11.tistory.com/107
* https://en.wikipedia.org/wiki/Matrix_chain_multiplication