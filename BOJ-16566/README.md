# Problem
* https://www.acmicpc.net/problem/16566
* 이미 냈던 숫자는 지우면서 UpperBound 쿼리 여러번 하기
* 난이도 : 플레티넘 5

# Solution
STL map을 쓰면 시간 초과가 난다.

### 방법 1 : Union Find 자료구조
* 풀이
  * LowerBound를 root로 하는 Union Find 자료구조를 만들어 해결한다. 
  즉, 민수의 덱에 3,7,10이 있으면 1-3의 root는 3, 4-7의 root는 7, 8-10의 root는 10이다.
  * 구하고 싶은 건 UpperBound이기 때문에 철수의 숫자에 +1을 한 값을 Find한다.
  * 민수가 낸 카드의 숫자와 이 숫자에 +1한 숫자를 Merge해주어서 LowerBound를 갱신한다.

* 시간 복잡도 :
  * $O(N+K)$
<br></br>

# Review
* 풀이 알고리즘과 비슷하게 처음에 떠올렸는데, 안 될 거라고 생각했다.
* 유니온 파인드의 재밌는 활용 문제인 것 같다.