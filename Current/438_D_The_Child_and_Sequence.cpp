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

Praise to the Cow God
*/
#include <bits/stdc++.h>
using namespace std;

#define FF first
#define SS second
#define pb push_back
#define ll long long
#define ld long double
#define ull unsigned ll
ll INF = 1000000000;
ll LINF = 1000000000000000000;
ll MOD = 1000000007;
// ll MOD = 998244353;

ifstream fin(".in");
ofstream fout(".out");

typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

ll add(const ll& a, const ll& b) {return (a + b) % MOD;}
ll sub(const ll& a, const ll& b) {return (a + MOD - b) % MOD;}
ll mult(const ll& a, const ll& b) {return (a * b) % MOD;}
ll power(ll a, ll b)
{
    ll n = b;
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
ll divide(const ll& a, const ll& b) {return (a * power(b, MOD - 2)) % MOD;}

int rand32()
{
    int a = rand();
    int b = rand();
    return (a << 16) | b;
}

ll rand64()
{
    ll a = rand32();
    ll b = rand32();
    return (a << 32) | b;
}

const int MAXN = 100010;
int N, Q;
ll arr[MAXN];

struct ST
{
    pll seg[4 * MAXN];

    void update(int a, int v, int cid, int ss, int se)
    {
        if (ss == se)
        {
            seg[cid].FF = v;
            seg[cid].SS = a;
            return;
        }

        int mid = (ss + se) / 2;
        if (a <= mid) update(a, v, cid * 2, ss, mid);
        else update(a, v, cid * 2 + 1, mid + 1, se);
        seg[cid].FF = seg[cid * 2].FF + seg[cid * 2 + 1].FF;
        seg[cid].SS = (arr[seg[cid * 2].SS] > arr[seg[cid * 2 + 1].SS])
                       ? seg[cid * 2].SS : seg[cid * 2 + 1].SS;
    }

    int max_query(int a, int b, int cid, int ss, int se)
    {
        if (a <= ss && se <= b) return seg[cid].SS;

        int ans = 0;
        int mid = (ss + se) / 2;
        if (a <= mid)
        {
            int al = max_query(a, b, cid * 2, ss, mid);
            if (arr[ans] < arr[al]) ans = al;
        } 
        if (b > mid) 
        {
            int ar = max_query(a, b, cid * 2 + 1, mid + 1, se);
            if (arr[ans] < arr[ar]) ans = ar;
        }
        return ans;
    }

    ll sum_query(int a, int b, int cid, int ss, int se)
    {
        if (a <= ss && se <= b) return seg[cid].FF;

        ll ans = 0;
        int mid = (ss + se) / 2;
        if (a <= mid) ans += sum_query(a, b, cid * 2, ss, mid);
        if (b > mid) ans += sum_query(a, b, cid * 2 + 1, mid + 1, se);
        return ans;
    } 
};

ST st;

int main()
{
    srand(time(NULL));
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N >> Q;
    for (int i = 1; i <= N; i++) 
    {
        cin >> arr[i];
        st.update(i, arr[i], 1, 1, N);
    }

    while (Q--)
    {
        int t;
        cin >> t;
        if (t == 1) 
        {
            int a, b;
            cin >> a >> b;
            cout << st.sum_query(a, b, 1, 1, N) << endl;
        }
        if (t == 2)
        {
            int a, b, x;
            cin >> a >> b >> x;
            int n = st.max_query(a, b, 1, 1, N);
            while (arr[n] >= x)
            {
                arr[n] %= x;
                st.update(n, arr[n], 1, 1, N);
                n = st.max_query(a, b, 1, 1, N);
            }
        }
        if (t == 3) 
        {
            int a, v;
            cin >> a >> v;
            arr[a] = v;
            st.update(a, arr[a], 1, 1, N);
        }
    }

    return 0;
} 