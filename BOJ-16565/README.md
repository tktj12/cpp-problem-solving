# Problem
* https://www.acmicpc.net/problem/16565
* 트럼프 카드에서 N개의 카드를 뽑았을 때 포카드를 만들 수 있는 확률 구하기
* 난이도 : 골드 2

# Solution
 naive하게는 $_{52}C_N$개의 조합을 살펴야 함.   
$N=4$일 때 $ans_N = 13$,   
$N=5 : ans_N = 13 * _{52-4}C_1$   
$N=6 : ans_N = 13 * _{52-4}C_2$   
$N=7 : ans_N = 13 * _{52-4}C_3$   
$N=8 : ans_N = 13 * _{52-4}C_4 - _{13}C _2$   
$N=9 : ans_N = 13* _{52-4}C_5 - _{13}C_2 * _{52-8}C _1$   
...   
$N = 12 : ans_N = 13* _{52-4}C_8 - _{13}C_2 * _{52-8}C_4 + _{13}C _3$   
...   
$N = 52 : ans_N = _{13}C _1* _{52-4}C _{N-4} - _{13}C_2 * _{52-8}C _{N-8} + ... - ... + ... - ... \ ... + _{13}C _{13} * _{4}C _{N-52}$

### 방법 1 : DP, 수학, 조합론, 포함 배제의 원리
* 풀이
  * $A_i$ : $N$개의 카드 중 $i$의 포카드가 무조건 나오는 모든 조합이라고 할 때,   
  포카드가 한 세트 이상 있는 조합 $T$는 $A_1 \cup A_2 \cup ... \cup A_{13}$ 이다. 
  이때 $T$의 크기 $|T|$는 포함 배제의 원리에 따라 아래와 같이 구할 수 있다.   
  $$|A_1\cup\cdots\cup A_n|=\sum_{i=1}^n|A_i|-\sum_{1\le i< j\le n}|A_i\cap A_j|+\sum_{1\le i < j < k\le n}|A_i\cap A_j\cap A_k|-\cdots+(-1)^{n-1}|A_1\cap\cdots\cap A_n|$$   
  * 따라서 다음과 같이 정답을 구할 수 있다.   
  $$ans_N = \sum_{i=1}^{[N/4]} ((-1)^{i-1} * _{13}C_i* _{52 - 4i}C _{N - 4i})$$
  

* 시간 복잡도 :
  * $O(N^2)$
<br></br>

# Learning
* 포함 배제의 원리 https://ko.wikipedia.org/wiki/%ED%8F%AC%ED%95%A8%EB%B0%B0%EC%A0%9C%EC%9D%98_%EC%9B%90%EB%A6%AC

# Review
* 처음에 포함 배제의 원리를 모르고 N=12까지만 보고 대충 짐작해서 풀었다