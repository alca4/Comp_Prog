/*
{O,O}
/)_)
 " "
Rowlet the Owlet
*/

#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
using namespace std;

typedef pair<int, int> pii;

struct Node
{
    // min value, location * -1
    pii v;
    Node* l;
    Node* r;

    Node(pii val) {v = val; l = nullptr; r = nullptr;}
    Node(Node* left, Node* right)
    {
        v = min(left->v, right->v);
        l = left;
        r = right;
    }
};

Node* build(int ss, int se)
{
    if (ss == se) return new Node(pii(1e9, ss * -1));
    int mid = (ss + se) / 2;
    return new Node(build(ss, mid), build(mid + 1, se));
}

Node* update(Node* n, int a, int val, int ss, int se)
{
    if (ss == se) return new Node(pii(val, a * -1));

    int mid = (ss + se) / 2;
    if (a <= mid) return new Node(update(n->l, a, val, ss, mid), n->r);
    else return new Node(n->l, update(n->r, a, val, mid + 1, se));
}

pii query(Node* n, int a, int b, int ss, int se)
{
    
    if (se < a || b < ss) return pii(1e9, 0);
    //cout << ss << " " << se << endl;
    if (a <= ss && se <= b)
    {
        if (n->v.first < a) return n->v;
        else return pii(1e9, 0);
    }

    if (ss == se) return pii(1e9, 0);
    
    int mid = (ss + se) / 2;
    pii a1 = pii(1e9, 0);
    pii a2 = pii(1e9, 0);
    if (a <= mid) a1 = query(n->l, a, b, ss, mid);
    if (b > mid) a2 = query(n->r, a, b, mid + 1, se);
    return min(a1, a2);
}

int N, Q;
int arr[500010];
Node* roots[500010];
int lastocc[500010];

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    scanf("%d", &N);
    roots[0] = build(1, N);
    map<int, int> last;
    for (int i = 1; i <= N; i++)
    {
        scanf("%d", &arr[i]);
        Node* cur = roots[i - 1];
        if (last.find(arr[i]) == last.end()) last[arr[i]] = -1;
        if (last[arr[i]] != -1) cur = update(cur, last[arr[i]], 1e9, 1, N);
        cur = update(cur, i, last[arr[i]], 1, N);
        last[arr[i]] = i;
        roots[i] = cur;
    }

    /*
    for (int j = 0; j <= N; j++)
    {
        for (int i = 1; i <= N; i++)
        {
            cout << query(roots[j], i, i, 1, N) << " ";
        }
        cout << endl;
    }
    */

    scanf("%d", &Q);
    while (Q--)
    {
        int a, b;
        scanf("%d%d", &a, &b);
        pii ans = query(roots[b], a, b, 1, N);
        //cout << ans.second * -1 << endl;
        if (ans.second * -1 < a) printf("0\n");
        else printf("%d\n", arr[ans.second * -1]);
    }
    return 0;
}