# Problem
* https://algospot.com/judge/problem/read/NAMING
* ���ڿ��� ���λ��̸鼭 ���̻��� �κ� ���ڿ��� ���ϱ�
* ���̵� : ��

# Solution

### ��� 1 : KMP �˰����� (Ŀ����-�𸮽�-���� �˰�����)
* Ǯ��
  * $getPartialMatch(str)$ �Լ��� KMP �˰������� ������ ���̴�. �� �Լ��� ��ȯ�ϴ� �迭 $p$�� ���
$p[i]$�� $str[..i]$�� ���λ絵 �ǰ� ���̻絵 �Ǵ� ���ڿ��� �ִ� �����̴�. ($p[0]$�� ������ �ʴ´�, $str[..i]$ : ���̰� $i+1$�� $str$�� �κ� ���ڿ�)
  * �� ������ ���ϴ� ���� "��ü ���ڿ��� ���λ絵 �ǰ� ���̻絵 �Ǵ� ���ڿ���"�� ���� ������ ������������ ������
�迭�� $answer$��� �� ��, ���ڿ� $answer[i]$�� $answer[i-1]$�� ���λ����� ���̻��� �� �ۿ� ����.   
�̰��� �̿��Ͽ� ������ �ذ��Ѵ�.

* �ð� ���⵵ :
  * $O(n)$, $n$ : ���ڿ��� ����
<br></br>