/*
  ___
 (o,o)
<  .  >
--"-"---
Rowlet is orz
*/
#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
#include <set>
#include <map>
#include <deque>
#include <queue>
#include <stack>
#include <unordered_set>
#include <unordered_map>
#include <bitset>
#include <cstring>
#include <cassert>
using namespace std;

#define F first
#define S second
#define pb push_back
#define ll long long
#define ld long double
#define INF 1000000000ull
#define MOD 1000000007ull
#define reset(x) memset(x, 0, sizeof(x))
#define all(x) (x).begin(), (x).end()
#define range(x, y, z) (x) + (y), (x) + (y) + (z)

typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

int read()
{
    int a;
    cin >> a;
    return a;
}

const int MAXN = 300010;
int N, M, P;
vector<int> owns[MAXN];
ll target[MAXN];
struct Event
{
    int s, e;
    ll v;
} showers[MAXN];

struct FT
{
    ll ft[MAXN];

    void update(int a, ll v)
    {
        while (a <= M)
        {
            ft[a] += v;
            a += (a & -a);
        }
    }

    ll query(int a)
    {
        ll sum = 0;
        while (a >= 1)
        {
            sum += ft[a];
            a -= (a & -a);
        }
        return sum;
    }
};

FT cur;

int ans[MAXN];
void process(int i, int sign)
{
    int a = showers[i].s, b = showers[i].e;
    ll v = showers[i].v * sign;

    if (a <= b)
    {
        cur.update(a, v);
        if (b != M) cur.update(b + 1, v * -1);
    }
    else
    {
        cur.update(1, v);
        cur.update(b + 1, v * -1);
        cur.update(a, v);
    }
}

void solve(int l, int r, vector<int>& rel)
{
    // cout << "solving " << l << " " << r << endl;
    if (rel.empty()) return;
    int mid = (l + r) / 2;
    for (int i = l; i <= mid; i++) process(i, 1);

    vector<int> left, right;
    for (int i = 0; i < rel.size(); i++)
    {
        int n = rel[i];
        // cout << n << ": ";
        ll tot = 0;
        for (int j = 0; j < owns[n].size(); j++)
        {
            tot += cur.query(owns[n][j]);
            if (tot >= target[n]) break;
        }
        // cout << tot << endl;
        if (tot >= target[n]) 
        {
            left.pb(n);
            ans[n] = min(ans[n], mid);
        }
        else right.pb(n);
    }

    if (l == r) 
    {
        process(l, -1);
        return;
    }
    solve(mid + 1, r, right);
    for (int i = l; i <= mid; i++) process(i, -1);
    solve(l, mid, left);
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N >> M;
    for (int i = 1; i <= M; i++) owns[read()].pb(i);
    for (int i = 1; i <= N; i++) cin >> target[i];

    cin >> P;
    for (int i = 1; i <= P; i++) showers[i] = {read(), read(), read()};

    for (int i = 1; i <= N; i++) ans[i] = INF;

    vector<int> rel;
    for (int i = 1; i <= N; i++) rel.pb(i);
    solve(1, P, rel);
    for (int i = 1; i <= N; i++)
    {
        if (ans[i] != INF) cout << ans[i] << endl;
        else cout << "NIE" << endl;
    }
    return 0;
}