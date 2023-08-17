# Problem
* https://www.acmicpc.net/problem/1725
* 히스토그램 막대그래프에서 가장 큰 직사각형의 넓이 구하기
* 난이도 : 플레티넘 5

# Solution

### 방법 1 : 분할정복 (divide and conquer)
* 풀이
  * $Divide(lo, hi)$ : [lo,hi]의 중간에 있는 막대를 포함하는 직사각형, [lo,mid-1]에서 가장 큰 직사각형, 
[mid+1,hi]에서 가장 큰 직사각형 반환

* 시간 복잡도 :
  * $O(n\log n)$
<br></br>
