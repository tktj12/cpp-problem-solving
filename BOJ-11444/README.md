# Problem
* https://www.acmicpc.net/problem/11444
* n번째 피보나치 수 구하기
* 난이도 : 상

# Solution

### 방법 1 : 분할 정복
* 풀이

$$fib(i)=fib(i-1)+fib(i-2)$$   

$$C_i=\begin{Bmatrix} fib(i-1) \\ 
fib(i) \end{Bmatrix}$$   

위와 같이 정의할 때 아래 식이 성립한다   

$$C_{i+1} = \begin{Bmatrix} fib(i) \\ 
fib(i+1) \end{Bmatrix} = \begin{Bmatrix} fib(i) \\ 
fib(i-1) + fib(i)\end{Bmatrix} = \begin{Bmatrix} C_{i,1} \\ 
C_{i,0} + C_{i,1}\end{Bmatrix} = \begin{Bmatrix} 0 & 1 \\ 
1 & 1\end{Bmatrix} C_i $$   

&nbsp;   
따라서 아래가 성립한다.   


$$\begin{Bmatrix} 0 & 1 \\ 
1 & 1 \end{Bmatrix} = W$$   

$$C_n=W* C_{n-1}=W* W*C_{n-2}=...=W^{n-1}*C_1$$

$$= W^{n-1} *\begin{Bmatrix} 0 \\ 
1 \end{Bmatrix} = \begin{Bmatrix} W^{n-1}_ {1,0} \\ 
W^{n-1}_{1,1} \end{Bmatrix} = \begin{Bmatrix} fib(n-1) \\ 
fib(n) \end{Bmatrix}$$   

&nbsp;   
$$\therefore fib(n) = W^{n-1}_{1,1}$$
&nbsp;   
분할 정복을 사용한 빠른 행렬곱을 구현하여 $W^{n-1}$를 구한다.

* 시간 복잡도 :
  * $O(\log n)$
<br></br>

참고 : 구종만, 『프로그래밍 대회에서 배우는 알고리즘 문제해결 전략』 (서울:인사이트, 2012), 351-353
