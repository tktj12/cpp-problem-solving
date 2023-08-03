# Problem
* https://www.acmicpc.net/problem/15663
* N개의 자연수 중에서 M개를 고른 수열 출력하기
* 난이도 : 실버 2

# Solution

### 방법 1 : 그냥 구현
* 풀이
  * set을 사용하면 중복없는 집합을 사전 순으로 만들 수 있다. 따라서 `set<vector<int>>` 자료형을 사용하여 간단하게 구현한다.

* 시간 복잡도 :
  * $O(N! * \log N!)$
<br></br>
