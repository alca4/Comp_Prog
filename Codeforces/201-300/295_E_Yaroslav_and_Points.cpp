/*
Idea: Segtree
Coordinate compress, then you have O(N + Q) points to segtree on
Be careful after compression though!
*/
#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
using namespace std;

#define ll long long

struct Query
{
    int t;
    int v1;
    int v2;
};

struct Node
{
    int cnt = 0;
    ll sum = 0;
    ll ans = 0;
};

Node merge(const Node& n1, const Node& n2)
{
    ll temp = n1.cnt * n2.sum - n2.cnt * n1.sum;
    return {n1.cnt + n2.cnt, n1.sum + n2.sum, abs(temp) + n1.ans + n2.ans};
}

int N, Q;
int arr[100010];
int ud[100010];
Node seg[1200010];
Query queries[100010];
map<int, int> segid;

void update(int a, int v, int cid, int ss, int se)
{
    //cout << "updating " << ss << " to " << se << endl;
    if (ss == se)
    {
        if (v == 2000000000) seg[cid] = {0, 0, 0};
        else seg[cid] = {1, v, 0};
        return;
    }

    int mid = (ss + se) / 2;
    if (a <= mid) update(a, v, cid * 2, ss, mid);
    else update(a, v, cid * 2 + 1, mid + 1, se);
    //cout << "merging " << ss << " " << mid << " with " << mid + 1 << " " << se << endl;
    seg[cid] = merge(seg[cid * 2], seg[cid * 2 + 1]);
    return;
}

Node query(int a, int b, int cid, int ss, int se)
{
    if (a <= ss && se <= b) return seg[cid];

    int mid = (ss + se) / 2;
    Node n;
    if (a <= mid) n = merge(n, query(a, b, cid * 2, ss, mid));
    if (b > mid) n = merge(n, query(a, b, cid * 2 + 1, mid + 1, se));
    return n;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N;
    for (int i = 1; i <= N; i++) cin >> arr[i];
    for (int i = 1; i <= N; i++) segid[arr[i]] = 1;

    cin >> Q;
    for (int i = 1; i <= Q; i++)
    {
        cin >> queries[i].t >> queries[i].v1 >> queries[i].v2;
        if (queries[i].t == 1) 
        {
            ud[queries[i].v1] += queries[i].v2;
            segid[arr[queries[i].v1] + ud[queries[i].v1]] = 1;
            //cout << "inserting: " << arr[queries[i].v1] + ud[queries[i].v1] << endl;
        }
        else
        {
            segid[queries[i].v1] = 1;
            segid[queries[i].v2] = 1;
        }
    }

    int id = 1;
    for (auto n : segid)
        segid[n.first] = id++;

    for (int i = 1; i <= N; i++) update(segid[arr[i]], arr[i], 1, 1, 300000);

    for (int i = 1; i <= Q; i++)
    {
        if (queries[i].t == 1)
        {
            //cout << "removing: " << segid[arr[queries[i].v1]] << endl;
            update(segid[arr[queries[i].v1]], 2000000000, 1, 1, 300000);
            arr[queries[i].v1] += queries[i].v2;
            //cout << "updating: " << segid[arr[queries[i].v1]] << endl;
            update(segid[arr[queries[i].v1]], arr[queries[i].v1], 1, 1, 300000);
        }
        else
        {
            //cout << "querying: " << segid[queries[i].v1] << " " << segid[queries[i].v2] << endl;
            cout << query(segid[queries[i].v1], segid[queries[i].v2], 1, 1, 300000).ans << endl;
        }
    }
    return 0;
}