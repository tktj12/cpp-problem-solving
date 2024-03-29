# Problem
* https://www.acmicpc.net/problem/13907
* 통행료가 오를 때마다 최소 통행료를 내는 경로의 통행료 구하기
* 난이도 : 플레티넘 4

# Solution

### 방법 1 : 다익스트라, Convex Hull Trick
* 풀이
  * 다익스트라 알고리즘으로 $s$부터 $d$로 가는 최단 경로를 구한다.
  * 이 과정에서 몇 개의 도로를 타고 $d$로 도착했는지 또한 계산한다 == $road$
  * 최단 경로가 찾아졌을 때 종료하지 않고 $road$가 줄어드는 경로가 있을 경우 계속 수행한다.
  * 이렇게 하면 $s$에서 $d$로 가는 여러 개의 { $road$, $cost$ }쌍을 구할 수 있다.
  * $road$는 인상되는 세금에 영향을 받고 $cost$는 영향을 받지 않는다. 따라서 $road$를 기울기, $cost$를 y절편으로 두고 CHT로 문제를 해결할 수 있다.

* 시간 복잡도 :
  * $O(M\log M + K\log N)$
<br></br>
