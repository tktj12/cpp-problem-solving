# Problem
* https://algospot.com/judge/problem/read/GENIUS
* 서로 다른 재생시간, 다른 확률을 가지고 있는 노래 중 특정 노래가 어느 시점 재생되고 있을 확률 구하기
* 난이도 : 상상상

# Solution
* K의 최댓값이 너무 크기 때문에 재귀 함수를 사용하는 동적 계획법은 할 수 없다.

### 방법 1 : 반복적 동적 계획법
* 풀이
  * $chance(remain, idx, i)$ : 현재 재생되고 있는 곡이 $idx$번 곡일 때 $remain$분 후에 $i$번 곡이 재생되고 있을 확률

* 시간 복잡도 :
  * $O(N^2KM)$
<br></br>

### 방법 2 : 반복적 동적 계획법
* 풀이
  * $start(time, song)$ : 재생을 시작한지 $time$분 후에 $song$번 노래가 재생을 시작할 확률
  * $prev$ : $song$ 전에 재생된 곡, $L(i)$ : 노래 $i$의 재생시간.
  * $start(time, song) = $

$$\sum_{prev} start(time-L(prev), prev)$$


* 시간 복잡도 :
  * $O(N^2K)$
<br></br>

### 방법 3 : 분할 정복, 행렬 거듭제곱
* K값이 너무 크기 때문에 K에 크게 영향을 받지 않는 알고리즘을 사용해야 한다.
* 풀이
  * 방법 2에서 정의한 $start$함수는 이전 값들의 선형 결합으로 만들어진다.
  * 그러므로 $C_{time}$을 다음과 같이 정의하면 확률 $T$를 이용해 $C_{time+1} = W*C_{time}$를 만족하는 가중치 행렬 $W$ 또한 계산할 수 있다.

$$\begin{bmatrix} start(time-3, 0) \\ 
\vdots \\ 
start(time-3, n-1) \\ 
start(time-2, 0) \\ 
\vdots \\ 
start(time-2, n-1) \\ 
start(time-1, 0) \\ 
\vdots \\ 
start(time-1, n-1) \\ 
start(time, 0) \\ 
\vdots \\ 
start(time, n-1) \end{bmatrix}$$

  * 따라서 $C_K = W^K * C_0$
  * 분할 정복을 사용한 빠른 거듭제곱을 통해 더 빠른 시간에 문제를 해결할 수 있다.

* 시간 복잡도 :
  * $O((NL)^3 \log K)$
<br></br>

