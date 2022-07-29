#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

typedef pair<int, int> pii;

int N, K, Q;
int points[200010][5];
int b[32][800010];
int s[32][800010];

void update(int id, int a, int v, int cid, int ss, int se)
{
    if (ss == se)
    {
        b[id][cid] = v;
        s[id][cid] = v;
        return;
    }

    int mid = (ss + se) / 2;
    if (a <= mid) update(id, a, v, cid * 2, ss, mid);
    else update(id, a, v, cid * 2 + 1, mid + 1, se);

    b[id][cid] = max(b[id][cid * 2], b[id][cid * 2 + 1]);
    s[id][cid] = min(s[id][cid * 2], s[id][cid * 2 + 1]);
}

pii query(int id, int qs, int qe, int cid, int ss, int se)
{
    if (qs <= ss && se <= qe) return pii(b[id][cid], s[id][cid]);
    
    int mid = (ss + se) / 2;
    pii ans1 = pii(-1e9, 1e9);
    pii ans2 = pii(-1e9, 1e9);
    if (qs <= mid) ans1 = query(id, qs, qe, cid * 2, ss, mid);
    if (qe > mid) ans2 = query(id, qs, qe, cid * 2 + 1, mid + 1, se);
    return pii(max(ans1.first, ans2.first), min(ans1.second, ans2.second));
}

void insert(int i)
{
    int sum = 0;
    for (int j = 0; j < K; j++) sum += points[i][j];
    for (int j = 0; j < 1 << K; j++)
    {
        int tsum = sum;
        int tmp = j;
        for (int k = 0; k < K; k++)
        {
            if (tmp % 2 == 1) tsum -= 2 * points[i][k];
            tmp /= 2;
        }
        update(j, i, tsum, 1, 1, N);
    }
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N >> K;
    for (int i = 1; i <= N; i++)
        for (int j = 0; j < K; j++)
            cin >> points[i][j];
    
    for (int i = 1; i <= N; i++) insert(i);

    cin >> Q;
    while (Q--)
    {
        int t;
        cin >> t;
        if (t == 1)
        {
            int i;
            cin >> i;
            for (int j = 0; j < K; j++) cin >> points[i][j];
            insert(i);
        }
        if (t == 2)
        {
            int a, b;
            cin >> a >> b;
            int mval = 0;
            for (int j = 0; j < 1 << K; j++)
            {
                pii ans = query(j, a, b, 1, 1, N);
                mval = max(mval, ans.first - ans.second);
            }
            cout << mval << endl;
        }
    }
}