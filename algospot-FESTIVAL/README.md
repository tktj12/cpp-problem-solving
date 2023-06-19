# Problem
* https://algospot.com/judge/problem/read/FESTIVAL
* 난이도 : 하

# Solving

* 방법 1 - 무식하게 계산하는 방법
1. 먼저 기준이 되는날 i를 잡는다.
2. i일~(i+L-1)일의 평균을 계산하여 최소값과 비교
3. i일~(i+L)일의 평균, i일~(i+L+1)일의 평균, ... , i일~N일의 평균 모두 최소값과 비교
4. i의 값이 1 부터 시작해서 N-L+1까지 과정 1~3를 반복

O((N-L)(N-L+1)) = O(N<sup>2</sup>)


# Learning

* cout의 소수 표현법에 정확도가 달라진다.
* cout 사용시 소수점 아래로 8자리까지 표시하려면 :   
```
cout << fixed 
cout.precision(8)
```
단 9번째 자리에서 반올림 됨

https://pmoncode.tistory.com/20
