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

###문제ID : BOARDCOVER(AOJ_BOARDCOVER.cpp)

2017.01.04.(수)

처음에 문제를 푸는 방향을 잘못 잡아서 고생을 했다. 맨 처음의 접근은 다음과 같았다.

1. 매 재귀 호출마다 보드에서 row-major로 가장 처음의 빈 칸을 찾는다.
2. 빈 칸이 없다면 보드 덮기에 성공한 경우이다.
3. 빈 칸에 대하여 다음의 5가지 경우에 대하여 전-탐색 해본다.

    a. 해당 칸을 확인하였음만 표시하고 아무 블록도 배치하지 않는다(다음 번의 재귀 호출에서 채워지도록 빈칸으로 유지).
    b. 해당 칸에 아래의 4가지 경우의 블록으로 배치해본다.
    
    ![boardcover1](https://github.com/wonseokdjango/AOJ/blob/master/images/boardcover1.png)
    
이 방법은 각 빈 칸에 대하여 5가지 경우의 수를 고려하게 되고 이는 rough하게 5^50개의 경우의 수를 세게 된다. 이는 2초 제한에 풀기에는 큰 경우의 수이므로 답을 구할 수는 있지만 TLE를 겪게 된다.

다음으로 시도한 방법은 처음 접근한 방법인 brute force를 유지하되 순서를 강제화 시킨 방법이다. 매 재귀 호출마다 row-major로 가장 처음의 빈 칸을 찾으므로 row-major로 해당 빈 칸 이전에 위치하는 빈 칸들은 이미 모두 채워진 형태로 가정하는 것이 방법의 핵심이다. 

1. 매 재귀 호출마다 보드에서 row-major로 가장 처음의 빈 칸을 찾는다.
2. 빈 칸이 없다면 보드 덮기에 성공한 경우이다.
3. 빈 칸에 대하여 아래의 경우를 고려한다.

    ![boardcover1](https://github.com/wonseokdjango/AOJ/blob/master/images/boardcover2.png)

실제로 row-major로 해당 빈칸 이전의 블록이 모두 채워져 있다고 가정한다면 고려의 대상이 되는 블록은 2, 5, 9, 12번째 블록 뿐이다. 따라서, 위의 4개 블록에 대하여 전-탐색을 수행하면 경우의 수가 4^(floor(50/3))이 되게 된다. 이 역시 2초 제한에 풀리기는 어려운 정도의 경우의 수인데 실제로 구현해보게 되면 n-th 재귀단계에서 놓은 블록의 형태에 따라 n+1-th 재귀단계에서 놓게 되는 블록이 크게 제한되므로 prunning이 커지게 된다. 예를 들어 2*3 크기의 보드를 덮기 위해서는 이론적으로 4^2개의 경우의 수를 고려해야하지만 실제로는 12개 밖에 고려하지 않는다. 이렇게 문제를 분석해보고 이론과 구현의 수행시간이 다르다는 것을 사전에 파악할 수 있는 것이 중요한데, 과연 실제로 문제를 풀 때 이런 부분들을 잘 대처할 수 있는지에 대한 자신이 없다.

```c_cpp

int solve(void)
{
    int r, c;
    for (r = 0; r < H; ++r)
    {
        for (c = 0; c < W; ++c)
        {
            if (BOARD[r][c] == '.')
                break;
        }

        if (c != W)
            break;
    }

    if (r == H && c == W)
        return 1;

    int ret = 0;
    for (int blk = 0; blk < NUMOFBLOCKS; ++blk)
    {
        int idx;
        for (idx = 0; idx < NUMOFBLANKS; ++idx)
        {
            if (
                !safe(r + dr[blk][idx], c + dc[blk][idx]) ||
                BOARD[r + dr[blk][idx]][c + dc[blk][idx]] != '.')
                break;
        }
        // you can put blk-th block.
        if (idx == NUMOFBLANKS)
        {
            for (idx = 0; idx < NUMOFBLANKS; ++idx)
                BOARD[r + dr[blk][idx]][c + dc[blk][idx]] = '#';
            ret += solve();
            for (idx = 0; idx < NUMOFBLANKS; ++idx)
                BOARD[r + dr[blk][idx]][c + dc[blk][idx]] = '.';
        }
    }

    return ret;
}

```

---

###문제ID : CLOCKSYNC(AOJ_CLOCKSYNC.cpp)

2017.01.06.(금).

직접 모든 경우를 전-탐색하는 방법으로 풀어낼 수 있는 문제이다. 전탐색을 적용하기 위해서는 아래와 같은 두 가지 사실을 깨닫는 것이 중요하다.

    1. 버튼을 누르는 순서는 답에 영향을 주지 못한다.
    2. 버튼을 4회 이상 누르는 것은 마무런 의미가 없다.

따라서, 버튼을 누르는 순서를 0번~9번으로 강제화하고, 각 버튼의 클릭을 0회~3회로하여 전-탐색을하게 되면 총 4^10개의 경우의 수반을 탐색하게 된다. 이는 제한시간 내에 충분히 문제를 풀어낼 수 있다. 한편, 재귀함수의 경우 _(이번에 고려할 버튼의 번호, 현재까지 버튼의 클릭 횟수)_ 를 인자로 받아 고려할 가치가 없는 답의 후보는 적절히 prunning한다.

```c_cpp

void solve(int btn, int cnt)
{
    int clk;
    for (clk = 0; clk < NUMOFCLOCKS && CLOCKS[clk] == 0; ++clk);
    if (clk == NUMOFCLOCKS)
    {
        CNT = (CNT > cnt) ? cnt : CNT;
        return;
    }

    if (btn == NUMOFBUTTONS)
        return;

    // click btn-th button.
    int idx;
    for (int click = 0; click < 4 && cnt + click < CNT; ++click)
    {
        idx = 0;
        while (TRIGGER[btn][idx] != -1)
        {
            CLOCKS[TRIGGER[btn][idx]] = (CLOCKS[TRIGGER[btn][idx]] + 3 * click) % 12;
            ++idx;
        }

        solve(btn + 1, cnt + click);

        idx = 0;
        while (TRIGGER[btn][idx] != -1)
        {
            CLOCKS[TRIGGER[btn][idx]] = (CLOCKS[TRIGGER[btn][idx]] + 9 * click) % 12;
            ++idx;
        }
    }
}

```

---

###문제ID : QUADTREE(AOJ_QUADTREE.cpp)

2016.01.06.(금).

직접 손으로 문제를 풀어보게 되면 자연스레 TREE를 그리게 된다(어쩌면 문제 이름 자체가 TREE이니 당연한 것일 수도 있겠다). 몇 번 풀어보면 TREE의 leaf node부터 상하를 반전시켜주면 되는 것을 알 수 있고 재귀함수를 사용하면 될 것 같은 강한 느낌을 받을 수 있다. 이때, 실제로 TREE를 구성하고 재귀적으로 상하를 반전시킬지 그냥 문자열을 읽으면서 처리할지 고민했는데 아무래도 두 번째 풀다보니 TREE를 직접 구성하지 않고도 충분히 풀 수 있다는 것이 떠올랐던 것 같다. 재귀함수로 문제를 풀기로 결심했으니 재귀함수의 return 값과 parameter를 무엇으로 할 지, base case는 무엇인지, recursive step은 무었인지 결정해주면 된다. 각각을 아래와 같이 결정하였다.

1. 반환 값
> 결국 프로그램에서 상하가 반전된 QUADTREE 문자열을 반환해줘야하는데 이 문자열을 재귀함수 내에서 하나의 전역 문자열 버퍼에 쓰기로 결정하면 전역 버퍼에 쓰인 문자열의 순서를 재배치 해주어야하는 등 귀찮아진다. 이런 경우 반환 값을 재귀함수의 반환 값으로 해주면 보다 쉬운 코딩이 가능하다. 따라서, 재귀함수는 현재 위치로부터 sub-tree를 상하반전 시킨 QUADTREE문자열을 반환한다.
2. 인자
> 입력 문자열에서 어디까지 읽었는지를 알 수 있어야 재귀함수의 각 단계에서 어디서부터 QUADTREE 변환을 시작할지를 결정할 수 있다. 따라서, 재귀함수의 인자로 '이번에 읽을 입력 문자열 위치'를 준다. CLOCKSYNC에서 재귀함수가 cnt를 인자로 가졌던 것과 유사하게 재귀적으로 유지되어야 할 값들의 경우 인자로 설정하면 편리하다.
3. base case
> base case는 당연히 'b', 'w'와 같이 한 색의 타일로 이뤄진 경우이다. 즉, 이번에 읽을 입력 문자열 위치에 'b' 또는 'w'가 쓰여 있다면 곧장 문자열 "b" 또는 "w"를 반환한다.
4. recursive step
> 이번에 읽을 입력 문자열 위치에 'x'가 쓰여 있다면 재귀적으로 sub-tree를 상하반전 시켜줘야 함을 의미한다. 이 경우, 순서대로 upper-left, upper-right, lower-left, lower-right를 재귀적으로 뒤집어주고, lower-left, lower-right, upper-left, upper-right 순으로 sub-tree의 순서를 뒤집어 반환해준다.

base case와 recursive step을 정하는 것 만으로 문제가 풀린다는 것을 직관적으로 알 수 있다. 이제 문제가 실제로 제한시간 내에 풀릴지 고려해봐야 한다. 대체, 왜, 어째서 학부때부터 항상 까먹는지 이해할 수 없는 master theorem이 사용된다.

![masterthm](https://github.com/wonseokdjango/AOJ/blob/master/images/masterthm.png)

T(n) = 4 * T(n/4) + n 이므로 T(n) = nlgn이고, 이는 제한 시간에 문제를 충분히 풀 수 있음을 보여준다.

```c_cpp

string solve(int pos)
{
    // base case.
    if (QUADTREE[pos] != 'x')
    {
        return QUADTREE.substr(pos,  1);
    }

    // recursive step.
    string ul, ur, ll, lr;
    ul = solve(pos + 1);
    ur = solve(pos + 1 + ul.size());
    ll = solve(pos + 1 + ul.size() + ur.size());
    lr = solve(pos + 1 + ul.size() + ur.size() + ll.size());

    return "x" + ll + lr + ul + ur;
}

```

---

###문제ID : FENCE(AOJ_FENCE.cpp)

2017.01.07.(토).

의외로 2번이나 오답을 냈다. 첫 번째는 현재 사용 중인 IDE에서 콘솔 복사 붙여넣기를 지원하지 않기에 freopen(*)을 사용했었는데 submit할 때 이를 수정하지 않고 그대로 제출해서 오답을 겪었다. #ifdef 구문 등을 활용해서 앞으로 비슷한 실수를 방지하는 것이 좋을 것 같다. 두 번째 오답은 구간에 대한 분할 정복 알고리즘을 사용하는 단계에서 s, e(또는 lo, hi)의 indexing 실수로 인해 발생했다. 항상 비슷한 문제를 풀 때 indexing을 실수하는 경우가 있는데 이 역시 직접 몇몇 case를 손으로 풀어보는 방법으로 극복하는 노력이 필요할 것으로 보인다.

이 문제는 분할정복 아이디어를 사용해서 풀 수 있다. 문제가 분할 정복 단원에 수록되어서 떠올릴 수 있었던 건지, 실제로 분할 정복이 떠오르는 문제 형식이어서 그랬던 것인지는 스스로 매우 의심스럽지만 우선 풀기로 했다. 최대의 넓이를 갖는 직사각형은 아래의 3가지 경우 중 하나에 반드시 속한다.
> 1. [s, m) 구간의 fence를 사용해서 만들어지는 경우.
> 2. (m, e] 구간의 fence를 사용해서 만들어지는 경우.
> 3. m을 포함하는 fence의 집합으로 만들어지는 경우.

1, 2.같은 경우는 간단하게 재귀 함수를 호출해주면 해결할 수 있지만, 3.의 경우 약간은 고민스러웠다. 처음에는 m을 포함하는 fence의 집합을 어디까지(어느 크기까지) 고려해주어야 하는가에 대해 기준이 있지 않을까 생각을 해보았는데 몇몇 반례를 직접 손으로 풀면서 만들어보니 결국 [s, e]구간 전체에 대해서 고려해주어야 함을 알 수 있었다(즉, 전-탐색). 3.을 효율적으로 고려해주기 위해서 매 단계마다 m의 좌/우측 인접 fence 중 더 높은 높이를 갖는 fence 쪽으로 확장해가면서 직사각형의 넓이를 계산해주는 방법을 사용하였다. 이 방법은 greedy property를 증명할 때 자주 사용되는 기법을 통해 정당성을 증명할 수 있다.
> 어느 한 단계에서 좌/우측의 fence l, r 중 더 낮은 fence l 쪽으로 확장하여 직사각형의 최대 넒이 x를 얻었다고 하자.
> 만약, 그러한 단계에서 r 쪽으로 확장하고 다음 단계에서 l로 확장하더라도 x의 값은 변하지 않는다.

따라서, 문제를 1, 2, 3.으로 분할 정복하는 이 알고리즘은 T(n)=2*T(n/2) + n과 같이 복잡도를 기술할 수 있고 master theorem에 의해 T(n)=O(nlgn)임을 알 수 있다. 이는 제한 시간 내에 문제를 풀기에 충분한 시간복잡도이다. 구현과 관련해서 주의할 만한 사항으로는 주어진 구간 [s, e]에 대하여 3.의 과정에서 (-INF, s) 또는 (e, +INF) 범위의 fence를 고려하려고 하는 경우를 적절히 잘 예외 처리해주어야 하는 점이 있다. 구간 밖의 원소를 -INF로 하여 data guard를 두는 등 여러 방법이 있을 수 있지만 난 그냥 분기를 사용해서 처리했다.

```c_cpp

int solve(int s, int e)
{
    // base cases.
    if (s > e)
        return 0;
    if (s == e)
        return FENCES[s];

    // recursive step(divide in 3 cases).
    int m = (s + e) / 2;
    int lsub = solve(s, m - 1);
    int rsub = solve(m + 1, e);

    int l = m;
    int r = m;
    int h = FENCES[m];
    int msub = FENCES[m];

    while (s <= l && r <= e)
    {
        int lh = (l - 1 < s) ? 0 : FENCES[l - 1];
        int rh = (r + 1 > e) ? 0 : FENCES[r + 1];

        if (lh < rh)
        {
            ++r;
            h = min(h, rh);
            msub = max(msub, h * (r - l + 1));
        }
        else
        {
            --l;
            h = min(h, lh);
            msub = max(msub, h * (r - l + 1));
        }
    }

    return max(msub, max(lsub, rsub));
}


```

---

###문제ID : FANMEETING(AOJ_FANMEETING.cpp)

2017.01.14.(토).

문제를 보고 무엇인가 비트 열의 곱셉으로 문제를 풀면 되겠다는 감을 잡는데는 성공했지만 문제 풀이의 핵심이었던 Karatsuba를 떠올리는 데는 실패했다. Karatsuba 알고리즘을 응용하면 O(n^2) 알고리즘을 O(n^lg3) 알고리즘으로 개선할 수 있다. x명의 멤버를 M(1) ~ M(x)로, y명의 팬을 F(1) ~ F(y)로 표현하기로 하자. 멤버와 팬을 나타내는 문자열을 곱셈 세로식처럼 적어보면 다음과 같이 되는 것을 알 수 있다.

![mult](https://github.com/wonseokdjango/AOJ/blob/master/images/mult.png)

위의 세로식 곱셈을 보면 곱셈 결과의 x-1번째 자리부터 y-1번째 자리가 각각 한 번의 라운드에서 이뤄지는 악수 또는 허그의 조합을 나타내고 있는 것을 알 수 있다. 따라서 'M'을 1로, 'F'를 0으로 자리올림을 무시하여 세로식을 계산한다면 [x-1, y-1]구간의 0의 갯수가 곧 전체 포옹의 경우의 수를 나타내게 된다. 이때, '자리올림을 무시하여'라는 부분이 구현할 때 까다로울 수도 있는데 이는 단순하게 곱하는 숫자들이 모두 x진법의 수라고 생각하면 쉽게 구현할 수 있다. 세로식을 살펴보면 결과값의 각 자리수는 최대 x개 수의 합으로 만들어지고 우리가 곱하려는 수는 모두 0 또는 1이므로 x진법을 가정하면 자리올림이 발생하지 않는다.

이제 두 수의 곱에서 [x-1, y-1]구간의 0의 갯수가 전체 포옹의 경우의 수인 것을 알았으니 Karatsuba 알고리즘을 사용해서 두 수를 빠리게 곱하는 방법에 대해서 알아보자. 곱하기 원하는 두 수 a(y자리수)와 b(x자리수)가 주어졌다고 하자(y>=x라고 가정). a, b에 대해서 상위 하위 m자리수와 상위 y-m자리 수를 분리하여 표현하면 axb는 아래와 같이 표현될 수 있다(0<=m<=y).

a x b
> = (a1 x BASE^m + a0) x (b1 x BASE^m + b0)

> = a1 x b1 x BASE^2m + (a1 x  b0 + a0 x b1) x BASE^m + a0 x b0

BASE^m, BASE^2m 연산은 단순한 shift 연산이므로 곱셈으로 치지 않는다면, 위의 곱셈에는 총 4회의 곱셈이 필요하게 된다. Karatsuba는 여기서 필요한 곱셈의 횟수를 3회로 줄이는데 (a1 x b0 + a0 x b1) = (a0 + a1) x (b0 + b1) - a1 x b1 - a0 x b0임을 사용한다. 매 단계 m의 값을 자리수의 절반(오차1)로 설정한다면 계산의 복잡도는 T(n) = 3T(n/2) + cn과 같이 표현된다. 여기서 cn항은 절반에 가깝게 나눈 수들의 덧셈 및 뺄셈에 소비되는 계산량을 의미한다. 역시, master 정리를 활용해보면 계산의 복잡도가 O(n^lg3)이 되는 것을 확인할 수 있다.

```c_cpp

vector<int> dq(const vector<int>& a, const vector<int>& b)
{
    int asize = a.size();
    int bsize = b.size();

    // base case.
    if (asize == 0 || bsize == 0)
        return vector<int>();
    if (asize < bsize)
        return dq(b, a);
    if (asize <= THRESHOLD)
        return bf(a, b);

    // recursive step.
    int m = asize / 2;
    vector<int> a0(a.begin(), a.begin() + m);
    vector<int> a1(a.begin() + m, a.end());
    vector<int> b0(b.begin(), b.begin() + min<int>(b.size(), m));
    vector<int> b1(b.begin() + min<int>(b.size(), m), b.end());

    vector<int> z0 = dq(a0, b0);
    vector<int> z2 = dq(a1, b1);

    add(a0, a1, 0);
    add(b0, b1, 0);
    vector<int> z1 = dq(a0, b0);
    sub(z1, z0, 0);
    sub(z1, z2, 0);

    vector<int> ret;
    add(ret, z0, 0);
    add(ret, z1, m);
    add(ret, z2, m + m);

    return ret;
}


```

---

###문제ID : WILDCARD(AOJ_WILDCARD.cpp)

2017.02.05.(일).

푼지 꽤 됬는데, 그 동안 README를 업데이트를 못해서 한 번에 업데이트 한다. 이 문제를 알기 쉽고 명확하게 표현해보면 다음과 같다.


> WILDCARD를 포함하는 패턴을 나타내는 pattern[0...n], 일치 여부를 알고 싶은 문자열 str[0...m]이 주어질 때, str[0...m]이 pattern[0...n]으로 표현가능한 문자열인지의 여부를 true or false로 구하라.


간단하게 DP를 적용해서 문제를 풀 수 있는데, 문제를 풀기 위해서 부분문제를 아래와 같이 정의하자.

> SUB[i][j] := **pattern[i...n]**과 **str[j...m]**이 매칭이 가능한지의 여부. true or false.

위와 같이 정의된 부분문제 SUB[i][j]를 풀기 위한  base case와 recursive step을 표현해 보면 아래와 같다.

SUB[i][j] =
> base case 1) **i == n인 경우**, 
>> 더 이상 대응 시킬 pattern이 없는 상태이므로 j == m(즉, str도 모두 소비)인 경우에만 true, 아닌 경우 false.

> base case 2) **j == m인 경우**,
>> 더 이상 소비할 str이 없는 상태이므로 pattern[i...n]이 모두 '*'만 포함하고 있거나 i == n(즉, pattern도 모두 소비)인 경우에만 true, 아닌 경우 false.

> recursive step 1) **pattern[i] != '*' && pattern[i] != '?'인 경우,**
>> pattern[i] != str[j]인 경우 false, 아닌 경우 SUB[i + 1][j + 1].

> recursive step 2) **pattern[i] == '*'인 경우,**
>> j + 1 <= idx <=m 인 idx에 대하여 SUB[i + 1][idx]가 모두 false인 경우에만 false, 아닌 경우 true.

