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

###문제ID : PICNIC(AOJ_PICNIC.cpp)

2016.12.30.(금)

입력의 크기가 10으로 매우 작은 편이어서 brute force 방법으로 모든 경우의 수를 세어주면 된다. 최악의 경우(모두가 친구인 경우)에도 10C2 * 8C2 * 6C2 * 4C2 * 2C2 / 5! - 945개의 조합만이 존재하므로 충분히 주어진 시간 내에 풀 수 있다. 다만, 모든 조합을 탐색하는 함수의 구현이 처음에는 조금 어색하게 느껴졌었는데 구현 해놓고 보니 잘 동작하였고 책의 구현과도 거의 일치하였다. 재귀적으로 수행되는 함수 solve는 아래와 같이 동작한다.

```c_cpp

/**
  * 모든 학생이 짝을 가지게 된 경우 1을 반환하고, 불가능한 조합의 경우 0을 반환한다.
  * 짝을 가지지 않은 사전 순으로 가장 앞선 학생을 찾고, 역시 사전 순으로 짝을 배정한다.
  * 재귀적으로 반복하여 모든 가능한 조합의 수를 센다.
  */
int solve(void)
{
    int idx;
    for (idx = 0; idx < N && IS_PAIRED[idx]; ++idx);

    if (idx == N)                                   ///< 모든 학생이 짝을 찾은 경우 1을 반환.
        return 1;

    int ret = 0;                                    ///< 불가능한 조합인 경우에는 0을 반환.
    for (int l = 0; l < N; ++l)
    {   
        if (!IS_PAIRED[l] && IS_FRIEND[idx][l])
        {   
            IS_PAIRED[idx] = IS_PAIRED[l] = true;   ///< 선택을 반영.
            ret += solve();                         ///< 조합의 갯수를 센다.
            IS_PAIRED[idx] = IS_PAIRED[l] = false;  ///< 선택 반영을 취소.
        }   
    }   

    return ret;
}

```

---