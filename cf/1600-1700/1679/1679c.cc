#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

struct Node
{
    int v;
    Node* l;
    Node* r;

    Node(int a) {v = a; l = nullptr; r = nullptr;}
    Node(Node* n1, Node* n2)
    {
        if (n1->v > 0 && n2->v > 0) v = 1;
        else v = 0;
        l = n1;
        r = n2;
    }
};

Node* build(int ss, int se)
{
    if (ss == se) return new Node(0);

    int mid = (ss + se) / 2;
    return new Node(build(ss, mid), build(mid + 1, se));
}

Node* update(Node* n, int a, int v, int ss, int se)
{
    if (ss == se) return new Node(n->v + v);

    int mid = (ss + se) / 2;
    if (a <= mid) return new Node(update(n->l, a, v, ss, mid), n->r);
    else return new Node(n->l, update(n->r, a, v, mid + 1, se));
}

bool query(Node* n, int a, int b, int ss, int se)
{
    if (a <= ss && se <= b) return n->v;

    int mid = (ss + se) / 2;
    bool ans = 1;
    if (a <= mid) ans = (ans && query(n->l, a, b, ss, mid));
    if (b > mid) ans = (ans && query(n->r, a, b, mid + 1, se));
    return ans;
}

int N, Q;

int main()
{
    scanf("%d%d", &N, &Q);
    Node* x = build(1, N);
    Node* y = build(1, N);
    for (int i = 1; i <= Q; i++)
    {
        int t;
        scanf("%d", &t);
        if (t == 1) 
        {
            int x1, y1;
            scanf("%d%d", &x1, &y1);
            x = update(x, x1, 1, 1, N);
            y = update(y, y1, 1, 1, N);
        }
        if (t == 2) 
        {
            int x1, y1;
            scanf("%d%d", &x1, &y1);
            x = update(x, x1, -1, 1, N);
            y = update(y, y1, -1, 1, N);
        }
        if (t == 3)
        {
            int x1, y1, x2, y2;
            scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
            bool ans = query(x, x1, x2, 1, N) || 
                       query(y, y1, y2, 1, N);
            if (ans) printf("Yes\n");
            else printf("No\n");
        }
    }
}