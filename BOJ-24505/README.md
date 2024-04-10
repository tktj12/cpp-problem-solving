# Problem
* https://www.acmicpc.net/problem/24505
* 길이가 11인 증가하는 부분수열의 개수 구하기
* 난이도 : 플레티넘 4

# Solution

### 방법 1 : 구간 트리
* 풀이
  * $a_{x,y}$ : 길이가 $x$이고 마지막 원소가 $y$인 증가 수열의 개수
  * $a_{1,y}$는 수열에 $y$가 등장하는 횟수와 같다.
  * $x \ge 2$일 때, $a_{x,y} = \sum a_{x-1, i}$ $(1 \le i < y)$
  * $i$번째 수에 대해 처리하기 전에는 트리 내에 [1, $i$-1]까지의 값밖에 존재하지 않는다. 따라서 $A_i$를 입력받은 순간에 $A_i$보다 작은 값들은 항상 $A_i$보다 왼쪽에 있다.

* 시간 복잡도 :
  * $O(kN\log N)$
  * $N$ : 입력 크기
  * $k$ : 증가하는 부분수열의 길이
<br></br>