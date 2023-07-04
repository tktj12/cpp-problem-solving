# Problem
* https://algospot.com/judge/problem/read/DRAGON
* 규칙을 갖고 늘어나는 문자열의 p~(p+l)번째 문자 구하기
* 난이도 : 

# Solution

### 방법 1 : 문제 그대로 코딩
* 풀이
  * $MakeString(string)$ 함수는 입력으로 받은 $string$ 문자열에서 모든 X, Y를 찾아 규칙에 맞게 변환하여 반환한다.

* 시간 복잡도 :
  * $O(2^N)$
<br></br>

### 방법 2 : 숨겨진 규칙을 찾아서 풀이
* 풀이
  * 아래에 구한 규칙을 토대로 계산
  * $n$세대의 문자열 $G_n = G_{n-1}+G_{n-2}-G_{n-3}-...-G_1-G_0-YF$, $G_0=XF$
  * $n$세대의 문자열 갯수 $C_n = 2^{n-1}*3+C_{n-1}$, $C_0 = 2$

* 시간 복잡도 :
  * $O(n)$
<br></br>

# Learning
* `iterator +1 -3 +2`와 `iterator +(1-3+2)` 연산이 다르다 전자의 경우   
iterator +1 => iterator -3 => iterator +2 순으로 연산되어 +1 순간에 end를 넘어가거나 -3 순간에 begin을 넘어갈 수 있다.
따라서 후자가 더 안전하고 올바른 방법이다.
