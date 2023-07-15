# Problem
* https://algospot.com/judge/problem/read/ROOTS
* 단변수 다항 방정식 해결하기
* 난이도 : 중

# Solution

### 방법 1 : 이분법, 구현
* 접근
  * $f'(x)$의 해가 $f(x)$의 극값이고 $f(x)$의 극값을 알면 어디쯤이 $f(x)=0$인지 쉽게 알 수 있다.

* 풀이
  * $f(lo) < 0$, $f(hi) > 0$ 인 구간 $\( lo, hi \]$에서 $f(x)=0$인 $x$를 찾는다.

* 시간 복잡도 :
  * $O(N^3)$
<br></br>
