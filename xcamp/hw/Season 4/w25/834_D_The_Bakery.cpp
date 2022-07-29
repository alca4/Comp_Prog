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

#define F first
#define S second
#define pb push_back
#define ll long long
#define ld long double
#define INF 1000000000
#define MOD 1000000007

typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

int readInt()
{
    int a;
    cin >> a;
    return a;
}

const int MAXN = 35010;

struct ST
{
    int seg[4 * MAXN], lazy[4 * MAXN];

    void apply(int v, int cid)
    {
        lazy[cid] += v;
        seg[cid] += v;
    }

    void push(int cid, int ss, int se)
    {
        if (ss != se)
        {
            apply(lazy[cid], cid * 2);
            apply(lazy[cid], cid * 2 + 1);
        }
        lazy[cid] = 0;
    }

    void update(int a, int b, int v, int cid, int ss, int se)
    {
        if (a > b) return;
        if (a <= ss && se <= b)
        {
            apply(v, cid);
            return;
        }

        push(cid, ss, se);
        int mid = (ss + se) / 2;
        if (a <= mid) update(a, b, v, cid * 2, ss, mid);
        if (b > mid) update(a, b, v, cid * 2 + 1, mid + 1, se);
        seg[cid] = max(seg[cid * 2], seg[cid * 2 + 1]);
    }

    void clear(int cid, int ss, int se)
    {
        seg[cid] = lazy[cid] = 0;
        if (ss == se) return;

        int mid = (ss + se) / 2;
        clear(cid * 2, ss, mid);
        clear(cid * 2 + 1, mid + 1, se);
    }
};

int N, K;
int cakes[MAXN];
int last[MAXN];
int p_occ[MAXN];
int dp[MAXN][60];

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N >> K;
    for (int i = 1; i <= N; i++) cin >> cakes[i];
    for (int i = 1; i <= N; i++) last[cakes[i]] = -1;
    for (int i = 1; i <= N; i++)
    {
        p_occ[i] = last[cakes[i]];
        last[cakes[i]] = i;
    }

    for (int i = 1; i <= K; i++)
    {
        ST seg;
        for (int j = 1; j <= N; j++)
        {
            seg.update(p_occ[j] + 1, j - 1, 1, 1, 0, N);
            // cout << "update " << p_occ[j] + 1 << " to " << j - 1 << endl;
            seg.update(j, j, dp[j - 1][i - 1] + 1, 1, 0, N);
            dp[j][i] = seg.seg[1];
        }
        /*s
        for (int j = 1; j <= N; j++) cout << dp[j][i] << " ";
        cout << endl;
        */
        seg.clear(1, 0, N);
    }
    
    cout << dp[N][K] << endl;
    return 0;
}