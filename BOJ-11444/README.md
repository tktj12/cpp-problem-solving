# Problem
* https://www.acmicpc.net/problem/11444
* n번째 피보나치 수 구하기
* 난이도 : 상

# Solution

### 방법 1 : 분할 정복
* 풀이
  * $$C_i =  \begin{pmatrix} fib(i-1) \\ fib(i) \end{pmatrix}$$   
라고 할 때 아래 식이 성립한다   
$$C_{i+1} = \begin{Bmatrix} fib(i) \\ fib(i+1) \end{Bmatrix} = \begin{Bmatrix} fib(i) \\ fib(i-1) & fib(i)\end{Bmatrix} = \begin{Bmatrix} C_{i,1} \\ C_{i,0} & C_{i,1}\end{Bmatrix} = \begin{Bmatrix} C_{i,1} \\ C_{i,0} & C_{i,1}\end{Bmatrix} = \begin{Bmatrix} 0 & 1 \\ 1 & 1\end{Bmatrix} C_i $$   
따라서 아래가 성립한다.   
$$&\begin{Bmatrix} 0 & 1 \\ 1 & 1 \end{Bmatrix} = W$$   
$C_n=W*C_{n-1}=W*W*C_{n-2}=...=W^{n-1}*C_1$   
$$C_n= \begin{Bmatrix} fib(n-1) \\ fib(n) \end{Bmatrix} = W^{n-1}*C_1 = W^{n-1} * \begin{Bmatrix} 0 \\ 1 \end{Bmatrix} = \begin{Bmatrix} W^{n-1}_{0,1} \\ W^{n-1}_{1,1} \end{Bmatrix}$$   
$fib(n) = W^{n-1}_{1,1}$
  * 따라서 $W^{n-1}$에 대해 분할 정복을 사용한 빠른 행렬곱을 사용할 수 있다.

* 시간 복잡도 :
  * $O(\log_{n})$
<br></br>
