# Problem
* https://www.acmicpc.net/problem/2367
* 파티에 음식 많이 가져오기
* 난이도 : 플레티넘 4

# Solution

### 방법 1 : 최대 유량, Ford-Fulkerson (Edmonds-Karp)
* 풀이
  * 문제의 조건을 아래와 같이 유량 그래프로 나타낼 수 있다.

![tempFileForShare_20240329-133401](https://github.com/tktj12/cpp-problem-solving/assets/136698877/f6ae5082-6b53-4419-b6a8-ea9b726be091)

* 시간 복잡도 :
  * $O(|V||E|^2) = O((N+D)N^2 D^2)$
<br></br>

### 방법 2 : 최대 유량, Dinic
* 풀이
  * 디닉 알고리즘으로 풀이
	
* 시간 복잡도 :
  * $O(|V|^2|E|) = O((N+D)^2 ND)$
  * 방법 1보다 더 빠르다.
<br></br>
