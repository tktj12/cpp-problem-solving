# Problem
* https://www.acmicpc.net/problem/10254
* 좌표평면에서 가장 거리가 먼 두 점 구하기
* 난이도 : 플레티넘 2

# Solution

### 방법 1 : 볼록껍질, 회전하는 캘리퍼스
* 풀이
  * 그레이엄 스캔으로 볼록껍질 생성한 후 회전하는 캘리퍼스로 볼록껍질의 지름을 구해서 문제를 해결한다.

* 시간 복잡도 :
  * $O(n\log n)$
<br></br>

# Learning
* long double을 쓴 풀이가 double에 비해 시간이 33% 정도 더 걸렸다.

# Review
* `return` 빼먹음, 줄바꿈, double 출력 등등.. 실수투성이였던 문제풀이