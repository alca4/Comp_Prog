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
#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
using namespace std;

#define FF first
#define SS second

typedef pair<int, int> pii;

const int MAXN = 2000010;
int N;
int arr[MAXN];
pii pairs[MAXN];

struct ST
{
    int seg[4 * MAXN];

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
        seg[cid] = max(seg[cid * 2], seg[cid * 2 + 1]);
    }

    int query(int a, int b, int cid, int ss, int se)
    {
        if (a > b) return 0;
        if (a <= ss && se <= b) return seg[cid];

        int ans = 0;
        int mid = (ss + se) / 2;
        if (a <= mid) ans = max(ans, query(a, b, cid * 2, ss, mid));
        if (b > mid) ans = max(ans, query(a, b, cid * 2 + 1, mid + 1, se));
        return ans;
    } 
};

ST st[4];

int main()
{
    // srand(time(NULL));
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    
    cin >> N;
    for (int i = 1; i <= N; i++) cin >> arr[i];

    for (int i = 1; i <= N; i++) pairs[i] = {arr[i], i};
    sort(pairs + 1, pairs + 1 + N);
    int nxt = 1;
    for (int i = 1; i <= N; i++)
    {
        if (i > 1 && pairs[i - 1].FF != pairs[i].FF) nxt++;
        arr[pairs[i].SS] = nxt;
    }

    int best = 0;
    st[0].update(arr[1], 1, 1, 1, N);
    st[2].update(arr[1], 1, 1, 1, N);
    for (int i = 2; i <= N; i++)
    {
        int id = arr[i];
        int a = 1 + st[1].query(1, id - 1, 1, 1, N);
        int b = 1 + st[0].query(id + 1, N, 1, 1, N);
        st[0].update(id, a, 1, 1, N);
        st[1].update(id, b, 1, 1, N);
        int c = 1 + st[3].query(id + 1, N, 1, 1, N);
        int d = 1 + st[2].query(1, id - 1, 1, 1, N);
        st[2].update(id, c, 1, 1, N);
        st[3].update(id, d, 1, 1, N);
        best = max({best, a, b, c, d});
    }
    cout << best << endl;
    return 0;
} 