# Problem
* https://algospot.com/judge/problem/read/INSERTION
* 삽입 정렬하기 전 배열의 원소들이 왼쪽으로 이동한 거리가 주어질 때 원래 배열을 찾아내기
* 난이도 : 중

# Solution

### 방법 1 : 이진 탐색 트리, 트립(treap)
* 풀이
  * 입력으로 주어진 배열 $A[]$는 원래 배열의 정보를 나타낸다. 
$A_i$는 $i$번 수가 삽입 정렬 때 왼쪽으로 얼마나 이동했는지이다. 
따라서 $A_0$ 부터 $A_{n-1}$까지 실제로 삽입 정렬을 시뮬레이션 하여 정렬된 배열의 인덱스별 위치를 구한다.
  * 실제로 일일이 원소들을 swap하면서 삽입하면 원소 하나당 $O(n)$시간이 소요되므로 
treap 자료구조를 이용하여 원소의 삽입을 $O(\log n)$ 시간 안에 한다.
  * 이렇게 정렬된 배열의 원소들의 원래 인덱스를 구하고 원래 배열의 순서대로 출력한다.

* 시간 복잡도 :
  * $O(n\log n)$
<br></br>

# Learning
* int rand() 함수
  * `<cstdlib>` 헤더 파일에 정의되어있다.
  * 0 ~ RAND_MAX(32767) 중 랜덤한 값을 반환한다.
  * srand(unsigned int seed) 함수로 seed 값을 설정할 수 있다.

* unique_ptr
  * 스마트 포인터 추상 자료를 구현한 것이다.
  * `<memory>` 헤더 파일에 정의되어있다.
  * 동적 할당된 객체의 주소를 '유일하게' 가질 수 있고 동적 할당 메모리를 자동으로 해제해주는 클래스이다.
  * 따라서 delete 할 필요가 없이 객체가 소멸될 때 가리키는 객체 또한 소멸된다.
  * make_unique() 함수로 unique_ptr 객체를 안전하게 생성할 수 있다.   
`unique_ptr<type> p = make_unique<type>();`
  * unique_ptr 객체에서 다른 객체로 포인터를 옮기려면 move() 함수를 사용해서 옮길 수 있다. 옮겨지면서 기존 객체는 소유를 잃는다.   
 `unique_ptr<type> q = move(p);`
