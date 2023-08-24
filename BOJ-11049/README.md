# Problem
* https://www.acmicpc.net/problem/11049
* �ּ����� ���� Ƚ���� ��İ��ϱ�
* ���̵� : ��� 3

# Solution

### ��� 1 : ���� ��ȹ��
* Ǯ��
  * $i$��° ��ĺ��� $j(\ge i)$��° ��ı����� ���� �ϱ� ���� �ּ� ������ $DP[i][j]$��� ����.
  $DP[i][j] = min_{i \le p < j} (DP[i][p] + DP[p+1][j] + M_{i, r}*M_{p, c}*M_{j, c} )$ �̴�. 
  ���⼭ $M_i$�� $i$��° ����̰� $r$�� ��, $c$�� ���̴�.

* �ð� ���⵵ :
  * $O(N^3)$
<br></br>

### ��� 2 : ���� ��ȹ��
* Ǯ��
  * ��� �Լ��� �ƴ� �ݺ������� ����

* �ð� ���⵵ :
  * $O(N^3)$
<br></br>

# Learning
* �� ������ $O(N\log N)$ �ð��� Ǫ�� ��� 1 ���̵��� Hu-Shing �˰����� �ִ�.
* https://singun11.tistory.com/107
* https://en.wikipedia.org/wiki/Matrix_chain_multiplication