# Problem
* https://algospot.com/judge/problem/read/PICNIC
* 난이도 : 하

# Solution
 
* 방법 1 : 완전탐색
1. 남아있는 학생 중 번호가 가장 빠른 학생을 고른다.
2. 나머지 학생 중 번호가 빠른 순서대로 가능한 짝인지 살펴본다.
3. 가능한 짝을 찾았고 아직 학생이 남아있다면, 다시 1번으로 돌아간다.
4. 가능한 짝을 찾았고 학생이 남아있지 않다면, 카운트를 1 증가시킨다.

* 시간 복잡도 :
$$O\left( \prod_{k=1}^\frac{N}{2} {2k-1} \right) = O((N-1)!!) = O(N!!)$$

* 시간 복잡도는 $O(N!!)$이지만 문제의 N이 최대 10이기때문에 시간 초과가 나지 않는다.

# Learning
* C++언어의 구글식 명명법에 관한 글을 읽었다.
https://torbjorn.tistory.com/257

* vector의 push_back() 함수는 값을 복사해서 배열의 새 원소를 생성한다.
* push_back({1, 2}) 처럼 쓸 수 있다.