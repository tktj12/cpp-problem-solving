# Problem
* https://algospot.com/judge/problem/read/BISHOPS
* 장애물들이 있는 NxN 체스판에 비숍들을 서로 공격하지 않도록 최대한 많이 놓는 경우 구하기
* 난이도 : 중

# Solution

### 방법 1 : 이분 매칭, 매칭 문제
* 풀이
  * 체스판에서 대각선을 두 종류로 나눌 수 있다. 하나는 오른쪽으로 갈 수록 올라가는 '/'과 같은 형태의 대각선이고, 
  하나는 오른쪽으로 갈 수록 내려가는 '\'형태의 대각선이다. 전자를 ascend, 후자를 descend라고 하겠다.   
  비숍은 두 대각선이 겹쳐지는 곳에 둘 수 있다고 생각할 수 있다. 따라서 하나의 비숍은 하나의 ascend와 하나의 descend를 
  포함하고, 다른 비숍은 이미 선택된 ascend와 descend를 포함할 수 없다.   
  따라서 이 문제를 하나의 ascend당 하나의 descend를 고르는 이분 매칭 문제로 변환하여 해결할 수 있다.

* 시간 복잡도 :
  * $O(|V||E|) = O(N^4)$
<br></br>
