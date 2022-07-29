#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
using namespace std;

typedef pair<int, int> pii;
#define ll long long

int N, M, Q;
ll bit[100010];
void update(int i, int v)
{
    while (i <= N)
    {
        bit[i] += v;
        i += (i & -i);
    }
}
ll query(int i)
{
    ll sum = 0;
    while (i > 0)
    {
        sum += bit[i];
        i -= (i & -i);
    }
    return sum;
}

struct Query
{
    ll t, x, y, v;
};

bool Comp(const Query& q1, const Query& q2)
{
    return pii(q1.x * -1, q1.t) < pii(q2.x * -1, q2.t);
}

int arr[100010];
ll ans[100010];
set<int> occ[100010];
int cnt = 0;
Query qs[700010];
Query influence[700010];

void solve(int l, int r)
{
    if (l == r) return;
    int mid = (l + r) / 2;

    solve(l, mid);
    solve(mid + 1, r);

    int use = 0;
    for (int i = l; i <= mid; i++) 
        if (qs[i].t == 1) influence[++use] = qs[i];
    for (int i = mid + 1; i <= r; i++)
        if (qs[i].t == 2) influence[++use] = qs[i];

    sort(influence + 1, influence + use + 1, Comp);

    for (int i = 1; i <= use; i++)
    {
        if (influence[i].t == 1) update(influence[i].y, influence[i].v);
        else ans[influence[i].v] += query(influence[i].y);
    }
    
    for (int i = 1; i <= use; i++)
        if (influence[i].t == 1) update(influence[i].y, influence[i].v * -1);
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N >> M;
    for (int i = 1; i <= N; i++) occ[i].insert(0);
    for (int i = 1; i <= N; i++) 
    {
        cin >> arr[i];
        auto it = occ[arr[i]].rbegin();
        if (occ[arr[i]].size() > 1) qs[++cnt] = {1, *it, i, i - *it};
        occ[arr[i]].insert(i);
    }
    for (int i = 1; i <= N; i++) occ[i].insert(N + 1);

    for (int i = 1; i <= M; i++) 
    {
        int t, n1, n2;
        cin >> t >> n1 >> n2;
        if (t == 1)
        {
            auto it = occ[arr[n1]].lower_bound(n1);
            auto l = --it;
            auto r = ++++it;
            --it;
            
            qs[++cnt] = {1, *l, *it, *l - *it};
            qs[++cnt] = {1, *it, *r, *it - *r};
            qs[++cnt] = {1, *l, *r, *r - *l};
            occ[arr[n1]].erase(it);
            arr[n1] = n2;

            r = occ[n2].lower_bound(n1);
            l = --r;
            r++;

            qs[++cnt] = {1, *l, n1, n1 - *l};
            qs[++cnt] = {1, n1, *r, *r - n1};
            qs[++cnt] = {1, *l, *r, *l - *r};
            occ[n2].insert(n1);
        }
        else
            qs[++cnt] = {2, n1, n2, ++Q};
    }
    solve(1, cnt);

    for (int i = 1; i <= Q; i++)
        cout << ans[i] << endl;
    return 0;
}