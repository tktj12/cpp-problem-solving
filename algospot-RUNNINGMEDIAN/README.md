# Problem
* https://algospot.com/judge/problem/read/RUNNINGMEDIAN
* 정렬한 수열의 달라지는 중간값들 모두 구하기
* 난이도 : 하

# Solution

### 방법 1 : 우선 순위 큐, heap
* 풀이
  * 중간값보다 큰 값은 최소 힙에, 작은 값은 최대 힙에 넣어서 매 순간 중간값을 구하기 용이하게 하여 해결한다.

* 시간 복잡도 :
  * $O(n \log n)$
<br></br>