> recursive step 3) **pattern[i] == '?'인 경우**
>> SUB[i + 1][j + 1].

```c_cpp

char solve(int wIdx, int nIdx)
{
    // base cases.
    if (wIdx == WILD.size())
        return (nIdx == NAME.size()) ? TRUE : FALSE;
    if (nIdx == NAME.size())
    {   
        int idx;
        for (idx = wIdx; idx < WILD.size() && WILD[idx] == '*'; ++idx);

        return (idx == WILD.size()) ? TRUE : FALSE;
    }   

    // dp step.
    char& ret = CACHE[wIdx][nIdx];
    if (ret == 0)
    {   
        // dp.
        if (WILD[wIdx] == '?')
            ret = solve(wIdx + 1, nIdx + 1); 
        else if (WILD[wIdx] == '*')
        {
            ret = FALSE;
            for (int rep = 0; rep <= NAME.size() - nIdx; ++rep)
            {
                if (solve(wIdx + 1, nIdx + rep) == TRUE)
                {
                    ret = TRUE;
                    break;
                }
            }
        }
        else
            ret = (WILD[wIdx] == NAME[nIdx] && solve(wIdx + 1, nIdx + 1) == TRUE) ? TRUE : FALSE;
    }   

    return ret;
}


```

---

###문제ID : TRIANGLEPATH(AOJ_TRIANGLE.cpp)

