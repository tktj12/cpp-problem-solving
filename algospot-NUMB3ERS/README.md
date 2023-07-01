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
  * $DP(now, village, remaining_day)$ now에서 remaining_day일 이후 village로 갔을 확률

* 시간 복잡도 :
  * $O(n^2dt)$
<br></br>

### 방법 3 : 동적 계획법 (종만북 풀이)
* 풀이
  * $DP2(here, day)$ : day일에 here에 있을 확률
  * 방법 2는 첫날 감옥에서 출발해서 계산하지만, 방법 3의 경우 마지막 날에서 첫날로 돌아간다.
  * 방법 2는 특정 마을로 가는 확률만을 계산해서 구하고자 하는 마을이 달라지면 처음부터 다시
계산해야 하지만 방법 3의 경우 어떤 마을을 계산하든 이전에 계산한 값을 사용할 수 있기 때문에 더 효율적이다.

* 시간 복잡도 :
  * $O(n^2d)$

# Learning
* `double`변수의 비트값이 전부 1인 상태 `0xFFFFFFFFFFFFFFFF` 이면, nan으로 처리된다.
* `double d = 0xFFFFFFFFFFFFFFFF` 이후에 d의 비트값을 확인하면   
`0x43F0000000000000` 이다. 즉 16비트 표현으로 값을 대입해도 비트값이 그대로 옮겨지진 않는다.   
따라서 double형은 memset이나 형변환으로 비트값을 직접 할당해야 한다.
