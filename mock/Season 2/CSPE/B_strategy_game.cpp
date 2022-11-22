/*
  ___
 (o,o)
<  .  >
--"-"---
Rowlet is orz
  _      _      _
>(.)__ <(.)__ =(.)__
 (___/  (___/  (___/
I am dum duck
*/
#include <bits/stdc++.h>
using namespace std;

#define FF first
#define SS second
#define pb push_back
#define ll long long
#define ld long double
#define INF 1000000000000000000
#define MOD 1000000007ll

typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

ll add(const ll& a, const ll& b) {return (a + b) % MOD;}
ll mult(const ll& a, const ll& b) {return (a * b) % MOD;}

ll modInverse(ll a)
{
    ll n = MOD - 2;
    ll ans = 1;

    ll binexp[64];
    binexp[0] = a;
    for (int i = 1; i < 64; i++) binexp[i] = mult(binexp[i - 1], binexp[i - 1]);

    while (n > 0)
    {
        int id = (int) log2(n & -n);
        ans = mult(ans, binexp[id]);
        n -= (n & -n);
    }

    return ans;
}

const int MAXN = 100010;
int N, M, Q;

struct ST
{
    pll seg[4 * MAXN];

    ST(int n)
    {
        init(1, 1, n);
    }

    void init(int cid, int ss, int se)
    {
        seg[cid] = {-INF, INF};
        if (ss == se) return;

        int mid = (ss + se) / 2;
        init(cid * 2, ss, mid);
        init(cid * 2 + 1, mid + 1, se);
    }

    pll combine(pll a, pll b)
    {
        return {max(a.FF, b.FF), min(a.SS, b.SS)};
    }

    void update(int a, int v, int cid, int ss, int se)
    {
        if (ss == se)
        {
            seg[cid] = {v, v};
            return;
        }

        int mid = (ss + se) / 2;
        if (a <= mid) update(a, v, cid * 2, ss, mid);
        else update(a, v, cid * 2 + 1, mid + 1, se);
        seg[cid] = combine(seg[cid * 2], seg[cid * 2 + 1]);
    }

    pll query(int a, int b, int cid, int ss, int se)
    {
        if (a <= ss && se <= b) return seg[cid];

        pll ans = {-INF, INF};
        int mid = (ss + se) / 2;
        if (a <= mid) ans = combine(ans, query(a, b, cid * 2, ss, mid));
        if (b > mid) ans = combine(ans, query(a, b, cid * 2 + 1, mid + 1, se));
        return ans;
    } 
};

int main()
{
    srand(time(NULL));
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N >> M >> Q;
    ST a(N), b(M), apos(N), aneg(N), bpos(M), bneg(M), aabs(N), babs(M);
    for (int i = 1; i <= N; i++) 
    {
        int n;
        cin >> n;
        a.update(i, n, 1, 1, N);
        if (n > 0) apos.update(i, n, 1, 1, N);
        if (n < 0) aneg.update(i, n, 1, 1, N);
        aabs.update(i, abs(n), 1, 1, N);
    }
    for (int i = 1; i <= M; i++) 
    {
        int n;
        cin >> n;
        b.update(i, n, 1, 1, M);
        if (n > 0) bpos.update(i, n, 1, 1, M);
        if (n < 0) bneg.update(i, n, 1, 1, M);
        babs.update(i, abs(n), 1, 1, M);
    }

    while (Q--)
    {
        int al, ar, bl, br;
        cin >> al >> ar >> bl >> br;

        ll ans = -INF;

        ll achoices[5];
        achoices[0] = a.query(al, ar, 1, 1, N).FF;
        achoices[1] = a.query(al, ar, 1, 1, N).SS;
        achoices[2] = apos.query(al, ar, 1, 1, N).SS;
        achoices[3] = aneg.query(al, ar, 1, 1, N).FF;
        achoices[4] = aabs.query(al, ar, 1, 1, N).SS;
        if (achoices[4] != 0) achoices[4] = INF;

        ll bchoices[5];
        bchoices[0] = b.query(bl, br, 1, 1, M).FF;
        bchoices[1] = b.query(bl, br, 1, 1, M).SS;
        bchoices[2] = bpos.query(bl, br, 1, 1, M).SS;
        bchoices[3] = bneg.query(bl, br, 1, 1, M).FF;
        bchoices[4] = babs.query(bl, br, 1, 1, M).SS;
        if (bchoices[4] != 0) bchoices[4] = INF;

        for (int i = 0; i < 5; i++)
        {
            if (achoices[i] == INF || achoices[i] == -INF) continue;
            ll bchoice = INF;
            for (int j = 0; j < 5; j++) if (bchoices[j] != INF && bchoices[j] != -INF)
                bchoice = min(bchoice, achoices[i] * bchoices[j]);
            ans = max(ans, bchoice);
        }
        
        cout << ans << endl;
    }

    return 0;
} 