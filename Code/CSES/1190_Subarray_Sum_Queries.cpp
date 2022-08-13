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

const int MAXN = 500010;

struct ST
{
    struct Node
    {
        ll ans, l_ans, r_ans, sum;
    } seg[MAXN * 4];

    Node combine(Node& n1, Node& n2)
    {
        Node ans;
        ans.ans = max({n1.ans, n2.ans, n1.r_ans + n2.l_ans});
        ans.l_ans = max(n1.l_ans, n1.sum + n2.l_ans);
        ans.r_ans = max(n1.r_ans + n2.sum, n2.r_ans);
        ans.sum = n1.sum + n2.sum;
        return ans;
    }

    void init(int cid, int ss, int se)
    {
        seg[cid] = {0, 0, 0, 0};
        if (ss == se) return;

        int mid = (ss + se) / 2;
        init(cid * 2, ss, mid);
        init(cid * 2 + 1, mid + 1, se);
    }

    void update(int a, ll v, int cid, int ss, int se)
    {
        if (ss == se)
        {
            seg[cid] = {v, v, v, v};
            return;
        }

        int mid = (ss + se) / 2;
        if (a <= mid) update(a, v, cid * 2, ss, mid);
        else update(a, v, cid * 2 + 1, mid + 1, se);
        seg[cid] = combine(seg[cid * 2], seg[cid * 2 + 1]);
    }
};

ST st;
int N, Q;

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N >> Q;
    for (int i = 1; i <= N; i++)
    {
        int n;
        cin >> n;
        st.update(i, n, 1, 1, N);
    }

    while (Q--)
    {
        int a, b;
        cin >> a >> b;
        st.update(a, b, 1, 1, N);
        cout << max(st.seg[1].ans, (ll) 0) << endl;
    }
    return 0;
}