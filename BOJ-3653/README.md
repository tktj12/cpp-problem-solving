# Problem
* https://www.acmicpc.net/problem/3653
* 규칙에 따라 DVD를 뺄 때 DVD 위에 몇 개의 DVD가 있는지를 여러 번 구하기
* 난이도 : 플레티넘 4

# Solution

### 방법 1 : 균형 이진 트리(Treap)
* 풀이
  * DVD 스택을 이진 트리로 관리한다.
  * DVD의 숫자 별로 key값을 다르게 한다.
	* 처음에는 key값과 DVD 숫자가 같지만, DVD를 빼고 다시 스택에 쌓을 때 key값을 다른 모든 DVD의 key값 보다 작게 설정한다.
	* 이후 이진 트리에 해당 DVD의 key값을 넣으면 스택의 가장 위에 쌓는 것과 같은 논리이다.
  * Treap을 사용하면 $key$보다 작은 키값이 몇개인지를 $O(\log N)$시간 안에 구할 수 있다.

* 시간 복잡도 :
  * $O((N+M)\log N)$
<br></br>

### 방법 2 : Segment Tree
* 풀이
  * DVD스택을 N+M으로 미리 크게 잡고 세그먼트 트리로 구간별 DVD개수를 저장할 수 있다.

* 시간 복잡도    
$O((N+M)\log (N+M)$