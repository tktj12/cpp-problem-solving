# Problem
* https://algospot.com/judge/problem/read/GRADUATION
* 태우는 졸업을 할 수 있는가 / 
전공과목, 선수과목, 학기별 개설과목 등 여러 조건이 있을 때 최소한 다녀야 할 학기 수 구하기
* 난이도 : 중

# Solution

### 방법 1 : 동적 계획법, 비트 마스킹
* 풀이
  * $Graduate(semester, learned)$ : 현재 학기가 semester, 들은 과목이 learned일 때
최소로 몇 학기를 더 들어야 졸업 가능한가
  * $N$이 충분히 작기 때문에 비트 마스킹을 이용하여 빠르게 풀 수 있다.

* 시간 복잡도 :
  * $O(M*2^{N+C})$
<br></br>
