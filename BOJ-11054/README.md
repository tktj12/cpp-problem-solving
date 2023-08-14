# Problem
* https://www.acmicpc.net/problem/11054
* 가장 긴 바이토닉 부분 수열 구하기
* 난이도 : 골드 4

# Solution

### 방법 1 : LIS 구하는 n log n 알고리즘
* 풀이
  * $rightLen[i]$ : 전체 수열의 왼쪽부터 오른쪽으로 i+1번 봤을 때 LIS의 최대 길이
  * $rightTop[i]$ : 전체 수열의 왼쪽부터 오른쪽으로 i+1번 봤을 때 LIS의 가장 큰 수
  * $leftLen[i]$ :  전체 수열의 오른쪽부터 왼쪽으로 i+1번 봤을 때 LIS의 최대 길이
  * $leftTop[i]$ :  전체 수열의 오른쪽부터 왼족으로 i+1번 봤을 때 LIS의 가장 큰 수
  * 이 네 가지 배열을 채우면 $O(n)$시간 안에 어떤 수를 기준으로 해야 가장 긴 바이토닉 수열을 얻을 수 있는지 구할 수 있다.

* 시간 복잡도 :
  * $O(n\log n)$
<br></br>
