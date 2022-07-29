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
int N, Q;

struct ST
{
    ll seg[8 * MAXN];

    void update(int a, int v, int cid, int ss, int se)
    {
        if (ss == se)
        {
            seg[cid] = v;
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

int in[MAXN], out[MAXN];
int tour[2 * MAXN];
int arr[MAXN];
int T = 0;
vector<int> nbs[MAXN];
ST seg;
map<int, queue<int>> occ;
int ans[MAXN];

void DFS(int a, int p)
{
    in[a] = ++T;
    tour[T] = a;
    for (int i = 0; i < nbs[a].size(); i++) 
        if (nbs[a][i] != p) DFS(nbs[a][i], a);
    out[a] = ++T;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N;
    for (int i = 1; i <= N; i++) cin >> arr[i];

    for (int i = 1; i < N; i++)
    {
        int a = read();
        int b = read();
        nbs[a].pb(b);
        nbs[b].pb(a);
    }

    DFS(1, 1);

    for (int i = 1; i <= 2 * N; i++)
    {
        if (tour[i] != 0)
            occ[arr[tour[i]]].push(i);
    }
    
    for (auto n : occ)
        seg.update(n.second.front(), 1, 1, 1, 2 * N);

    for (int i = 1; i <= 2 * N; i++)
    {
        if (tour[i] > 0)
        {
            ans[tour[i]] = seg.query(in[tour[i]], out[tour[i]], 1, 1, 2 * N);
            seg.update(in[tour[i]], 0, 1, 1, 2 * N);
            occ[arr[tour[i]]].pop();
            if (occ[arr[tour[i]]].size() > 0) 
            {
                int nv = occ[arr[tour[i]]].front();
                seg.update(nv, 1, 1, 1, 2 * N);
            }
        }
    }
    
    for (int i = 1; i <= N; i++) cout << ans[i] << " ";
    cout << endl;
    return 0;
}