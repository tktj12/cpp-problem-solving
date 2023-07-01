# Problem
* https://algospot.com/judge/problem/read/NUMB3ERS
* 경로가 있는 노드들에서 d일 뒤에 특정 노드에 있을 확률
* 난이도 : 하

# Solution

### 방법 1 : 완전 탐색
* 풀이
  * 전체 경우를 전부 탐색하고 확률을 구함

* 시간 복잡도 :
  * $O(n^d)$
<br></br>

### 방법 2 : 동적 계획법
* 풀이
  * 방법 1의 경우들에 대해 메모이제이션을 구현

* 시간 복잡도 :
  * $O(n^2 d)$

# Learning
* `double`변수의 비트값이 전부 1인 상태 `0xFFFFFFFFFFFFFFFF` 이면, nan으로 처리된다.
* `double d = 0xFFFFFFFFFFFFFFFF` 이후에 d의 비트값을 확인하면   
`0x43F0000000000000` 이다. 즉 16비트 표현으로 값을 대입해도 비트값이 그대로 옮겨지진 않는다.   
따라서 double형은 memset이나 형변환으로 비트값을 직접 할당해야 한다.