2017.02.05.(일).

굳이 README를 적을 필요가 느껴지지 않을 정도로 쉬운 DP문제에 속한다. 다만, 문제를 풀 때 부분문제의 정의를 어떻게 하냐에 따라서 문제를 푸는 과정이 간단해 질 수도, 복잡해 질 수도 있다는 사실을 알아두기 위해서는 도움이 되는 문제이다. 이 문제 같은 경우 부분문제의 정의를 아래의 두 가지 방법으로 해 볼 수 있다.

> 방법1. **SUB[i][j]** := arr[i][j]에서 시작하는 TRIANGLEPATH의 최대 합.

> 방법2. **SUB[i][j]** := arr[i][j]에서 종료하는 TRIANGLEPATH의 최대 합.

만약, 이 문제를 푸는데 방법2.의 접근을 사용한다면 모든 부분문제를 풀어낸 후 삼각형의 밑변에 위치하는 원소들에 대해서 최대 값을 갖는 위치를 루프를 돌며 찾아주어야 할 것이다. 반면, 방법1.을 사용하여 문제를 푼다면 모든 부분문제를 풀어낸 후 단지 삼각형의 윗 꼭지점에 위치한 원소의 값이 곧 답이 될 것이다(모든 TRIANGLEPATH는 반드시 그 위치에서 시작하므로). 방법1.을 사용하여 문제를 풀 때, base case와 recursive step은 아래와 같다(삼각형의 높이를 h라고 하자).

