# Problem
* https://algospot.com/judge/problem/read/NERD2
* 푼 문제 수, 라면 그릇 수로 판별하는 너드
* 난이도 : 중

# Solution

### 방법 1 : 균형 이진 트리 (STL set, red-black tree)
* 풀이
  * 균형 이진 트리 $nerd$를 사람을 추가할 때마다 푼 문제 수 $P$를 기준으로 정렬해둔다.
  * 현재 참가 신청한 사람을 $i$라고 했을 때 $i$가 $nerd$에 들어가기 위해서는 $P_i < P_b$를 만족하는 가장 작은 값을 갖고있는 
$nerd$의 원소 $b$와 $Q_b < Q_i$를 만족해야 한다.   
  * $nerd$에 $i$를 넣었을 때 $O(\log n)$ 시간 안에 $nerd_{i+1}$를 알 수 있다.
  * $i$가 $nerd$에 들어가는 경우 $nerd$에서 빠져야 하는 사람들이 있을 수 있다.   
$nerd$는 정렬되어 있다. 따라서 $nerd_{i-1}$부터 조건을 만족하는 원소를 발견할 때 까지 조건을 만족하지 않는 
원소들을 모두 삭제한다.

* 시간 복잡도 :
  * $O(n\log n)$
<br></br>
