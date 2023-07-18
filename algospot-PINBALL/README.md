# Problem
* https://algospot.com/judge/problem/read/PINBALL
* 2���� ��鿡�� �����ϴ� ���� �ٸ� ��ֹ��鿡 ���� ƨ���� �� �浹�ϴ� ��ֹ����� ���� ���ϱ�
* ���� ����
* ���̵� : ��

# Solution

### ��� 1 : ����, ����
* Ǯ��
  * ������ ������ ����Ͽ� ����
  * $d$ �������� �����ϰ� ���� ��ǥ�� $p$, �������� $1$�� ���� ������ $o$, �������� $r$�� ������ �Ÿ��� $r+1$�� ���� �� �浹�Ѵ�.   
��, ���� $((o-p) - k*d)$�� ���̰� $r+1$�̾�� �ϴ� ���� �̿��Ͽ� �浹 ����, �浹 ��ġ�� �˾Ƴ���.
  * �浹 ��ġ�� $c$�� �� �� o���� c�� ���ϴ� ����� ���̰� ���� ���� $c-o$�� ���� ������� $d$�� �̿��Ͽ� 
�ݻ� ������ ����Ѵ�. �׸����� �׷����� �ս��� ������ �� �ִµ�,
$-d$�� $c-o$�� �翵�� ���͸� $l$ �̶�� �ϸ� $-d * 2*(l-d)$�� ����Ͽ� �� ���� ������ ���� �� �ִ�.

* �ð� ���⵵ :
  * $O(nk)$, $n$ : ��ֹ� ����, $k$ : ����ϴ� �浹 Ƚ��
<br></br>