SUB[i][j] :=
> base case) **i == h - 1**인 경우,
>> 더 이상 가능한 TRIANGLEPATH가 없으므로 arr[i][j]의 값과 같다.
> recursive step) **i != h - 1**인 경우,
>> arr[i][j]부터 시작되는 두 TRIANGLEPATH에 대해서 더 큰 쪽을 답으로 한다. 즉, arr[i][j] + max(SUB[i+1][j], SUB[i+1][j+1]).

```c_cpp

for (int h = H - 2; h >= 0; --h)
{
    for (int idx = 0; idx < h + 1; ++idx)
        TRIANGLE[h][idx] += MAXVAL(TRIANGLE[h + 1][idx], TRIANGLE[h + 1][idx + 1]);
}

```

---

###문제ID : LIS(AOJ_LIS.cpp)

2017.02.05.(일).

아주 유명한 DP문제로 쉽게 풀 수 있다. DP해법 이외에도 O(nlgn)짜리 솔루션이 알려져 있다. 이 풀이는 DP풀이 방법을 보인다. 부분 문제의 정의를 아래와 같이 설정한다.

> SUB[i] := arr[i]에서 끝나는 LIS중 최대의 길이.

위의 정의에 해당하는 모든 부분문제를 풀어주고 arr의 모든 원소에 대해 SUB의 최대 값을 찾아주면 답이 된다. SUB[i]를 풀기 위한 base case와 recursive step은 아래와 같다(arr의 길이를 len이라고 가정한다).

