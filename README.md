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