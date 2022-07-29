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
#define pb push_back

const int MAXN = 100010;

int readInt()
{
    int a;
    cin >> a;
    return a;
}

struct Query
{
    int t, x, y;
};

int N;
map<int, int> coords;
Query qs[MAXN];
pii segments[MAXN];

int p[MAXN];
int root(int a)
{
    return p[a] = (a == p[a] ? a : root(p[a]));
}

vector<int> seg[8 * MAXN];

void update(int a, int b, int v, int cid, int ss, int se)
{
    if (a <= ss && se <= b)
    {
        seg[cid].push_back(v);
        return;
    }

    int mid = (ss + se) / 2;
    if (a <= mid) update(a, b, v, cid * 2, ss, mid);
    if (b > mid) update(a, b, v, cid * 2 + 1, mid + 1, se);
}

void query(int a, int id, int cid, int ss, int se)
{
    if (seg[cid].size() > 0)
    {
        for (int i = 0; i < seg[cid].size(); i++)
        {
            int rt = root(seg[cid][i]);
            segments[id] = {min(segments[id].F, segments[rt].F),
                            max(segments[id].S, segments[rt].S)};
            p[rt] = id;
        }
        seg[cid].clear();
        seg[cid].pb(id);
    }

    if (ss == se) return;

    int mid = (ss + se) / 2;
    if (a <= mid) query(a, id, cid * 2, ss, mid);
    else query(a, id, cid * 2 + 1, mid + 1, se);
}

int SEG = 0;

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N;
    for (int i = 1; i <= N; i++) 
    {
        cin >> qs[i].t >> qs[i].x >> qs[i].y;
        if (qs[i].t == 1)
            coords[qs[i].x] = coords[qs[i].y] = 0;
    }

    int cnt = 0;
    for (auto n : coords) coords[n.F] = ++cnt;

    for (int i = 1; i <= N; i++)
    {
        if (qs[i].t == 1)
        {
            SEG++;
            p[SEG] = SEG;
            int l = coords[qs[i].x];
            int r = coords[qs[i].y];
            segments[SEG] = {l, r};
            if (r - l > 1)
            {
                update(l + 1, r - 1, SEG, 1, 1, 2 * MAXN);
            }
            query(l, SEG, 1, 1, 2 * MAXN);
            query(r, SEG, 1, 1, 2 * MAXN);
        }
        else
        {
            int rtx = root(qs[i].x);
            int rty = root(qs[i].y);
            if (rtx == rty || (segments[rty].F <= segments[rtx].F &&
                               segments[rtx].S <= segments[rty].S))
                cout << "YES" << endl;
            else cout << "NO" << endl;
        }
    }
    return 0;
}