SUB[i] =
> base case) **i == 0**인 경우,
>> LIS를 더 이상 만들어 나갈 수 없으므로 최대 길이를 갖는 LIS는 {arr[0]}이다. 따라서, SUB[i] = 1.
> recursive step) **i != 0**인 경우,
>> 0 <= idx < i인 idx에 대해서 SUB[i] = 1 + max(SUB[idx])이다. 즉, 가장 긴 LIS의 뒤에 자기 자신을 추가한다.

```c_cpp

// solve.
for (int cur = 0; cur < N; ++cur)
{
    CACHE[cur] = 1;
    for (int pre = cur - 1; pre >= 0; --pre)
    {
        if (NUMBERS[pre] < NUMBERS[cur])
            CACHE[cur] = MAXVAL(CACHE[cur], CACHE[pre] + 1); 
    }
}

```

---

###문제ID : JLIS(AOJ_JLIS.cpp)

2017.02.05.(일).

LIS에서 조금의 변형을 가한 문제에 불과했는데, base case 설정을 잘못해서 푸는데 애를 먹었다. 이 문제의 부분문제 정의를 아래와 같이 하였다(A의 길이를 n, B의 길이를 m이라고 하자).

> SUB[i][j] := A[i], B[j]에서 시작하는 JLIS중 최대의 길이를 갖는 JLIS의 길이.

여기서, "A[i], B[j]로 시작하는"의 의미는 JLIS에 포함된 원소 중 A에 속하는 모든 원소는 A[i...n-1]에서만 등장할 수 있고, B에 속하는 모든 원소는 B[j...m-1]에서만 등장할 수 있다는 의미이다. 이를 바탕으로 SUB[i][j]를 풀기 위해서 경우의 수를 떠올려보면 아래와 같은 경우가 있을 것이다.

**case1.** A[i] ... B[j] ...

**case2.** B[j] ... A[i] ...

**case3.** (A[i] == B[j]) ...

위에서 보인 각각의 경우를 염두에 두고, SUB[i][j]를 풀기 위한 base case와 recursive step을 보이면 아래와 같다.

> base case1) **i == n**인 경우,
>> SUB[i][j]는 B의 원소만을 사용하여 만들어지는 LIS의 길이와 같다.

> base case2) **j == m**인 경우,
>> SUB[i][j]는 A의 원소만을 사용하여 만들어지는 LIS의 길이와 같다.

> recursive step1) **A[i] < B[j]**인 경우(case1.에 해당),
>> i < ni <= n, A[i] < A[ni]인 ni에 대해서 SUB[i][j] = 1 + max(SUB[ni][j])

> recursive step2) **A[i] > B[j]**인 경우(case2.에 해당),
>> j < nj <= m, B[j] < B[nj]인 nj에 대하여 SUB[i][j] = 1 + max(SUB[i][nj])

> recursive step3) **A[i] == B[j]**인 경우(case3.에 해당),
>> i < ni <= n, A[i] < A[ni], j < nj <= m, B[j] < B[nj]인 ni, nj에 대하여 SUB[i][j] = 1 + max(SUB[i+1][j+1])

사실 문제를 처음 풀 때, "SUB[i][j] := A[i], B[j]로 끝나는 JLIS중 최대의 길이를 갖는 JLIS의 길이"로 정의했었는데, 이 경우에도 문제를 풀 수는 있다. 이 때, 끝까지 깨닫지 못했던 것은 base case1, 2 였는데 어디에선가 반드시 A 또는 B만을 사용하여 LIS를 풀어어야 한다는 것을 캐치하지 못해 문제를 풀지 못 했었다. 앞으로는 base case를 설정할 때 주의하도록 해야겠다.

```c_cpp

// padding.
A[N] = B[M] = MAXNUM;

for (int i = N - 1; i >= 0; --i)
{
    CACHE[i][M] = 1;
    for (int ni = i + 1; ni < N; ++ni)
    {
        if (A[i] < A[ni])
            MAX_UPDATE(CACHE[i][M], 1 + CACHE[ni][M]);
    }
}
for (int j = M - 1; j >= 0; --j)
{
    CACHE[N][j] = 1;
    for (int nj = j + 1; nj < M; ++nj)
    {
        if (B[j] < B[nj])
            MAX_UPDATE(CACHE[N][j], 1 + CACHE[N][nj]);
    }
}
CACHE[N][M] = 0;

// solve.
for (int i = N - 1; i >= 0; --i)
{
    for (int j = M - 1; j >= 0; --j)
    {
        CACHE[i][j] = (A[i] == B[j]) ? 1 : 2;
        if (A[i] < B[j])
        {
            for (int ni = i + 1; ni <= N; ++ni)
            {
                if (A[i] < A[ni])
                    MAX_UPDATE(CACHE[i][j], 1 + CACHE[ni][j]);
            }
        }
        else if (A[i] > B[j])
        {
            for (int nj = j + 1; nj <= M; ++nj)
            {
                if (B[j] < B[nj])
                    MAX_UPDATE(CACHE[i][j], 1 + CACHE[i][nj]);
            }
        }
        else
        {
            for (int ni = i + 1; ni <= N; ++ni)
            {
                for (int nj = j + 1; nj <= M; ++nj)
                {
                    if (A[i] < A[ni] && B[j] < B[nj])
                        MAX_UPDATE(CACHE[i][j], 1 + CACHE[ni][nj]);
                }
            }
        }
    }
}


```

