# Problem
* https://www.acmicpc.net/problem/11660
* NxN 행렬에서 구간 합 구하기
* 난이도 : 실버 1

# Solution

### 방법 1 : 구간 합
* 풀이
  * (1,1)부터 (x,y)까지의 구간 합을 미리 구해놓는다.
  * $psum(x1,y1,x2,y2) = psum(1,1,x2,y2) - psum(1,1,x2,y1-1) - psum(1,1,x1-1,y2) + psum(1,1,x1-1,y1-1)$

* 시간 복잡도 :
  * $O(N^2 + M)$
<br></br>
