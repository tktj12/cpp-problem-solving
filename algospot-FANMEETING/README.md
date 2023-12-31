# Problem
* https://algospot.com/judge/problem/read/FANMEETING
* 모든 멤버가 포옹을 하는 경우의 수
* 난이도 : 상

# Solution
* 입력이 최대 200000 이므로 $N^2$ 미만의 알고리즘을 사용해야 한다.
* 완전 탐색을 할 경우 수행 시간이 100억 정도 나온다.

### 방법 1 : 분할 정복, 카라츠바(karatsuba) 알고리즘 (출처 : 『알고리즘 문제해결 전략』)
* 풀이
  * $n$자리수의 숫자 $A$의 각 자릿수를 $A_1,A_2,...,A_n$ 라고 하자.   
매우 큰 수 $A, B$에 대해 $A \times B=C$를 계산하는 과정 중에서 각 자리 별 덧셈을 전부 마치고 C의 일의 자리부터 자리올림을 해야한다.   
그런데 자리 올림을 하기 전에
$C$의 $i$번째 자리는 $C_i = A_1 \times B_i + A_2 \times B_{i-1} + ... + A_n \times B_{i-n}$ 의 형태를 갖게 되는데   
$A$의 자릿수는 오름차순이고 $B$의 자릿수는 내림차순인 걸 알 수 있다.   
이때 $A$의 자릿수도 내림차순으로 맞춰주기 위해서는 $A$를 좌우 반전시키면 된다.   
이 아이디어를 사용하여 문제를 해결한다. 또한 카라츠바 알고리즘을 사용하여 더 빠른 곱셈을 한다.

* 시간 복잡도 :
  * $O(N^{\lg 3})$
<br></br>

### 방법 2 : bit 연산
* 풀이
  * 입력에 대해 M은 1, F는 0으로 생각할 수 있다.
  * 입력을 bit로 바꾸고 모든 경우에 대해 bit곱 연산을 수행하여 경우의 수를 계산한다.

* 시간 복잡도 :
  * $O(( \frac{N}{64} )^2) = O(N^2)$

* 코드가 더 간단하고 시간 복잡도는 $O(N^2)$이지만 이 문제 N의 범위에선 분모 $64^2$이 무시할 수 없는 정도여서 시간도 더 적게 든다.
<br></br>

### 방법 3 : bit 연산, shift 미리 계산
* bit 연산을 하는 건 2번 방법과 같다. 그런데 2번에서 더 나아가서   
  shift 연산을 미리 해서 전체적인 속도를 증가시킬 수 있었다.   

* 풀이
  * 멤버의 원본 데이터에서 시프트를 0번 한 것부터 63번 한 것까지 미리 계산해놓는다.   
    이러면 비트곱을 수행할 때 순서대로 계산해주면 논리상 문제가 없다.
  * 그리고 unsigned long long 이 64비트 이므로 멤버 비트를 64번 시프트 할 때 마다 비트곱 되어지는 팬 비트의 시작 인덱스를 옮겨준다.

* 시간 복잡도 :
  * $O(( \frac{N}{64} )^2) = O(N^2)$
<br></br>

# Learning
* 이 문제를 곱셈의 원리로 풀 수 있다는 것은 바로 이해했다.
그런데 카라츠바 알고리즘은 일반적인 곱셈과는 과정이 달라서 예외가 발생하지 않는지가 의문이었다.
특히 과정 중에 빼기를 하는데, 이때 특정 자리에서 음수가 나오는 게 아닌가 하는 생각이 들었다.
하지만 $(a_0+a_1)(b_0+b_1) - (a_0b_0+a_1b_1)$ 이 식을 자세히 들여다 보면
$(a_0+a_1)(b_0+b_1)$의 어느 자리에서건 $(a_0 b_0+a_1 b_1)$ 보다 작을 수 없다는 걸 알 수 있다.

* 첫 번째 자리만 생각해 보자 
  * $(a_{0_0}+a_{1_0})(b_{0_0}+b_{1_0}) - a_{0_0} * b_{0_0} - a_{1_0} * b_{1_0}$   
    $= a_{0_0} * b_{1_0} + a_{1_0} * b_{0_0}$
  * 입력으로 음수를 받지 않는다. 따라서 $(a_{0_0}$ , $b_{1_0}$ , $a_{1_0}$ , $b_{0_0}) \ge 0$ 이므로 음수가 나올 수 없다.

* 카라츠바 알고리즘에서 $N^2$ 곱셈 알고리즘을 쓰는 threshold는 100 정도가 적당하다.
