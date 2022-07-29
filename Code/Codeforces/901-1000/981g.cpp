#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
using namespace std;

#define ll long long
#define MOD 998244353
typedef pair<int, int> pii;

int N, Q;
ll seg[800010];
ll mult[800010];
ll add[800010];
void build(int cid, int ss, int se)
{
    if (ss == se) return;
    mult[cid] = 1;
    add[cid] = 0;

    int mid = (ss + se) / 2;
    build(cid * 2, ss, mid);
    build(cid * 2 + 1, mid + 1, se);
}
void prop(int cid, int ss, int se)
{
    if (mult[cid] == 1 && add[cid] == 0) return;
    seg[cid] = ((seg[cid] * mult[cid]) % MOD + (add[cid] * (se - ss + 1)) % MOD) % MOD;
    if (ss != se)
    {
        int mid = (ss + se) / 2;
        //seg[cid * 2] = (seg[cid * 2] * mult[cid] + add[cid] * (mid - ss + 1)) % MOD;
        mult[cid * 2] = (mult[cid * 2] * mult[cid]) % MOD;
        add[cid * 2] = (add[cid * 2] * mult[cid] + add[cid]) % MOD;
        //seg[cid * 2 + 1] = (seg[cid * 2 + 1] * mult[cid] + add[cid] * (se - mid)) % MOD;
        mult[cid * 2 + 1] = (mult[cid * 2 + 1] * mult[cid]) % MOD;
        add[cid * 2 + 1] = (add[cid * 2 + 1] * mult[cid] + add[cid]) % MOD;
    }
    mult[cid] = 1;
    add[cid] = 0;
}
void update(int a, int b, int v, int cid, int ss, int se)
{
    prop(cid, ss, se);
    //cout << "updating " << ss << " " << se << " with " << v << endl;
    //cout << "current value is: " << seg[cid] << endl;
    if (a <= ss && se <= b)
    {
        if (v == 1) add[cid] = (add[cid] + 1) % MOD;
        if (v == 2) mult[cid] = (mult[cid] * 2) % MOD;
        prop(cid, ss, se);
        return;
    }

    int mid = (ss + se) / 2;
    if (a <= mid) update(a, b, v, cid * 2, ss, mid);
    if (b > mid) update(a, b, v, cid * 2 + 1, mid + 1, se);
    prop(cid * 2, ss, mid);
    prop(cid * 2 + 1, mid + 1, se);
    seg[cid] = (seg[cid * 2] + seg[cid * 2 + 1]) % MOD;
    //cout << ss << " to " << se << " has set sizes " << seg[cid] << endl;
}
ll query(int a, int b, int cid, int ss, int se)
{
    //cout << "querying: " << ss << " to " << se << endl;
    prop(cid, ss, se);
    if (a <= ss && se <= b) 
    {
        //cout << "seg from " << ss << " to " << se << " is " << seg[cid] << endl;
        return seg[cid];
    }

    int mid = (ss + se) / 2;
    ll ans = 0;
    if (a <= mid) ans += query(a, b, cid * 2, ss, mid);
    if (b > mid) ans += query(a, b, cid * 2 + 1, mid + 1, se);
    prop(cid * 2, ss, mid);
    prop(cid * 2 + 1, mid + 1, se);
    seg[cid] = (seg[cid * 2] + seg[cid * 2 + 1]) % MOD;
    //cout << "ans from " << ss << " to " << se << " is " << ans << endl;
    return ans % MOD;
}

struct Node
{
    int v;
    int full = 0;
    int l = -1;
    int r = -1;
};
int sz;
Node occ[15000000];
void prop2(int id, int ss, int se)
{
    if (!occ[id].full) return;
    occ[id].full = 0;
    occ[id].v = (se - ss + 1);
    if (ss == se) return;
    int mid = (ss + se) / 2;
    if (occ[id].l == -1) occ[id].l = sz++;
    occ[occ[id].l].full = 1;
    occ[occ[id].l].v = mid - ss + 1;
    if (occ[id].r == -1) occ[id].r = sz++;
    occ[occ[id].r].full = 1;
    occ[occ[id].r].v = se - mid;
}
void traverse(int id, int a, int b, int ss, int se)
{
    prop2(id, ss, se);

    //cout << "traversing on: " << ss << " " << se << endl;
    if (a <= ss && se <= b)
    {
        //cout << "range " << ss << " to " << se << " has value " << n.v << endl;
        if (occ[id].v == (se - ss + 1))
        {
            //cout << "updating " << ss << " to " << se << " by 2 " << endl;
            update(ss, se, 2, 1, 1, N);
            return;
        }
        if (occ[id].v == 0)
        {
            //cout << "updating " << ss << " to " << se << " by 1 " << endl;
            update(ss, se, 1, 1, 1, N);
            occ[id].v = (se - ss + 1);
            occ[id].full = 1;
            return;
        }
    }

    int mid = (ss + se) / 2;
    if (a <= mid) 
    {
        if (occ[id].l == -1) occ[id].l = sz++;
        traverse(occ[id].l, a, b, ss, mid);
    }
    if (b > mid) 
    {
        if (occ[id].r == -1) occ[id].r = sz++;
        traverse(occ[id].r, a, b, mid + 1, se);
    }

    int val = 0;
    if (occ[id].l != -1) val += occ[occ[id].l].v;
    if (occ[id].r != -1) val += occ[occ[id].r].v;
    occ[id].v = val;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N >> Q;
    build(1, 1, N);
    sz = N + 1;
    while (Q--)
    {
        int t;
        cin >> t;
        //cout << "====" << endl;
        if (t == 1)
        {
            int v, x, y;
            cin >> x >> y >> v;
            traverse(v, x, y, 1, N);
        }
        else
        {
            int x, y;
            cin >> x >> y;
            cout << query(x, y, 1, 1, N) << endl;
        }
    }
    return 0;
}