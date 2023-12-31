# Problem
* https://algospot.com/judge/problem/read/DRUNKEN
* 도로의 길이와 장소별 음주 단속 시간이 주어질 때 u에서 v로 가는 최단 경로 구하기
* 난이도 : 상

# Solution

### 방법 1 : 플로이드 알고리즘 (Floyd), 모든 최단 경로 쌍
* 풀이
  * 플로이드 알고리즘은 간선들의 가중치에 대해서만 최단 경로를 계산할 수 있다. 
게다가 음주 단속은 한 장소에서만 할 수 있기 때문에 경로 상의 최대의 정체 시간을 고려해야 한다.
  * 플로이드 알고리즘 수행 도중에 모든 $(u,v)$ 쌍에 대해 $u$에서 $v$로 가는 경로 상의 최악의 정체 시간을 저장하고
최단 경로를 계산할 때 이 값도 고려한다.
    * 이 값을 $delay[u][v]$라고 하자 $(u,v)$ 경로 대신 $k$를 거치는 경로를 선택하는 경우는 
    $(u,v) + delay[u][v]$ 보다 $(u,k) + (k,v) + max(delay[u][k], delay[k][v], delay[k][k])$ 값이 
    더 작은 경우이다. 또한 $k$를 거치는 경로를 선택하는 순간 $delay[u][v]$의 값을 갱신한다.

* 시간 복잡도 :
  * $O(|V|^3 + Q)$

* 반례가 있는 틀린 알고리즘이다.
  * $u$에서 $k$로 가는 경로 중 길이가 10, 정체 시간이 100인 경로 $A$와 길이가 99, 정체 시간이 1인 경로 $B$가 있을 경우 
  $(u, k)$는 경로 $B$를 선택한다. 그런데 $u$에서 $v$로 가는 최단경로를 계산할 때 $(u,k)$, $(k,v)$에서 $(k,v)$가 
  길이가 1, 정체 시간이 100 이라면 $(u,k)$가 A를 선택하는 게 더 낫다.
<br></br>

### 방법 2 : 플로이드 알고리즘 (Floyd), 모든 최단 경로 쌍 (종만북 풀이)
* 풀이
  * 플로이드 알고리즘을 제대로 이해해보자.   
  플로이드 알고리즘은 $u$에서 $v$로 가는 최단 경로 $(u,v)$를 만들기 위해 경유점들의 집합 $S$에 원소를 $1$부터 $|V|$까지 차례대로 넣는다. 
  이때 집합 $S$에 원소를 1부터 넣지 않고 $delay$가 가장 작은 장소부터 넣는다면   
  $delay$를 포함한 최단 경로 : $pathWithDelay[u][v]$, $delay$를 포함하지 않은 최단 경로 : $path[u][v]$ 라고 할 때,   
  $pathWithDelay[u][v] = min( \ pathWithDelay[u][v], \ path[u][k] + path[k][v] + delay[k] \ )$가 성립한다. 
  왜냐하면 어차피 $delay[k]$가 현재까지의 경유점의 $delay$ 중 최댓값이기 때문에 간선의 가중치의 합이 가장 짧은 경로인 $path$만 보면 되기 때문이다.

* 시간 복잡도 :
  * $O(|V|^3 + Q)$

<br></br>
