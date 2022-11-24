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
#define INF 1000000000000000000ll
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
int N, Q;

map<ll, ll> compress;
map<ll, ll> unravel;

struct ST
{
    int seg[8 * MAXN], lazy[8 * MAXN];

    void push(int cid, int ss, int se)
    {
        if (lazy[cid] == 1) seg[cid] = se - ss + 1;
        if (lazy[cid] == 2) seg[cid] = 0;
        if (lazy[cid] == 3) seg[cid] = se - ss + 1 - seg[cid];

        if (ss != se)
        {
            if (lazy[cid] == 1 || lazy[cid] == 2) lazy[cid * 2] = lazy[cid * 2 + 1] = lazy[cid];
            else 
            {
                lazy[cid * 2] = 3 - lazy[cid * 2];
                lazy[cid * 2 + 1] = 3 - lazy[cid * 2 + 1];
            }
        }
        lazy[cid] = 0;
    }

    void update(int a, int b, int v, int cid, int ss, int se)
    {
        push(cid, ss, se);
        if (a <= ss && se <= b)
        {
            lazy[cid] = v;
            push(cid, ss, se);
            return;
        }

        int mid = (ss + se) / 2;
        if (a <= mid) update(a, b, v, cid * 2, ss, mid);
        if (b > mid) update(a, b, v, cid * 2 + 1, mid + 1, se);
        seg[cid] = seg[cid * 2] + seg[cid * 2 + 1];
    }

    ll query(int cid, int ss, int se)
    {
        push(cid, ss, se);
        if (seg[cid] == se - ss + 1) return unravel[se + 1];
        if (ss == se) return unravel[ss];

        int mid = (ss + se) / 2;
        ll ans;
        if (seg[cid * 2] == mid - ss + 1) ans = query(cid * 2 + 1, mid + 1, se);
        else ans = query(cid * 2, ss, mid);
        seg[cid] = seg[cid * 2] + seg[cid * 2 + 1];
        return ans;
    }
};

struct Query
{
    int t;
    ll l, r;
} queries[MAXN];

ST st;

int main()
{
    srand(time(NULL));
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> Q;
    compress[1] = 1;
    for (int i = 1; i <= Q; i++)
    {
        int t;
        ll l, r;
        cin >> t >> l >> r;
        queries[i] = {t, l, r};
        compress[l] = 1;
        compress[r + 1] = 1;
    }

    int cnt = 0;
    for (auto n : compress) compress[n.FF] = ++cnt;
    for (auto n : compress) unravel[n.SS] = n.FF;
    N = compress.size() - 1;

    for (int i = 1; i <= Q; i++)
    {
        st.update(compress[queries[i].l], compress[queries[i].r + 1] - 1, queries[i].t, 1, 1, N);

        for (int i = 1; i <= 4 * N; i++) cout << st.seg[i] << " ";
        cout << endl;

        if (unravel[1] != 1) cout << 1 << endl;
        else cout << st.query(1, 1, N) << endl;
    }
    return 0;
} 