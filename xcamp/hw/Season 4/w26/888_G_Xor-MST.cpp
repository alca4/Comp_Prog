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
using namespace std;

#define F first
#define S second
#define pb push_back
#define ll long long
#define ld long double
#define INF 1000000000ull
#define MOD 1000000007ull

typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

int read()
{
    int a;
    cin >> a;
    return a;
}

const int MAXN = 200010;
const int MAXL = 30;

ll digAt(int a, int p)
{
    return (a & (1 << (p - 1))) > 0;
}

struct Trie
{
    int SZ = 0;
    struct Node
    {
        int v;
        int lc, rc;
        int lcount, rcount;
        int l;
    } trie[20 * MAXN];

    Trie() {create(MAXL);}
    
    int create(int l)
    {
        SZ++;
        trie[SZ].lc = trie[SZ].rc = -1;
        trie[SZ].lcount = trie[SZ].rcount = 0;
        trie[SZ].l = l;
        return SZ;
    }

    int insert(int a, int cid, int l)
    {
        if (cid == -1) cid = create(l);
        if (l > 0)
        {
            if (!digAt(a, l))
            {
                trie[cid].lc = insert(a, trie[cid].lc, l - 1);
                trie[cid].lcount++;
            }
            else
            {
                trie[cid].rc = insert(a, trie[cid].rc, l - 1);
                trie[cid].rcount++;
            }
        }
        else trie[cid].v = a;
        return cid;
    }

    ll findBest(int v, int root, int l)
    {
        if (l == 0) return 0;
        ll dig = digAt(v, l);

        if (!dig)
        {
            if (trie[root].lcount > 0)
                return findBest(v, trie[root].lc, l - 1);
            else
                return pow(2, l - 1) + findBest(v, trie[root].rc, l - 1);
        }
        else
        {
            if (trie[root].rcount > 0)
                return findBest(v, trie[root].rc, l - 1);
            else
                return pow(2, l - 1) + findBest(v, trie[root].lc, l - 1);
        }
    }

    ll searchVals(int root, int l, int r2, int l2)
    {
        if (l == 0) return findBest(trie[root].v, r2, l2);

        ll ans = INF;
        if (trie[root].lcount > 0) ans = min(ans, searchVals(trie[root].lc, l - 1, r2, l2));
        if (trie[root].rcount > 0) ans = min(ans, searchVals(trie[root].rc, l - 1, r2, l2));
        return ans;
    }

    ll ans(int root, int l)
    {
        if (l == 0) return 0;
        ll a1 = 0, a2 = 0, a3 = 0;
        if (trie[root].lc != -1) a1 = ans(trie[root].lc, l - 1);
        if (trie[root].rc != -1) a2 = ans(trie[root].rc, l - 1);

        if (trie[root].lc != -1 && trie[root].rc != -1)
        {
            a3 = searchVals(trie[root].lc, l - 1, trie[root].rc, l - 1) + pow(2, l - 1);
            used++;
        }

        return a1 + a2 + a3;
    }

    int T;
    int used = 0;
};

int N;
set<int> vals;
Trie t;

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N;
    for (int i = 1; i <= N; i++) 
    {
        int n;
        cin >> n;
        vals.insert(n);
    }

    for (auto n : vals) t.insert(n, 1, MAXL);
    t.T = vals.size();
    
    cout << t.ans(1, MAXL) << endl;
    return 0;
}