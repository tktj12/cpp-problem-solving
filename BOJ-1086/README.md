# Problem
* https://www.acmicpc.net/problem/1086
* 순열을 합쳐서 만들 수 있는 수 중에 K로 나누어 떨어지는 경우의 비율 구하기
* 난이도 : 플레티넘 5

# Solution
 총 N!개의 경우의 수가 있다.

### 방법 1 : 모듈라 연산, DP
* 풀이
  * 1000을 17로 나눈 나머지는 100을 17로 나눈 나머지에 10을 곱하고, 이 숫자를 17로나눈 나머지와 같다. 
  * 따라서 (최대) 15개의 숫자중에 무엇을 사용했고(bit mask), 현재 나머지가 몇인지를 알면 나올 수 있는 경우의 수가 정해지기 때문에 
  DP를 사용하여 시간 안에 문제를 해결할 수 있다.


* 시간 복잡도 :
  * $O(2^NK)$
<br></br>
