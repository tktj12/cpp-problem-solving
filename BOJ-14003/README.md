# Problem
* https://www.acmicpc.net/problem/14003
* LIS(longest increasing subsequence) 구하기
* 난이도 : 플레티넘 5

# Solution

### 방법 1 : 균형 이진 트리
* 풀이
  * $O(n \log n)$ 방법으로 LIS의 $i$번째가 될 수 있는 요소를 찾을 때마다 $i$번째 요소를 출현한 순서를 기준으로 이진 트리에 저장한다. 
이렇게 하면 LIS의 $i$번의 요소의 출현 순서를 $O(\log n)$ 시간 안에 알 수 있다.
  * $LIS$의 마지막 요소($LIS_{n}$ 라고 하자)의 최소값의 출현 순서 $ord_{n}$이 있을 때 (ex, LIS가 {1,2,3,4,5} 라면 5의 출현 순서) 
$LIS_{n}$ 이전에 $LIS_{1} ~ LIS_{n-1}$이 출현한건 자명하다. 즉 $ord_{1} ~ ord_{n-1} < ord_{n}$이다.   
이것을 이용하여 $LIS$의 $i$번째 요소를 $O(\log n)$ 시간에 찾는다.

* 시간 복잡도 :
  * $O(n \log n)$
<br></br>
