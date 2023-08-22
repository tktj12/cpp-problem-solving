# Problem
* https://www.acmicpc.net/problem/16229
* 문자열 S에 k개의 문자를 더해서 반복 패턴으로만 구성된 문자열 만들기
* 난이도 : 플레티넘 4

# Solution

### 방법 1 : Z 알고리즘
* 풀이
  * $k < n$ 이라면 패턴의 길이 $pattern$의 최댓값은 $int((k+n)/2)$이다. 
  따라서 가장 큰 $pattern$부터, $S$의 접두사 $S[..pattern]$(이)가 반복되는지 확인한다. 
  * $Z$ 알고리즘으로 $Z$배열을 만들면 이를 쉽게 확인할 수 있다.

* 시간 복잡도 :
  * $O(N)$
<br></br>
