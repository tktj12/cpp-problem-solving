# Problem
* https://www.acmicpc.net/problem/13275
* 부분 문자열 중 가장 긴 팰린드롬 문자열 찾기
* 난이도 : 플레티넘 5

# Solution

### 방법 1 : Manacher 알고리즘
* 풀이
  * Manacher 알고리즘은 $O(|S|)$시간 안에 팰린드롬인 부분 문자열들을 구할 수 있다.
  * Manacher 알고리즘은 홀수 팰린드롬만 구할 수 있기 때문에 문자열 중간에 '.'을 넣어서 
  원본 문자열의 짝수 팰린드롬도 구할 수 있게 만들었다.

* 시간 복잡도 :
  * $O(|S|)$
<br></br>

# Learning
* Manacher 알고리즘 https://ialy1595.github.io/post/manacher/
