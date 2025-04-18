/*
Idea: Sweepline Segtree
Pretty straightforward application
Compress one of two dimensions into time
*/
#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
using namespace std;

#define ll long long

struct Info
{
    int l;
    int r;
    int loc;

    bool operator<(const Info& other) const
    {
        return loc < other.loc;
    }
};

ll N, Q;
map<int, int> index;
int seg[1200010]; // expected, upset
int lazy[1200010];
vector<Info> ud;
ll sum[300010];

void pull(int cid, int ss, int se)
{
    lazy[cid] = 0;
    seg[cid] = se - ss + 1 - seg[cid];
    if (ss == se) return;
    lazy[cid * 2] = 1 - lazy[cid * 2];
    lazy[cid * 2 + 1] = 1 - lazy[cid * 2 + 1];
}

void update(int a, int b, int cid, int ss, int se)
{
    if (lazy[cid]) pull(cid, ss, se);

    if (a <= ss && se <= b)
    {
        lazy[cid] = 1;
        pull(cid, ss, se);
        return;
    }

    int mid = (ss + se) / 2;
    if (a <= mid) update(a, b, cid * 2, ss, mid);
    if (b > mid) update(a, b, cid * 2 + 1, mid + 1, se);
    if (lazy[cid * 2]) pull(cid * 2, ss, mid);
    if (lazy[cid * 2 + 1]) pull(cid * 2 + 1, mid + 1, se);
    seg[cid] = seg[cid * 2] + seg[cid * 2 + 1];
}

int query(int a, int b, int cid, int ss, int se)
{
    if (lazy[cid]) 
    {
        //cout << "unresolved update at " << ss << " " << se << endl;
        pull(cid, ss, se);
        //cout << "val is now: " << seg[cid] << endl;
    }

    if (a <= ss && se <= b) return seg[cid];

    int mid = (ss + se) / 2;
    int ans = 0;
    if (a <= mid) ans += query(a, b, cid * 2, ss, mid);
    if (b > mid) ans += query(a, b, cid * 2 + 1, mid + 1, se);
    if (lazy[cid * 2]) pull(cid * 2, ss, mid);
    if (lazy[cid * 2 + 1]) pull(cid * 2 + 1, mid + 1, se);
    seg[cid] = seg[cid * 2] + seg[cid * 2 + 1];
    return ans;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N >> Q;
    for (int i = 1; i <= N; i++) 
    {
        int a;
        cin >> a;
        index[a] = i;
    }

    int cnt = 1;
    for (auto n : index) 
    {
        index[n.first] = cnt++;
    }
    index[1000000001] = cnt;

    for (int i = 1; i <= Q; i++)
    {
        int l, r;
        cin >> l >> r;
        if (index.find(l) != index.end()) l = index[l];
        else if (index.upper_bound(l) == index.end()) continue;
        else l = index[index.upper_bound(l)->first];
        if (index.find(r) != index.end()) r = index[r];
        else if (index.upper_bound(r) == index.begin()) continue;
        else r = index[index.upper_bound(r)->first] - 1;
        //cout << l << " " << r << endl;
        ud.push_back({l, r, l});
        ud.push_back({l, r, r + 1});
    }

    sort(ud.begin(), ud.end());

    int id = 0;
    for (int i = 1; i <= N; i++)
    {
        //cout << "i is: " << i << endl;
        while (id < ud.size())
        {
            if (ud[id].loc != i) break;
            
            update(ud[id].l, ud[id].r, 1, 1, N);
            //cout << "updating " << ud[id].l << " " << ud[id].r << endl;
            id++;
        }

        if (i > 1) 
        {
            sum[i] += query(1, i - 1, 1, 1, N);
            //cout << "gained from start " << query(1, i - 1, 1, 1, N) << endl;
        }
        if (i < N) 
        {
            sum[i] += N - i - query(i + 1, N, 1, 1, N);
            //cout << "gained from end " << N - i - query(i + 1, N, 1, 1, N) << endl;
        }
        //cout << "sum is: " << sum[i] << endl;
    }

    ll ans = N * (N - 1) * (N - 2) / 6;
    for (int i = 1; i <= N; i++) ans -= sum[i] * (sum[i] - 1) / 2;
    cout << ans << endl;
    return 0;
}