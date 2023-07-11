# Problem
* https://algospot.com/judge/problem/read/LUNCHBOX
* 도시락 데우기 / 모든 도시락을 하나씩 데우고, 먹는 시간을 최소로 만들기
* 난이도 : 하

# Solution

### 방법 1 : 그리디
* 풀이
  * 먹는시간 $e_i$가 제일 큰 것 부터 먹는다.
* 탐욕적 선택 속성 증명 - greedy choice property 
  * $e_i > e_j$ 인 $j$ 도시락을 먼저 데우는 최적해가 있다고 가정했을 때 $i$ 도시락과 $j$ 도시락의 순서를
바꾸어도 전체 시간이 늘어나지 않는다. 따라서 $i$ 도시락을 먼저 먹는 최적해가 존재한다.

* 시간 복잡도 :
  * $O(n\log n)$
<br></br>
