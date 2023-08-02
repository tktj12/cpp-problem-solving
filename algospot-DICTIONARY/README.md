# Problem
* https://algospot.com/judge/problem/read/DICTIONARY
* 입력의 순서를 통해 알파벳의 순서 알아내기
* 난이도 : 중

# Solution

### 방법 1 : 큐, DFS
* 풀이
  * 임의의 알파벳 $p$보다 사전순으로 앞서는 알파벳 $q$를 그래프 상에서 $q->p$로 표현하고 
DFS로 위상 정렬을 하려 문제를 해결한다.

* 시간 복잡도 :
  * $O(n*l)$

* 처음 생각대로 큐를 이용하여 풀었지만 굳이 큐를 쓸 필요가 없이 바로 다음 단어와 비교하는 것 만으로도 충분하다.
<br></br>
