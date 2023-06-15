https://algospot.com/judge/problem/read/FESTIVAL

# 풀이

* 방법 1 - 무식하게 계산하는 방법
1. 먼저 기준이 되는날 P를 잡는다.
2. P일~(P+L-1)일의 평균부터 P일~N일의 평균까지 계산
3. P의 값이 1 부터 시작해서 N-L+1까지 과정 1,2를 반복해서 평균이 가장 낮은 값을 찾는다.

O(n) = n(n+1)  
'   '= n<sup>2</sup>