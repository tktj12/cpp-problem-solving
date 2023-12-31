# Problem
* https://www.acmicpc.net/problem/15824
* 모든 조합의 최솟값, 최댓값의 차를 더하기
* 난이도 : 골드 2

# Solution

### 방법 1 : 수학, 조합론, 누적합
* 풀이
  * naive하게 생각하면 $O(2^n)$시간에 모든 조합을 만들고 최솟값과 최댓값의 차이를 구하면 된다.   
  여기서 조금만 더 생각하면, 최솟값과 최댓값을 고정시키고 가능한 모든 조합의 개수를 셀 수 있다. 
  * 최솟값이 $p$, 최댓값을 $q$, $p \le x \le q, (x \ne p, x \ne q)$인 $x$의 개수를 $k$라고 할 때 
  주헌고통지수가 $q-p$인 조합의 개수는 총 $2^k$개이다.   
  그런데 이 또한 naive하게 모든 $p, q$쌍에 대해 구하면 $O(n^2)$ 시간이 요구된다. 
  * $k$값은 정렬하면 바로 알 수 있기 때문에 우선 입력 배열을 정렬할 필요가 있다. ($k$ = 최댓값, 최솟값의 인덱스 차이, 그리고 중복 원소에 대해서도 고려하지 않아도 된다.) 
  그리고 배열의 $i$번째 원소 $A_i$에 대해 $A_i$가 $p$가 될 때가 있고 $q$가될 때가 있을 것이다. 
  $p$일 때는 $A_i * 2^k$만큼 빼주어야 하고 $q$일 때는 $A_i * 2^k$만큼 더해주어야 할 것이다.    
  그리고 이에 따라 정답을 아래와 같이 구할 수 있다.   
  $$\sum_{i=2}^n (A_i \sum_{j=0}^{i-2} 2^j) - \sum_{i=1}^{n-1} (A_i \sum_{j=0}^{n-i-1} 2^j)$$ 
  * 이때 2의 거듭 제곱의 합이 반복적으로 곱해지기 때문에 2의 거듭제곤의 합을 미리 계산해주어서 
  빠르게 문제를 풀 수 있다. 코드에선 이걸 $epsum$ 배열에 저장하였다.

* 시간 복잡도 :
  * 정렬에 가장 큰 시간이 소요된다.
  * $O(n\log n)$
<br></br>
