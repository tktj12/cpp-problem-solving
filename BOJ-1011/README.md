# Problem
* https://www.acmicpc.net/problem/1011
* x부터 y까지 규칙에 맞게 가장 빨리 이동하는 경우 구하기
* 난이도 : 골드5

# Solution

### 방법 1 : 이분 탐색
* 풀이
  * 가능한 경우를 생각해봤을 때 우주선의 장치를 최소로 작동하는 이동 거리는   
1 2 3 ... n-1 n n-1 ... 2 1 의 형식으로 만들 수 있다.
  * 이 때 최댓값 $n$, 이동거리 $distance$에 대해 $n^2 \le distance < n^2+2n+1$을 만족한다.
  * 또한 $n^2 = distance$ 일 경우 장치가 $2n-1$번,   
$n^2 < distance \le n^2+n$일 경우 $2n$번,   
$n^2+n < distance \le n^2+2n$일 경우 $2n+1$번 작동한다.

* 시간 복잡도 :
  * $O(\log n)$
<br></br>
