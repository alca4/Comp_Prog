/*
Idea: segtree
Segtree stores occurences of a number
Walk on segtree to find answer (amortizes o nklogn)
*/
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

#define MAXN 300000

struct Query
{
    int l;
    int r;
    int k;
    int id;
};

struct Node
{
    // #occ, val of number * -1
    int num;
    Node* left;
    Node* right;

    Node(int val) {num = val, left = nullptr, right = nullptr;}
    Node(Node* n1, Node* n2)
    {
        num = n1->num + n2->num;
        left = n1;
        right = n2;
    }
};

int N, Q;
int arr[300010];
Node* t[300010];
Query q[300010];

Node* build(int ss, int se)
{
    if (ss == se) return new Node(0);

    int mid = (ss + se) / 2;
    return new Node(build(ss, mid), build(mid + 1, se));
}

Node* update(Node* n, int a, int ss, int se)
{
    if (ss == se) return new Node(n->num + 1);
    
    int mid = (ss + se) / 2;
    if (a <= mid) return new Node(update(n->left, a, ss, mid), n->right);
    else return new Node(n->left, update(n->right, a, mid + 1, se));
}

int query(Node* l, Node* r, int tar, int ss, int se) 
{
    if (ss == se) 
    {
        if (r->num - l->num > tar) return ss;
        else return 1e9;
    }

    if (r->num - l->num <= tar) return 1e9;

    int mid = (ss + se) / 2;
    int ans = query(l->left, r->left, tar, ss, mid);
    if (ans == 1e9) ans = min(ans, query(l->right, r->right, tar, mid + 1, se));
    return ans;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    t[0] = build(1, MAXN);
    cin >> N >> Q;
    for (int i = 1; i <= N; i++) cin >> arr[i];

    for (int i = 1; i <= N; i++) t[i] = update(t[i - 1], arr[i], 1, MAXN);
    
    for (int i = 1; i <= Q; i++)
    {
        int a, b, c;
        cin >> a >> b >> c;
        int ans = query(t[a - 1], t[b], (b - a + 1) / c, 1, MAXN);
        if (ans == 1e9) cout << -1 << endl;
        else cout << ans << endl;
    }
}