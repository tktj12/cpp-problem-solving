# Problem
* https://algospot.com/judge/problem/read/CHILDRENDAY
* M���� ������̰� ���ִ� N���� ���̵��� ��� �����ϰ� �峭�� ���ֱ�
* ���̵� : ��

# Solution

### ��� 1 : BFS
* Ǯ��
  * $C \mod N = M, (C \ge N)$ �̾�� ��� ������ ������ �� �ִ�.
  * �� ���� $a,b,c (a \ge 0, b > 0, c \ge 0)$�� ���� ���� ���� �����Ѵ�.   
$( (a \mod b) * 10 + c ) \mod b = (10*a + c) \mod b$   
  * $N$���� ���� �������� �������� �ϴ� �Ͻ��� �׷����� �̿��Ͽ� ������ �ذ��Ѵ�.


* �ð� ���⵵ :
  * $O(N*|d|)$
<br></br>