# Problem
* https://algospot.com/judge/problem/read/PALINDROMIZE
* 가장 짧은 팰린드롬 만들기
* 난이도 : 중

# Solution

### 방법 1 : KMP 알고리즘
* 풀이
  * 입력 문자열 $s$를 뒤집어 문자열 $f$를 만들고, $s$와 $f$를 비교하며
가장 많이 겹치는 부분의 길이를 찾는다.
  * 이때 KMP 알고리즘으로 $O(n)$시간 안에 탐색한다.

* 시간 복잡도 :
  * $O(n)$
<br></br>