---

###문제ID : PI(AOJ_PI.cpp)

2017.02.06.(월).

전형적인 DP문제로 쉽게 풀 수 있다. 굳이 까다로운 점을 찾아보자면 문자열의 연속한 3~5자리 형태에 따라 난이도가 결정되는 부분인데 이는 아래의 사실을 깨닫으면 쉽게 극복할 수 있다. 

> 문자열을 3~5자리로 끊어 읽는 경우만 생각한다. 8자리 숫자가 있을 때 3/3/2와 같이 끊어 읽는 것은 불가능하다.

problem description에 몇 줄 더 적혀있으면 문제를 푸는 사람들이 혼란 없이 풀 수 있을 듯한데 문제의 출처가 CF라고하니 참고 넘어가는 수 밖에 없을 듯 하다.

주어진 숫자를 PI, PI의 길이를 n이라고 할 때, 문제를 풀기 위한 부분 문제의 정의는 아래와 같다.

> SUB[i] := PI[i...n - 1]을 외우기 위한 최소 난이도.

정의된 부분 문제를 풀기 위한 base case, recursive step은 아래와 같다.

> base case1) **i == n**인 경우,

>> 외울 숫자가 더 이상 없는 경우이므로 SUB[i] = 0.

> base case2) **i == n - 1 또는 i == n - 2**인 경우,

>> 위에서 밝혔듯 모든 숫자는 3~5자리로 끊어서 일어야만 한다. 따라서, base case2와 같이 한 글자 또는 두 글자를 외우는 것은 불가능한 경우이다. 이와 같은 경우가 답에 포함되지 않도록 SUB[i] = +INF로 한다.

> recursive step) **0 <= i < n - 1**인 경우,

>> PI[pos...pos + group - 1]로 표현되는 group(3 <= group <= 5)개의 숫자를 외우기 위한 난이도를 dif(pos, group)라고 하자. 이 때, SUB[i]는 아래와 같이 표현될 수 있다. 이 때, array bound를 체크해주어야 하는 것에 주의 한다.

>>> SUB[i] = min(CACHE[i + group] + dif(i, group));

```c_cpp

// base case.
CACHE[PI.length()] = 0;
CACHE[PI.length() - 1] = 10 * MAXLEN;
CACHE[PI.length() - 2] = 10 * MAXLEN;

// recursive step.
for (int idx = PI.length() - 3; idx >= 0; --idx)
{
    for (int group = 3; idx + group - 1 < PI.length() && group <= 5; ++group)
        CACHE[idx] = min(CACHE[idx], CACHE[idx + group] + difficulty(idx, group));
}

cout << CACHE[0] << endl;

```

---

###문제ID : QUANTIZE(AOJ_QUANTIZE.cpp)

2017.02.09.(목).

오랜 시간이 걸리지 않고 풀 수는 있지만 막상 풀고나서 설명하려하면 꽤나 애를 먹이는 문제이다. 간혹, DP문제인 것을 알고 풀이를 시작하더라도 부분문제 관계식을 찾는 것이 어려운 경우가 있는데 이런 경우에는 항상 기본으로 돌아가서 brute-force 솔루션을 생각해보도록 하자 (주어진 수열을 정렬하여 ***a[1], a[2], ... ,a[n]***를 얻었다고 하고, 이 수열을 S개의 양자화 값 ***q[1], q[2], ... ,q[S]***로 양자화하는 코드를 생각해보면 아래 DP풀이가 당연하게 느껴짐)

이 문제를 풀기 위한 부분문제의 정의는 아래와 같다. 주어진 수열을 정렬하여 ***a[1], a[2], ... ,a[n]***을 얻었다고 가정하자.

> SUB[f][q] := a[**f**...n]을 **q**개의 양자 값을 사용하여 양자화 할 때 오차 제곱의 최소 합.

위와 같이 부분 문제를 정의하면 아래와 같이 base case와 recursive step을 도출할 수 있다.

> base case1) **f >= n + 1**인 경우,
>> 더 이상 양자화 해야할 값이 없으므로 오차는 0이다.

> base case2) **f < n + 1**이고 **q <= 0**인 경우,
>> 양자화 해야할 값은 남아 있지만 양자화에 사용할 수 있는 값이 남아있지 않으므로 +INF.

> recursive step) **f < n + 1** 이고 **q > 0**인 경우,
>> SUB[f][q] := min(***sq_error(f, len)*** + SUB[f + len][q - 1])

위의 recursive step에서 ***sq_error(f, len)***이 등장하는데 이는 "a[f...f + len - 1]을 하나의 값을 사용하여 양자화 할 때, 오차 제곱의 최소 합"으로 정의된다. 이 값을 구하는 것은 어렵지 않은데, 하나의 양자화에 사용되는 값에 대하여 주어진 구간의 오차의 제곱 합을 구하는 공식을 살펴보면 이를 확인할 수 있다.

f(s, e, q) := a[s...e]를 q를 사용하여 양자화 할 때 오차의 제곱의 합

>= f(s, e, q)

> = (a[s] - q)^2 + (a[s + 1] - q)^2 + ... + (a[e] - q)^2

> = a[s]^2 + a[s + 1]^2 + ... + a[e]^2 + (e - s + 1)q^2 - 2q(a[s] + a[s + 1] + ... + a[e])

f(s, e, q)를 q에 대해 미분하여 f(s, e, q)가 최소 값을 갖는 지점을 구해보면 q = avg(a[s...e])임을 알 수 있다. 즉, ***sq_error(f, len)***은 a[f...f + len - 1]을 a[f...f + len - 1]의 평균값을 사용하여 양자화 하였을 때 얻어지는 오차의 제곱합과 같다. 이때, 문제에서 요구하는 S개의 양자화에 사용되는 값은 모두 정수이므로 양자화에 사용될 q를 반올림하여 정수로 사용해야 함에 주의한다.

