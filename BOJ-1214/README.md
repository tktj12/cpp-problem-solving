# Problem
* https://www.acmicpc.net/problem/1214
* 세상에 지폐가 두 가지만 있을 때 물건을 구입하기 위한 최소 금액 내기
* 난이도 : 플레티넘 5

# Solution

### 방법 1 : 이진트리
* 풀이
  * $P* i + Q*j$ 의 결과는 반복되는 것을 이용하여 필요 없는 계산을 하지 않고 빠르게 수행한다.
  * $P* i + Q*j$ 의 결과를 이진트리 set에 저장하고 같은 결과가 나오면 계산을 종료한다.

* 시간 복잡도 :
  * $O(\sqrt{D} \log \sqrt{D})$
<br></br>

### 백준 minpro0818님 설명
$P * 0$ 부터 $i$를 증가시켜 $P * i + Q * j$의 값을 계산하면 된다. $j$는 $P * i + Q * j \ge D$를 만족하는 최소의 값으로 $i$의 값에 따라 결정된다.   
$P$, $Q$의 최소공배수까지만 계산하면 그 뒤는 계산할 필요가 없다. 
$P * i + Q * j = P * i - LCM(P, Q) + Q * j + LCM(P, Q)$   
$= P * (i - \frac{LCM(P, Q)}{P}) + Q * (j + \frac{LCM(P, Q)}{Q})$ 이고,    
$i - \frac{LCM(P, Q)}{P} = i'$, $j + \frac{LCM(P, Q)}{Q} = j'$으로 놓으면    
$P * i' + Q * j'$가 되는데, $i' < i$이므로 이 값은 이미 계산 했던 값이다.    
따라서 $P * i \ge LCM(P, Q)$라면, $i - \frac{LCM(P,Q)}{P} \ge 0$ 이고, 따라서 $i' \ge 0$이므로 $i'$는 이미 계산했던 값이다.
