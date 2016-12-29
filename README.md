# AOJ
AOJ solutions

this repo has solutions of some problems at AOJ(algospot.com)

contact : won.seok.django@gmail.com

---
##전략
1. 비슷한 문제 떠올리기.
2. brute force.
3. 순서를 강제하기.
4. 뒤에서부터 풀어보기.
5. 분해하기/그룹짓기.
6. 손으로 풀어보기.
7. 그림 그려보기.
8. 수식으로 풀어보기.
---
###문제ID : FESTIVAL(AOJ_FESTIVAL.cpp)
2016.12.28.(수)

매우 쉬운 문제에 속한다. 전체 N일 중 L개 이상 연속한 구간을 모두 검사하여 최소의 평균 대여일을 갖는 구간을 찾으면 된다. N의 범위가 1000개 밖에 되지 않으므로 가능한 경우의 수는 아무리 많아 1000H2개 뿐이고 이는 충분히 1초안에 풀 수 있는 입력의 크기이다. 구간의 평균을 구하는 과정에서 이동 평균 아이디어를 사용하면 보다 나은 효율을 보일 수 있다.
```c_cpp
double solve(void)
{
    int sum = 0;
    double avg = MAXAVG;

    for (int s = 0; s <= N - L; ++s)
    {   
        // initial min avg from s to s + L - 1.
        sum = 0;
        for (int l = 0; l < L; ++l)
        {
            sum += COST[s + l]; 
        }
        avg = std::min(avg, (double)sum / L); 

        // min avg from s to e.
        for (int e = s + L; e < N; ++e)
        {
            sum += COST[e];
            avg = std::min(avg, (double)sum / (e - s + 1));
        }
    }   

    return avg;
}
```
---

