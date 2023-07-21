# Problem
* https://algospot.com/judge/problem/read/ITES
* 부분수열의 합이 k인 구간 찾기
* 난이도 : 하

# Solution

### 방법 1 : 큐
* 풀이
  * 수열의 첫 원소부터 차례대로 큐에 넣는다.
  * 큐 안에 원소들의 합이 k 이상이 될 때마다 pop 연산과 동시에 합이 정확히 k가 되는지 검사한다.

* 시간 복잡도 :
  * $O(n)$
<br></br>
