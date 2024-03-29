# Problem
* https://www.acmicpc.net/problem/1006
* 원타곤에 특수소대 최소한으로 배치하기
* 난이도 : 플레티넘 3

# Solution

### 방법 1 : DP
* 풀이
  1. 원타곤은 원형이기 때문에 처음과 끝이 없다. 하지만 임의로 처음과 끝을 정해서 일자로 만든다.
  2. 일자 배열을 생각하고 DP를 한다.
  3. 바로 이전에 한 선택이 현재 선택에 영향을 미친다. 따라서 이전에 한 선택을 숫자로 변환하여 고려한다.
  4. n이 3 이상인 경우 처음과 끝이 같이 커버될 수 있다. 따라서 처음과 끝이 같은 소대에 의해 커버될 모든 경우에 대해 DP를 한다.

* 시간 복잡도 :
  * $O(N)$
<br></br>
