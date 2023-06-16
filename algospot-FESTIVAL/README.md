https://algospot.com/judge/problem/read/FESTIVAL

# Solving

* 방법 1 - 무식하게 계산하는 방법
1. 먼저 기준이 되는날 i를 잡는다.
2. i일~(P+L-1)일의 평균부터 P일~N일의 평균까지 계산
3. i의 값이 1 부터 시작해서 N-L+1까지 과정 1,2를 반복해서 평균이 가장 낮은 값을 찾는다.

O(n) = n(n+1) = n<sup>2</sup>


# Learning

* cout의 소수 표현법에 정확도가 달라진다.
* cout 사용시 소수점 아래로 8자리까지 표시하려면 :   
```
cout << fixed 
cout.precision(8)
```
단 9자리에서 반올림 됨

https://pmoncode.tistory.com/20