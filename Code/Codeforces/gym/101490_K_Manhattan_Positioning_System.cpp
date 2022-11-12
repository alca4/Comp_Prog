/*
  ___
 (o,o)
<  .  >
--"-"---
Rowlet is orz
*/
#include <bits/stdc++.h>
using namespace std;

#define FF first
#define SS second
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

const int MAXN = 1010;
int N;
pii pts[MAXN];
int d[MAXN];

struct Line
{
    int n1, n2, n3;

    bool operator<(const Line& other)
    {
        return n3 < other.n3;
    }
};

Line lb[MAXN], rb[MAXN], ub[MAXN], db[MAXN];

bool check(int x, int y)
{
    if ((x + y) % 2 == 1) return 0;
    for (int i = 1; i <= N; i++) if (max(abs(x - pts[i].FF), abs(y - pts[i].SS)) != d[i]) return 0;
    return 1;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N;
    for (int i = 1; i <= N; i++) cin >> pts[i].FF >> pts[i].SS >> d[i];
    for (int i = 1; i <= N; i++) 
    {
        int x = pts[i].FF, y = pts[i].SS;
        pts[i].FF = x + y;
        pts[i].SS = x - y;
    }

    for (int i = 1; i <= N; i++)
    {
        int x = pts[i].FF, y = pts[i].SS;
        // cout << x << " " << y << endl;
        db[i] = {x - d[i], x + d[i], y - d[i]};
        ub[i] = {x - d[i], x + d[i], y + d[i]};
        lb[i] = {y - d[i], y + d[i], x - d[i]};
        rb[i] = {y - d[i], y + d[i], x + d[i]};
    }

    sort(lb + 1, lb + 1 + N);
    sort(rb + 1, rb + 1 + N);
    sort(ub + 1, ub + 1 + N);
    sort(db + 1, db + 1 + N);

    int r = rb[1].n3;
    int l = lb[N].n3;
    int u = ub[1].n3;
    int d = db[N].n3;

    // cout << l << " " << r << " " << d << " " << u << endl;
    
    if (r < l || u < d) 
    {
        cout << "impossible" << endl;
        return 0;
    } 
    if (d < max(lb[N].n1, rb[1].n1) || d > min(lb[N].n2, rb[1].n2) ||
        u < max(lb[N].n1, rb[1].n1) || u > min(lb[N].n2, rb[1].n2) ||
        l < max(db[N].n1, ub[1].n1) || l > min(db[N].n2, ub[1].n2) ||
        r < max(db[N].n1, ub[1].n1) || r > min(db[N].n2, ub[1].n2))
    {
        cout << "impossible" << endl;
        return 0;
    }

    int cnt = 0;
    pii ans;
    if (check(l, d)) ans = {l, d}, cnt++;
    if (u != d && check(l, u)) ans = {l, u}, cnt++;
    if (l != r && check(r, d)) ans = {r, d}, cnt++;
    if (l != r && u != d && check(r, u)) ans = {r, u}, cnt++;

    int x = (ans.FF + ans.SS) / 2;
    int y = (ans.FF - ans.SS) / 2;

    if (cnt == 0) cout << "impossible" << endl;
    else if (cnt > 1) cout << "uncertain" << endl;
    else cout << x << " " << y << endl;
    return 0;
}