```c_cpp

// init.
for (int row = 0; row < MAX_N + 1; ++row)
{
    for (int col = 0; col < MAX_Q + 1; ++col)
        CACHE[row][col] = MAX_VAL;
}
for (int row = 0; row < MAX_N + 1; ++row)
    CACHE[row][0] = MAX_VAL;
for (int col = 0; col < MAX_Q + 1; ++col)
    CACHE[N][col] = 0;

// sort.
sort(ARR, ARR + N);

// solve.
for (int f = N - 1; f >= 0; --f)
{
    for (int q = 1; q <= S; ++q)
    {
        int sum = ARR[f];
        int sqr = ARR[f] * ARR[f];

        for (int len = 1; f + len - 1 < N; ++len)
        {
            int avg = (int)((double)sum / len + 0.5);
            int var = sqr - 2 * avg * sum + len * avg * avg;

            MIN_UPDATE(CACHE[f][q], var + CACHE[f + len][q - 1]);

            sum += ARR[f + len];
            sqr += ARR[f + len] * ARR[f + len];
        }
    }
}

```

---

###문제ID : TILING2(AOJ_TILING2.cpp)

2017.02.09.(목).

매우 쉬운 문제로 DP의 대표적인 문제이나, 사실 피보나치 수열을 구하는 것과 다름 없어 DP를 쓸 필요도 없다.
아래 그림과 같이 타일의 n번째 위치에서 하나의 세로 타일로 끝나거나, 두개의 가로 타일로 끝나는 경우 외에는 다른 경우가 존재하지 않으므로 아주 간단하게 아래의 점화식을 얻을 수 있다.

![tile](https://github.com/wonseokdjango/AOJ/blob/master/images/tile.png)

> SUB[i] := 2xi 타일을 채우는 경우의 수

> SUB[i] = SUB[i - 1] + SUB[i - 2]

```c_cpp

int fibo(int n)
{
    if (n == 1)
        return 1;
    if (n == 2)
        return 2;

    int p = 2;
    int pp = 1;
    int cur = p + pp;

    for (int i = 3; i < n; ++i)
    {
        pp = p;
        p = cur;
        cur = (p + pp) % MOD;
    }

    return cur;
}

```

---

###문제ID : TRIPATHCNT(AOJ_TRIPATHCNT.cpp)

2017.02.09.(목).

이 리포지토리에 있는 TRIANGLEPATH와 거의 일치하는 문제이다. 경로의 최대값을 구하는 방법은 TRIANGLEPATH와 100% 일치하며, 이 과정에서 아래와 같이 부분문제 하나를 더 풀어준다. h가 트리의 높이를 나타낸다고 하자.

> SUB2[i][j] := TRIANGLE[i][j]에서 시작하는 최대 TRIANGLEPATH의 갯수.

> base case) **i == h - 1**인 경우,

>> 최대의 TRIANGLEPATH가 단, 하나의 원소로 구성되고 유일하므로 SUB2[i][j] = 1.

> recursive step) **0 <= i < h - 1**인 경우,

>> subcase1) **SUB[i + 1][j] > SUB[i + 1][j + 1]**인 경우,

>>> 바로 아래 있는 원소를 이용해야만 최대의 경로를 얻을 수 있으므로 SUB2[i][j] = SUB2[i + 1][j]

>> subcase2) **SUB[i + 1][j] < SUB[i + 1][j + 1]**인 경우,

>>> 우측 아래 있는 원소를 이용해야만 최대의 경로를 얻을 수 있으므로 SUB2[i][j] = SUB2[i + 1][j + 1]

>> subcase3) **SUB[i + 1][j] == SUB[i + 1][j + 1]**인 경우,

>>> 바로 아래, 우측 아래 있는 원소 중 어떤 것을 사용해도 항상 최대 경로를 얻을 수 있으므로 SUB2[i][j] = SUB2[i + 1][j] +SUB2[i + 1][j + 1].

```c_cpp

// solve.
for (int h = N - 2; h >= 0; --h)
{
    for (int pos = 0; pos < h + 1; ++pos)
    {
        if (PATHSUM[h + 1][pos] > PATHSUM[h + 1][pos + 1])
        {
            PATHSUM[h][pos] = TRIANGLE[h][pos] + PATHSUM[h + 1][pos];
            PATHCNT[h][pos] = PATHCNT[h + 1][pos];
        }
        else if (PATHSUM[h + 1][pos] < PATHSUM[h + 1][pos + 1])
        {
            PATHSUM[h][pos] = TRIANGLE[h][pos] + PATHSUM[h + 1][pos + 1];
            PATHCNT[h][pos] = PATHCNT[h + 1][pos + 1];
        }
        else
        {
            PATHSUM[h][pos] = TRIANGLE[h][pos] + PATHSUM[h + 1][pos];
            PATHCNT[h][pos] = PATHCNT[h + 1][pos] + PATHCNT[h + 1][pos + 1];
        }
    }
}


```

---

###문제ID : SNAIL(AOJ_SNAIL.cpp)

2017.02.27.(월).

쉽게 해결할 수 있는 쳔에 속하는 문제로 부분문제만 잘 정의해주면 간단히 해결할 수 있다. 문제를 풀기 위한 부분문제의 정의는 아래와 같다.

> SUB[i][j] := i일에 달팽이가 j 미터 이상에 도달했을 확률

위의 부분문제 정의에 맞추어 기저사례와 재귀사례에 대한 점화식을 세우면 아래와 같다.

> base case 1) **j == 0**인 경우,
 
>> 항상 0 미터에는 도달이 가능하므로 SUB[i][j] = 1.0

> base case 2) **j == 1이고 i != 0**인 경우,

>> 비가 오건 안오건 상관 없이 i > 0일 만에 1미터에 도달하는 것은 항상 가능하므로 SUB[i][j] = 1.0

> base case 3) **j != 0 이고 i == 0**인 경우,

>> 0일 만에 j > 0 미터에 도달하는 것은 불가능므로 SUB[i][j] = 0.0

