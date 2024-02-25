# Problem
* https://www.acmicpc.net/problem/9250
* 어떤 문자열의 부분 문자열 중에 문자열 집합 S의 원소와 하나라도 일치하는 게 있는지 구하기
* 난이도 : 플레티넘 2

# Solution

### 방법 1 : Aho-Corasick
* 풀이
  * Aho-Corasick 기본 문제

* 시간 복잡도 :
  * $O(NL + QL)$
  * $NL$ : $N \times 문자열$의 길이 
  * $QL$ : $Q \times 문자열$의 길이 
<br></br>
