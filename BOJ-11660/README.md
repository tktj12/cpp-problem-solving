# Problem
* https://www.acmicpc.net/problem/11660
* NxN ��Ŀ��� ���� �� ���ϱ�
* ���̵� : �ǹ� 1

# Solution

### ��� 1 : ���� ��
* Ǯ��
  * (1,1)���� (x,y)������ ���� ���� �̸� ���س��´�.
  * $psum(x1,y1,x2,y2) = psum(1,1,x2,y2) - psum(1,1,x2,y1-1) - psum(1,1,x1-1,y2) + psum(1,1,x1-1,y1-1)$

* �ð� ���⵵ :
  * $O(N^2 + M)$
<br></br>