> recursive step)

>> i일 만에 j미터 이상에 도달하는 경우는 'i - 1일에 정확히 j - 1미터 이상에 도달하고 비가 오거나 오지 않은 경우', 'i - 1일에 정확히 j - 2미터에 도달하고 비가 온 경우'로 나누어 볼 수 있다. 아래의 식은 이와 같은 과정을 보인다. 전자의 경우 'j - 1미터 이상'을 그대로 사용하고 후자의 경우 '정확히 j - 2미터'로 바꾸어 문제를 푸는 이유는 각 부분문제가 겹치는 부분을 포함하지 않도록하디 위함임에 주의한다. 

> SUB[i][j] = SUB[i - 1][j - 1] + 0.75 * (SUB[i - 1][j - 2] - SUB[i - 1][j - 1])

```c_cpp

for (int day = 1; day <= DAY; ++day)
{
    for (int h = 2; h <= H; ++h)
    {
        CACHE[day][h] = 0.25 * CACHE[day - 1][h - 1] + 0.75 * CACHE[day - 1][h - 2];
    }
}

```

---

###문제ID : ASYMTILING(AOJ_ASYMTILING.cpp)

2017.02.28.(월).

이 리포지토리에서 다루는 TILING2문제와 크게 다른 점은 없다. 단지, TILING2 문제를 풀어준 후에 부분문제들을 가지고 대칭 타일링의 경우의 수를 빼주어야 한다는 점만이 다르다. 2 * n(n > 4) 너비의 사각형을 채우기 위한 비대칭 타일링의 수는 아래와 같이 서브 케이스를 나누어 경우의 수를 제하여 줌으로써 계산될 수 있다.

> case 1 ) n 이 짝수인 경우

> ![tile](https://github.com/wonseokdjango/AOJ/blob/master/images/asym_even.png)

> case 2 ) n 이 홀수인 경우

> ![tile](https://github.com/wonseokdjango/AOJ/blob/master/images/asym_odd.png)

```c_cpp

u64t ans = 0;

if (1 == N)
    ans = 0;
else if (2 == N)
    ans = 0;
else if (3 == N)
    ans = 2;
else if (4 == N)
    ans = 2;
else if (0 == N % 2)
{
    ans += fibo(N);
    ans += 2 * MOD;
    ans -= 2 * fibo((N - 2) / 2);
    ans %= MOD;
    ans += MOD;
    ans -= fibo((N - 4) / 2);
    ans %= MOD;
}
else
{
    ans += fibo(N);
    ans += MOD;
    ans -= fibo((N - 1) / 2);
    ans %= MOD;
}

```

---

###문제ID : POLY(AOJ_POLY.cpp)

2017.03.02.(목).

점화식을 구하기가 조금은 까다롭게 느껴질 수 있는 문제이지만, 부분문제를 영리하게 정의하면 쉽고 빠르게 풀 수 있다. n개의 정사작형으로 만들 수 있는 각각의 폴리오미노를 최상단에 위치하는 정사각형의 갯수로 분리할 수 있는데, n이 2인 경우, 3인 경우에 대해서 예를 들어보면 아래의 그림과 같다.

![poly](https://github.com/wonseokdjango/AOJ/blob/master/images/poly.png)

n = 3인 경우를 잘 살펴보면, 3개 정사각형으로 만들 수 있는 최상단에 **top(1 <= top <= 2)**개 정사각형이 존재하는 폴리오미노는 **3 - top**개 정사각형으로 만들 수 있는 최상단에 **under(1 <= under <= 3 - top)**개 정사각형이 위치하는 폴리오미노 상단에 **top**개의 정사각형을 올려놓는 것으로 만들 수 있는 것을 알 수 있다(적색으로 표시한 부분을 살펴보면). 여기에 마지막으로 최상단에 3개의 정사각형이 위치하는 일직선 모양의 폴리오미노를 더해준다면 우리는 3개 정사각형으로 만들 수 있는 모든 폴리오미노를 구할 수 있다.

이 과정을 수식으로 나타내기 위해서 부분문제를 아래와 같이 정의하자.

> SUB[total][top] := total개 정사각형으로 만들 수 있는 최상단에 top개 정사각형이 위치하는 폴리오미노의 수

위의 부분문제에 따라 기저사례와 재귀사례를 정의해주면 아래와 같다.

> base case 1) **total < top**인 경우.

>> 총 정사각형의 수보다 많은 수의 정사각형이 최상단에 위치할 수는 없으므로 SUB[total][top] = 0.

> base case 2) **total == top**인 경우,

>> total개 정사각형을 사용할 때, 최상단에 total개 정사각형이 위치하는 폴리오미노는 일직선 모양의 폴리오미노 뿐이다. 따라서, SUB[total][top] = 1.

> recursive step) **total > top**인 경우,

>> top개의 정사각형을 total - top개의 정사각형으로 만들어지는 최상단에 under개가 위치하는 폴리오미노의 위에 올려 놓으면 된다. top개 정사각형을 under개 정사각형 위에 올려놓을 수 있는 방법의 수는 top + under - 1개 이므로 아래와 같이 식을 얻을 수 있다.

>> SUB[total][top] = sum{(top + under - 1) * SUB[total - top][under]}, 1 <= under < top

빠른 풀이를 위해 테스트 케이스의 최대 크기에 대해 모든 부분문제를 다 풀어 놓은 뒤 각 테스트 케이스에서 SUB[total][0] + SUB[total][1] + ... + SUB[total][total]을 구해준다면 좀 더 효율적인 구현이 가능하다.

```c_cpp

// pre-processing.
for (int total = 1; total <= MAXN; ++total)
{
    for (int top = 1; top < total; ++top)
    {
        CACHE[total][top] = 0;
        for (int under = 1; under <= total - top; ++under)
        {
            CACHE[total][top] += (top + under - 1) * CACHE[total - top][under];
            CACHE[total][top] %= MOD;
        }
    }
    CACHE[total][total] = 1;
}

// solve.
scanf(" %d", &N);
int ans = 0;
for (int top = 1; top <= N; ++top)
    ans = (ans + CACHE[N][top]) % MOD;

```

---