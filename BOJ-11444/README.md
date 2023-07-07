# Problem
* https://www.acmicpc.net/problem/11444
* n��° �Ǻ���ġ �� ���ϱ�
* ���̵� : ��

# Solution

### ��� 1 : ���� ����
* Ǯ��
  * $$C_i =  \begin{pmatrix} fib(i-1) \\ fib(i) \end{pmatrix}$$   
��� �� �� �Ʒ� ���� �����Ѵ�   
$$C_{i+1} = \begin{Bmatrix} fib(i) \\ fib(i+1) \end{Bmatrix} = \begin{Bmatrix} fib(i) \\ fib(i-1) & fib(i)\end{Bmatrix} = \begin{Bmatrix} C_{i,1} \\ C_{i,0} & C_{i,1}\end{Bmatrix} = \begin{Bmatrix} C_{i,1} \\ C_{i,0} & C_{i,1}\end{Bmatrix} = \begin{Bmatrix} 0 & 1 \\ 1 & 1\end{Bmatrix} C_i $$   
���� �Ʒ��� �����Ѵ�.   
$$&\begin{Bmatrix} 0 & 1 \\ 1 & 1 \end{Bmatrix} = W$$   
$C_n=W*C_{n-1}=W*W*C_{n-2}=...=W^{n-1}*C_1$   
$$C_n= \begin{Bmatrix} fib(n-1) \\ fib(n) \end{Bmatrix} = W^{n-1}*C_1 = W^{n-1} * \begin{Bmatrix} 0 \\ 1 \end{Bmatrix} = \begin{Bmatrix} W^{n-1}_{0,1} \\ W^{n-1}_{1,1} \end{Bmatrix}$$   
$fib(n) = W^{n-1}_{1,1}$
  * ���� $W^{n-1}$�� ���� ���� ������ ����� ���� ��İ��� ����� �� �ִ�.

* �ð� ���⵵ :
  * $O(\log_{n})$
<br></br>
