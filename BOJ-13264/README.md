# Problem
* https://www.acmicpc.net/problem/13264
* 접미사 배열 구하기
* 난이도 : 플레티넘 3

# Solution

### 방법 1 : 맨버-마이어스(Manber-Myers) 접미사 배열 알고리즘
* 풀이
  * 맨버-마이어스 알고리즘은 $O(n\log^2 n)$ 시간 안에 접미사 배열을 사전순으로 구할 수 있다.

* 시간 복잡도 :
  * $O(n\log^2 n)$

* 입력 데이터 중에 정렬에 $O(n^2)$ 시간이 걸리는 데이터가 있는 것 같다. 
이 방법으로는 시간 초과가 난다.
<br></br>

### 방법 2 : 맨버-마이어스(Manber-Myers) 접미사 배열 알고리즘, counting sort
* 풀이
  * 맨버-마이어스 알고리즘에서 정렬하는 부분을 quick sort로 하지 않고 $O(n+k)$시간이 걸리는 
  counting sort로 구현한다. 여기서 $k$는 정렬하는 수의 범위이다. 이 문제에선 문자열의 길이가 $k$이므로 
  $k$는 $n$과 같고 따라서 맨버-마이어스 알고리즘을 $O(n\log n)$시간 안에 수행할 수 있다.

* 시간 복잡도 :
  * $O(n\log n)$

<br></br>

# Learning 
* counting sort는 $O(n+k)$ 시간이 걸리고 stable한 정렬 알고리즘이다.
* stable하다는 뜻은 정렬할 때 중복값들도 그 순서가 유지된다는 뜻이다. 즉 1,0,2,0 을 정렬해서 
0,0,1,2를 얻었다면 앞의 0과 뒤의 0의 순서 유지된다. 반면 quick sort는 unstable하다. 
이 특성은 의미 없어 보이지만, 객체를 정렬할 때 중복값으로 처리되지만 내부 값은 다른 것을 정렬할 땐 중요한 특성이다.

# Review
`index[--cnt[group[perm[i]+t]]] = i;` ... ?   
`res[--cnt[group[perm[index[i]]]]] = perm[index[i]];` ... ????
* counting sort는 이쁘게 짜기 힘들 것 같다..