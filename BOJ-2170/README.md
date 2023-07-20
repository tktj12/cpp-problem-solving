# Problem
* https://www.acmicpc.net/problem/2170
* 1차원 선 위에 겹칠 수 있는 선들의 총 길이 구하기
* 난이도 : 골드 5

# Solution

### 방법 1 : 정렬
* 풀이
  * 선이 그려지기 시작하는 곳을 start, 끝나는 곳을 end 라고 했을 때,
선들을 start 순으로 정렬 후 다음 선의 start와 이전 선의 end의 구간이 겹치면 현재 그리고 있는 선의 start는 유지하고
더 긴 쪽 end로 end 값을 갱신한다.    
겹치지 않을 경우 그리고 있는 선의 길이를 구하고(end - start), start와 end 모두 갱신한다.

* 시간 복잡도 :
  * $O(n \log n)$
<br></br>
