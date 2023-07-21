# Problem
* https://algospot.com/judge/problem/read/CHRISTMAS
* 산타할아버지의 인형 주문 / K명의 아이들에게 남김없이 같은 수의 인형 나눠주기
* 난이도 : 상

# Solution

### 방법 1 : 
* 풀이
  * $(a - b) \mod k = 0$ 이기 위해서는 $a\mod k = b\mod k $이어야 한다.
이런 성질과 구간 합을 이용하여 문제를 해결한다.

* 시간 복잡도 :
  * $O(n\log n)$
<br></br>
