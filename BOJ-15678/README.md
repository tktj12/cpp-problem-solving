# Problem
* https://www.acmicpc.net/problem/15678
* ���� ¡�˴ٸ��� ������ �� �ִ�� ���ϱ�
* ���̵� : �÷�Ƽ�� 5

# Solution
### �м�
* N���� ������, �ִ� �̵��Ÿ� D
* �Դ� ���� �� �ʿ䰡 ���� == ������ �ٲ� �ʿ䰡 ����
* �� �� �ִ� �� �� 0�̻��� �ִٸ� ���� ����� �� ������ �ȴ�.

### ��� 1 : DP, Segment Tree
* ��ͽ� :   

$$DP(pos)=
\begin{cases}
score[pos]+max_{1\le i \le D} (DP(pos-i)), & \mbox{if } max_{1\le i \le D} (DP(pos-i)) > 0 \\
score[pos], & \mbox{else}
\end{cases}$$

* Ǯ�� :
  * 
  
* Time Complexity :   
$O(N\log N)$
<br></br>
