# Problem
* https://www.acmicpc.net/problem/14725
* 트리의 루트에서 리프노드까지의 경로가 여러개 주어질 때 트리의 구조 파악하기
* 난이도 : 골드 3

# Solution

### 방법 1 : 이분 탐색, DFS
* 풀이
  * 주어지는 입력은 트리의 루트에서 리프 노드까지 경로이다. 따라서 트리의 루트에서부터 해당 깊이에 해당하는 문자열을 
  자식 노드로 추가하면 된다. 이미 자식 노드로 추가된 상태라면 입력 배열이 끝날 때까지 더 깊이 들어간다.
  * 또한 어떤 자식 노드를 갖고 있는지를 빠르게 접근하기 위해 map을 사용한다.
  * 출력은 DFS로 전위순회한 것과 같다.

* 시간 복잡도 :
  * $O(k*t *n\log n)$, $t$ : 문자열의 길이, $k$ : 트리의 최대 깊이
<br></br>
