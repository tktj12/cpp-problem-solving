# Problem
* https://algospot.com/judge/problem/read/WILDCARD
* 패턴에 일치하는 문자열 찾기
* 난이도 : 중

# Solution

### 방법 1 : 무작정 풀기
* 풀이
  * 순수 직관적으로 가능한 모든 경우의 수를 if문을 사용해서 구현
  * 주의할 점은 커서가 마지막으로 만난 '*' 다음으로 돌아갈 때 $i$도 적절하게 값을 바꿔줘야 한다.

* 시간 복잡도 :
  * $N$ : 문자열 길이
  * $O(N^2)$
<br></br>
