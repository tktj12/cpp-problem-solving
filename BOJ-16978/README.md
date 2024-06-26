# Problem
* https://www.acmicpc.net/problem/16978
* 값이 중간에 바뀌는 수열에서 k번째 바뀐 수열에서 구간 쿼리하기
* 난이도 : 플레티넘 4

# Solution

### 방법 1 : Segment Tree, 오프라인 쿼리
* 풀이
  1. 2번 연산을 $k$값에 따라 정렬한다. 이때 2번 연산이 나타난 순서 또한 기억한다.
  2. 정렬한 순서대로 구간 쿼리를 한다. k값에 맞춰 수열을 변경하고 구간 쿼리를 구한다.
  3. 1번에서 2번 연산이 나타난 순서를 기억했으므로, 그 순서에 맞춰 출력한다.

* 시간 복잡도 :
  * $O(N\log N + M\log M)$
<br></br>
