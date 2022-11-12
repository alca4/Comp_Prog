#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

typedef pair<int, int> pii;

struct Node
{
    int v;
    Node* l;
    Node* r;

    Node(int a) {v = a; l = nullptr; r = nullptr;}
    Node(Node* lc, Node* rc)
    {
        v = max(lc->v, rc->v);
        l = lc;
        r = rc;
    }
};

Node* build(int ss, int se)
{
    if (ss == se) return new Node(-1e9);

    int mid = (ss + se) / 2;
    return new Node(build(ss, mid), build(mid + 1, se));
}

Node* update(Node* n, int a, int v, int ss, int se)
{
    if (ss == se) 
    {
        if (v > n->v) return new Node(v);
        else return n;
    }

    int mid = (ss + se) / 2;
    if (a <= mid) return new Node(update(n->l, a, v, ss, mid), n->r);
    else return new Node(n->l, update(n->r, a, v, mid + 1, se));
}

int query(Node* n, int a, int b, int ss, int se)
{
    if (a <= ss && se <= b) return n->v;

    int mid = (ss + se) / 2;
    int ans = -1e9;
    if (a <= mid) ans = max(ans, query(n->l, a, b, ss, mid));
    if (b > mid) ans = max(ans, query(n->r, a, b, mid + 1, se));
    return ans;
}

int N;
int psum[100010];
int dp[100010];
Node* seg;

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N;
    seg = build(1, 2 * N + 1);
    string str;
    cin >> str;
    for (int i = 1; i <= N; i++) psum[i] = psum[i - 1] + (str[i - 1] == 'R' ? 1 : -1);
    for (int i = 0; i <= N; i++) psum[i] += N + 1;

    seg = update(seg, N + 1, -1, 1, 2 * N + 1);
    for (int i = 1; i <= N; i++)
    {
        seg = update(seg, psum[i - 1], dp[i - 1] - i, 1, 2 * N + 1);
        int best = query(seg, 1, psum[i] - 1, 1, 2 * N + 1) + i + 1;
        dp[i] = max(dp[i - 1], best);
    }

    cout << dp[N] << endl;
    return 0;
}