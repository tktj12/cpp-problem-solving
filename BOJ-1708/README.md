# Problem
* https://www.acmicpc.net/problem/1708
* N개의 점을 전부 포함하는 볼록 껍질 구하기
* 난이도 : 플레티넘 5

# Solution

### 방법 1 : 유클리드 벡터, 그레이엄 스캔 (Graham Scan)
* 풀이
  * 그레이엄 스캔은 최하단의 최좌단 점을 기준으로 하여 이 점의 반시계 방향으로 다른 점들을 정렬하여 볼록 껍질을 만드는 방법이다. 

* 시간 복잡도 :
  * $O(n\log n)$
<br></br>
