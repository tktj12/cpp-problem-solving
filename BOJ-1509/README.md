# Problem
* https://www.acmicpc.net/problem/1509
* ���ڿ��� �Ӹ������ ���ڿ���� �����ϴ� ��� �� �ּҷ� �����ϴ� ��� ���ϱ�
* ���̵� : ��� 1

# Solution

### ��� 1 : Manacher, DP
* Ǯ��
  * $DP[i]$ : $i$�� �ε������� �ּ��� �Ӹ���� ���� ����. 
  * �ų�ó �˰��������� �Ӹ���� �κ� ���ڿ����� ���ϰ�, $DP$ �迭�� �ϼ��Ѵ�.
  * $i$�� �ε����� �߽����� �ϴ� �Ӹ������ �������� $p$�̸� $0 \le k \le p$�� ���� ������ ���� �� �ִ�.
  $DP[i+k] = min(DP[i+k], DP[i-k-1] + 1)$

* �ð� ���⵵ :
  * $O(N^2)$
<br></br>