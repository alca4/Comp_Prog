/*
Idea: segtree
Each color gets its own lazy value
Handle set of intervals
Use segtree for corrections-when swtiching from c to c2, a[i] += lazy[c] - lazy[c2]
Maintain your set

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
#define INF 1000000000ll
#define MOD 1000000007ll

typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

const int MAXN = 1000010;
int N, Q;

struct Itv
{
    int s, e, c;
};

bool operator<(const Itv& i1, const Itv& i2)
{
    return pii(i1.s, i1.e) < pii(i2.s, i2.e);
}

set<Itv> itvs;
ll lazy[MAXN];

struct ST
{
    ll seg[4 * MAXN];

    void update(int a, ll v, int cid, int ss, int se)
    {
        if (a > N) return;
        if (ss == se)
        {
            seg[cid] += v;
            return;
        }

        int mid = (ss + se) / 2;
        if (a <= mid) update(a, v, cid * 2, ss, mid);
        else update(a, v, cid * 2 + 1, mid + 1, se);
        seg[cid] = seg[cid * 2] + seg[cid * 2 + 1];
    }

    ll query(int a, int b, int cid, int ss, int se)
    {
        if (a <= ss && se <= b) return seg[cid];

        ll ans = 0;
        int mid = (ss + se) / 2;
        if (a <= mid) ans += query(a, b, cid * 2, ss, mid);
        if (b > mid) ans += query(a, b, cid * 2 + 1, mid + 1, se);
        return ans;
    } 
};

ST st;

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N >> Q;

    Itv init;
    init.s = 1;
    init.e = N;
    init.c = 1;

    itvs.insert(init);

    while (Q--)
    {
        // cout << "====================" << endl;
        string str;
        cin >> str;
        if (str == "Color")
        {
            int a, b, c;
            cin >> a >> b >> c;

            Itv s = *(--itvs.upper_bound({a, INF, a}));
            itvs.erase(s);
            if (s.s < a) itvs.insert({s.s, a - 1, s.c});
            itvs.insert({a, s.e, s.c});

            // cout << s.s << " " << s.e << " is gone " << endl;

            Itv e = *(--itvs.upper_bound({b, INF, b}));
            itvs.erase(e);
            if (e.e > b) itvs.insert({b + 1, e.e, e.c});
            itvs.insert({e.s, b, e.c});

            // cout << e.s << " " << e.e << " is gone " << endl;

            auto rs = --itvs.upper_bound({a, INF, a});
            auto re = itvs.upper_bound({b, INF, b});

            // cout << "removing from " << rs->s << " " << rs->e << " to "
            //      << re->s << " " << re->e << endl;
            

            for (auto it = rs; it != re; ++it) 
            {
                // cout << it->s << " " << it->e << endl;
                // cout << "adding " << lazy[it->c] - lazy[c] << " to " << it->e << endl;
                // cout << "adding " << lazy[c] - lazy[it->c] << " to " << it->s - 1 << endl;
                st.update(it->s, lazy[it->c] - lazy[c], 1, 1, N);
                st.update(it->e + 1, lazy[c] - lazy[it->c], 1, 1, N);
            }

            itvs.erase(rs, re);
            itvs.insert({a, b, c});
        }
        if (str == "Add")
        {
            int a, b;
            cin >> a >> b;
            lazy[a] += b;
        }
        if (str == "Query")
        {
            int id;
            cin >> id;
            int color = (--itvs.upper_bound({id, INF, id}))->c;
            cout << st.query(1, id, 1, 1, N) + lazy[color] << endl;
        }

        // for (int i = 1; i <= N; i++) cout << st.query(1, i, 1, 1, N) << " ";
        // cout << endl;
        // for (int i = 1; i <= N; i++)
        // {
        //     int color = (--itvs.upper_bound({i, INF, i}))->c;
        //     cout << lazy[color] << " ";
        // }
        // cout << endl;

        // for (auto n : itvs)
        // {
        //     cout << n.s << " " << n.e << endl;
        // }
    }
    return 0;
} 