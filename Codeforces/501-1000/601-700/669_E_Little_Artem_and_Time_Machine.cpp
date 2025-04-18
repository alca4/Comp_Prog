/*
Idea: CDQ
Straightforward application
solve for the queries entirely for the left and right, 
then solve for ones which go to both sidees
*/
#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
using namespace std;

struct Query
{
    int id;
    int t;
    int time;
    int v;
};

bool CompTm(const Query& q1, const Query& q2)
{
    return q1.time < q2.time;
}

bool CompT(const Query& q1, const Query& q2)
{
    return q1.id < q2.id;
}

int N;
Query qs[100010];
int ans[100010];
map<int, int> cnt;

void solve(int l, int r)
{
    if (l == r) return;

    int mid = (l + r) / 2;
    solve(l, mid);
    solve(mid + 1, r);

    sort(qs + l, qs + mid + 1, CompTm);
    sort(qs + mid + 2, qs + r + 1, CompTm);

    int tl = l;
    int tr = mid + 1;
    while (tl <= mid && tr <= r)
    {
        if (qs[tl].time < qs[tr].time)
        {
            if (qs[tl].t == 1) cnt[qs[tl].v]++;
            if (qs[tl].t == 2) cnt[qs[tl].v]--;
            tl++;
        }
        else
        {
            if (qs[tr].t == 3) ans[qs[tr].id] += cnt[qs[tr].v];
            tr++;
        }
    }
    while (tr <= r) 
    {
        if (qs[tr].t == 3) ans[qs[tr].id] += cnt[qs[tr].v];
        tr++;
    }
    for (int i = l; i < tl; i++)
    {
        if (qs[i].t == 1) cnt[qs[i].v]--;
        if (qs[i].t == 2) cnt[qs[i].v]++;
    }
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N;
    for (int i = 1; i <= N; i++) 
        cin >> qs[i].t >> qs[i].time >> qs[i].v;
    for (int i = 1; i <= N; i++) qs[i].id = i;
    solve(1, N);

    sort(qs + 1, qs + N + 1, CompT);
    for (int i = 1; i <= N; i++)
        if (qs[i].t == 3) cout << ans[i] << endl;
    
    return 0;
}