# Problem
* https://www.acmicpc.net/problem/1918
* 중위 표기법을 후위 표기법으로 바꾸기
* 난이도 : 골드 2

# Solution

### 방법 1 : 스택
* 풀이
  * 알파벳은 순서대로 정답에 집어넣고, 연산자들은 :   
  1. 스택이 비었거나 스택의 탑에 있는 원소보다 우선순위가 높다면 스택에 저장한다.   
  2. 스택의 탑에 있는 원소보다 우선순위가 낮은 연산자면 1번이 만족할 때 까지 pop해서 정답에 집어넣는다. 
  3. 괄호 안의 연산자들은 괄호 밖에 있는 모든 연산자들보다 우선순위가 높다.
  4. 마지막에 스택을 모두 비운다.

* 시간 복잡도 :
  * $O(N)$
<br></br>
