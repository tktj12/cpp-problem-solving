# Problem
* https://www.acmicpc.net/problem/9465
* 규칙에 의해 스티커를 떼서 얻을 수 있는 점수의 최댓값 구하기
* 난이도 : 실버 1

# Solution

### 방법 1 : 동적 계획법
* 풀이
  * $DP(idx, action)$ : $idx$번째 열의 스티커에 $action$행동을 취했을 때 $idx$열~ $n$열까지 얻을 수 있는 
점수의 최댓값 리턴

* 시간 복잡도 :
  * $O(n)$
<br></br>
