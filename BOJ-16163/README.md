# Problem
* https://www.acmicpc.net/problem/16163
* 부분 문자열 중 회문인 것의 개수 구하기
* 난이도 : 플레티넘 5

# Solution

### 방법 1 : Manacher 알고리즘
* 풀이
  * 회문인 문자열이 있을 때, 양 끝의 문자를 지우면 또 다른 회문 문자열이다.
  * Manacher 알고리즘으로 홀수, 짝수 회문을 모두 구한다. Manacher는 $i$를 중심으로 하는 회문의 최대 길이를 
  구한다. 이를 이용해 적절히 답을 구한다.

* 시간 복잡도 :
  * $O(|S|)$
<br></br>
