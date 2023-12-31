# Problem
* https://algospot.com/judge/problem/read/SOLONG
* 출현 빈도에 따른 자동 완성 기능을 사용할 수 있을 때 단어를 만들기 위해 최소로 타이핑해야 하는 횟수 구하기
* 난이도 : 중

# Solution

### 방법 1 : 트라이(trie) 자료구조
* 풀이
  * 트라이 자료구조의 노드의 멤버 변수중에 지금 탭을 누르면 가게되는 경로(현재 노드를 거쳐 갈 수 있는 단어들 중 
출현 빈도가 가장 높은 단어로 가는 경로)를 저장하는 멤버 변수와 그 출현 빈도를 저장하는 멤버 변수를 둔다.
  * 트라이에 새 단어를 삽입할 때 출현 빈도에 대한 정보도 같이 인자로 줘서 각 노드들이 
해당 멤버 변수를 최신화할 수 있게 만든다.
  * 트라이에서 단어를 찾을 때 현재경로가 탭 경로(위의 설명)를 따르는지에 따라 타이핑 카운트를 다르게 한다.


* 시간 복잡도 :
  * $O((n+m)l)$, $n$ : 입력 개수, $m$ : 질문 개수, $l$ 문자열의 길이
<br></br>
