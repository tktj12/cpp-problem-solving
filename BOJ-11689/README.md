# Problem
* https://www.acmicpc.net/problem/11689
* n과 서로소인 k의 개수 구하기
* 난이도 : 골드 1

# Solution

### 방법 1 : 오일러 피(phi) 함수, 정수론, 소수
* 풀이
  * 오일러 피 함수 $\varphi (n)$의 값은 $gcd(n,k) = 1$인 $n$이하의 $k$의 개수이다. 즉 이 문제의 답과 동일하다.
  * 오일러 피 함수의 성질을 활용하여 문제를 푼다. 즉 "$\varphi (p^k) = p^k - p^{k-1}$, $p$는 소수"인 것을 
  이용한다.

* 시간 복잡도 :
  * $O(\sqrt{n})$
<br></br>

# Learning
* 오일러 피 함수
* https://namu.wiki/w/%EC%98%A4%EC%9D%BC%EB%9F%AC%20%ED%94%BC%20%ED%95%A8%EC%88%98?from=%EC%98%A4%EC%9D%BC%EB%9F%AC%20%ED%8C%8C%EC%9D%B4%20%ED%95%A8%EC%88%98
* https://ko.wikipedia.org/wiki/%EC%98%A4%EC%9D%BC%EB%9F%AC_%ED%94%BC_%ED%95%A8%EC%88%98
<br></br>

# Review
* 왜째서 이런 함수가 있는가..