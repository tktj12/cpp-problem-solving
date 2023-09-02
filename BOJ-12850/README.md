# Problem
* https://www.acmicpc.net/problem/12850
* D시간에 특정 건물에 있을 수 있는 경로의 개수 구하기
* 난이도 : 골드 1

# Solution

### 방법 1 : 수학, 빠른 거듭제곱
* 풀이
  * 정보과학관이 0번, 전산관이 1번, 미래관이 2번, 신양관이 3번, 한경직기념관이 4번, 진리관이 5번, 
  학생회관이 6번, 형남공학관을 7번 건물이라고 하자. 그리고 1x8 행벡터 $C_i$를 정보과학관에서 출발하여 $i$시간에 각 건물에 도달 가능한 경로 
  의 개수로 정의하자. 따라서 $C_0 = \left| 1,0,0,0,0,0,0,0 \right|, \ C_1 = \left| 0,1,1,0,0,0,0,0 \right|$이다. 
  $i$에서 $i+1$로 바뀔 때 각 건물로 가는 경로는 인접한 건물에서 오는 경우밖에 없다. 인접한 건물은 절대 바뀌지 않고, 따라서 
  $C_{i+1} = C_i* W$를 만족하는 $W$가 있다. 그러므로 $C_D = C_0*W^D$이다.
  * $D$가 매우 크므로 분할정복을 이용한 빠른 거듭제곱으로 $W^D$를 구해서 문제를 해결한다.
  * 문제에서 제시된 지도를 통해 $W$를 구할 수 있다.

$$W = \begin{vmatrix} 0 & 1 & 1 & 0 & 0 & 0 & 0 & 0 \\
1 & 0 & 1 & 1 & 0 & 0 & 0 & 0 \\
1 & 1 & 0 & 1 & 1 & 0 & 0 & 0 \\
0 & 1 & 1 & 0 & 1 & 1 & 0 & 0 \\
0 & 0 & 1 & 1 & 0 & 1 & 0 & 1 \\
0 & 0 & 0 & 1 & 1 & 0 & 1 & 0 \\
0 & 0 & 0 & 0 & 0 & 1 & 0 & 1 \\
0 & 0 & 0 & 0 & 1 & 0 & 1 & 0 \\
\end{vmatrix}$$


* 시간 복잡도 :
  * $O(N^2\log D)$, $N$ : 건물 개수, $D$ : 산책 시간
<br></br>