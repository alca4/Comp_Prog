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
using namespace std;

typedef pair<int, int> pii;
#define F first
#define S second
#define ll long long
#define ld long double
#define INF 1000000000
#define MOD 1000000007
#define DELTA 200000

const int MAXN = 100010;

int readInt()
{
    int a;
    cin >> a;
    return a;
}

int N;
vector<int> child[MAXN];
ll a[MAXN], b[MAXN];
ll dp[MAXN];

struct Line
{
    ll m, b;

    ll valueAt(int x)
    {
        return m * x + b;
    }

    ld intersect(const Line& other)
    {
        return 1.0 * (other.b - b) / (m - other.m);
    }
};

struct Node
{
    Line l;
    int lc = -1, rc = -1;
};

int at[MAXN];
vector<Line> stl[MAXN];
struct LCT
{
    vector<Node> seg;

    int create(Line l)
    {
        seg.push_back({l, -1, -1});
        return seg.size() - 1;
    }

    void insert(Line l, int cid, ll ss, ll se)
    {
        if (ss > se) return;
        ll mid = (ss + se) / 2;

        bool dl = l.valueAt(ss) < seg[cid].l.valueAt(ss);
        bool dm = l.valueAt(mid) < seg[cid].l.valueAt(mid);

        if (dm) 
        {
            Line temp = l;
            l = seg[cid].l;
            seg[cid].l = temp;
        }

        if (ss == se) return;
        else if (dl != dm) 
        {
            if (seg[cid].lc == -1) seg[cid].lc = create(l);
            insert(l, seg[cid].lc, ss, mid);
        }
        else 
        {
            if (seg[cid].rc == -1) seg[cid].rc = create(l);
            insert(l, seg[cid].rc, mid + 1, se);
        }
    }

    ll query(int a, int cid, ll ss, ll se)
    {
        ll ans = seg[cid].l.valueAt(a);
        if (ss == se) return ans;

        ll mid = (ss + se) / 2;
        if (a <= mid)
        {
            if (seg[cid].lc == -1) seg[cid].lc = create(seg[cid].l);
            ans = min(ans, query(a, seg[cid].lc, ss, mid));
        }
        else
        {
            if (seg[cid].rc == -1) seg[cid].rc = create(seg[cid].l);
            ans = min(ans, query(a, seg[cid].rc, mid + 1, se));
        }
        return ans;
    }
};
LCT tree[MAXN];

int combine(int a, int b)
{
    if (stl[a].size() < stl[b].size()) swap(a, b);
    for (int i = 0; i < stl[b].size(); i++) 
    {
        stl[a].push_back(stl[b][i]);
        tree[a].insert(stl[b][i], 0, 1, 1000000);
    }
    return a;
}

void DFS(int n, int p)
{
    tree[n].create({0, 1000000000000000000});
    at[n] = n;

    int leaf = 1;
    for (int i = 0; i < child[n].size(); i++) 
    {
        if (child[n][i] == p) continue;
        DFS(child[n][i], n);
        leaf = 0;
        int a1 = at[n];
        int a2 = at[child[n][i]];
        at[n] = combine(at[n], at[child[n][i]]);
        if (at[n] == a1) 
        {
            stl[a2].clear();
            tree[a2].seg.clear();
        }
        else 
        {
            stl[a1].clear();
            tree[a1].seg.clear();
        }
    }

    if (!leaf) dp[n] = tree[at[n]].query(a[n] + DELTA, 0, 1, 1000000);
    stl[at[n]].push_back({b[n], dp[n] - b[n] * DELTA});
    tree[at[n]].insert({b[n], dp[n] - b[n] * DELTA}, 0, 1, 1000000);
    child[n].clear();
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N;
    for (int i = 1; i <= N; i++) a[i] = readInt();
    for (int i = 1; i <= N; i++) b[i] = readInt();

    for (int i = 1; i < N; i++)
    {
        int a = readInt();
        int b = readInt();
        child[a].push_back(b);
        child[b].push_back(a);
    }
    
    DFS(1, 0);
    for (int i = 1; i <= N; i++) cout << dp[i] << " ";
    cout << endl;
    return 0;
}