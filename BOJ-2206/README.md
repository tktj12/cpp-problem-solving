# Problem
* https://www.acmicpc.net/problem/2206
* NxM 맵에서 벽을 한 번까지 부술 수 있을 때 최단경로 구하기
* 난이도 : 골드 3

# Solution

### 방법 1 : BFS
* 풀이
  * BFS를 할 때 각 경로 별로 벽을 부순 적이 있는지에 대한 정보를 고려한다.

* 시간 복잡도 :
  * $O(N*M)$
<br></br>

# Learning
* queue의 front를 reference로 참조하고 queue를 pop했을 때 어떤 일이 발생하는지 예상하지 못했다. 
queue에서 pop된 원소는 즉시 소멸한다고 생각해도 될 것 같다.
