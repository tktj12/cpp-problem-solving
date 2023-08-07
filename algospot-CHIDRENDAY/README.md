# Problem
* https://algospot.com/judge/problem/read/CHILDRENDAY
* M명의 욕심쟁이가 껴있는 N명의 아이들이 모두 만족하게 장난감 사주기
* 난이도 : 상

# Solution

### 방법 1 : BFS
* 풀이
  * $C \mod N = M, (C \ge N)$ 이어야 모든 조건을 만족할 수 있다.
  * 세 정수 $a,b,c (a \ge 0, b > 0, c \ge 0)$에 대해 다음 식이 성립한다.   
$( (a \mod b) * 10 + c ) \mod b = (10*a + c) \mod b$   
  * $N$으로 나눈 나머지를 정점으로 하는 암시적 그래프를 이용하여 문제를 해결한다.


* 시간 복잡도 :
  * $O(N*|d|)$
<br></br>
