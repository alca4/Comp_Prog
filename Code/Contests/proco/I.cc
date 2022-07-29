#include<iostream>
#include<algorithm>
#include<map>
using namespace std;

int N;
int rocks[100000];
map<int, int> memo[100000];

int DP(int cur, int speed)
{
    if (memo[cur].find(speed) != memo[cur].end()) return memo[cur][speed];
    //cout << cur << endl;
    if (cur == N - 1) return 0;
    int next = cur + 1;
    while (next < N && rocks[next] < rocks[cur] + speed - 2) next++;
    int ans = 1e9;
    while (next < N && rocks[next] >= rocks[cur] + speed - 2)
    {
        if (rocks[next] > rocks[cur] + speed + 2) return min(ans, 1000000000);
        if (rocks[next] - rocks[cur] != speed) 
            ans = min(DP(next, rocks[next] - rocks[cur]) + 1, ans);
        next++;
    }
    memo[cur][speed] = ans;
    return ans;
}

int main()
{
    scanf("%d", &N);
    for (int i = 0; i < N; i++) scanf("%d", &rocks[i]);
    sort(rocks, rocks + N);
    int best = 1e9;
    for (int i = 1; i < N; i++)
    {
        if (rocks[i] > 3) break;
        best = min(DP(i, rocks[i]) + 1, best);
        //cout << "best is " << best << " when trying from " << i << endl;
    }
    if (best == 1e9) best = -1;
    cout << best << endl;
    return 0;
}