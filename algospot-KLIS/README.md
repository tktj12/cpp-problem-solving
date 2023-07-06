# Problem
* https://algospot.com/judge/problem/read/
* K��° LIS ���ϱ�
* ���̵� : ��

# Solution

### ��� 1 : 
* Ǯ��
  * �� ������ ��� ������ � �� this�� �� LIS�� ���Եȴٰ� ���� �� �� LIS���� this �ڿ� �� �� �ִ� ����
�������� ������ Ȯ���� ����� ã�� �� �߿��ϴ�.
  * �� ��� LIS ������ Ǯ���� �� ����� $O(N\log{N})$ ����� Ȱ���ߴ�. ���� ����� LIS�� i��°�� �� �� �ִ� ���� ����
�� �ϳ����� ����������, �� Ȱ���ؼ� LIS�� i��°�� �� �� �ִ� ������ ���� ������ ����Ͽ� ���� �� �ִ� LIS�� �� ������
������ ���� �� �ֵ��� �ߴ�.
  * [0��° ������ ����]   
[1��° ������ ����]   
[2��° ������ ����]   
. . .   
[n-1��° ������ ����]
  * �� ��� ������ ���տ��� LIS�� ���� ������ �����Ͽ� LIS�� ���� ������ ���� �� �ִ�.
  * �� ���ư��� �� ������ y,x ��ǥ(cur_len, vector_idx)�� �������� �޸������̼��� �� �� �ִ�.

* �ð� ���⵵ :
  * $O(N\log{N} + N^2 + N^2) = O(N^2)$
<br></br>