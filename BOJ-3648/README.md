# Problem
* https://www.acmicpc.net/problem/3648
* 심사위원이 의심하지 않게 투표 조작하기
* 난이도 : 플레티넘 3

# Solution

### 방법 1 : 2-SAT
* 풀이
  * 주어진 입력들로 2-CNF인 논리식을 만들 수 있다.
  * 2-SAT 알고리즘에서 임의의 변수 $A$에 대해 $A$를 표현하는 정점의 SCC가 $!A$를 표현하는 정점의 SCC보다 위상이 높을 경우 
$A$는 거짓일 수밖에 없다.
  * Tarjan 알고리즘으로 주어진 2-CNF에 대해 SCC를 구하여 이를 해결할 수 있다.

* 시간 복잡도 :
  * $O(|N| + |M|)$
<br></br>

# 오답노트
* 2-SAT을 풀 수 있다면 임의의 변수 $a$가 반드시 true도 되고 false도 되는 줄 알았다. $a$는 true, false 중 하나, 혹은 둘 다 가능할 수 있다.