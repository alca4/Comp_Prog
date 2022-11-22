#include<iostream>
#include<fstream>
#include<vector>
#include<queue>
#include<algorithm>
using namespace std;

typedef vector<int> vi;
typedef pair<int, int> pii;
typedef pair<int, pii> piii;
#define f first
#define s second

int Encode(pii x) {return x.f * 2002 + x.s;}
pii Decode(int x) {return pii(x / 2002, x % 2002);}

int A, B, N, M;
vi x_fences;
vi y_fences;
int par[5000000];
int r[5000000];

int Root(int a) {return a == par[a] ? a : Root(par[a]);}
bool isSameSet(int a, int b) {return Root(a) == Root(b);}
void Union(int a, int b)
{
    // a and b are guaranteed isSameSet(a, b) is false
    a = Root(a);
    b = Root(b);
    if (r[a] > r[b]) par[b] = a;
    else
    {
        par[a] = b;
        if (r[a] == r[b]) r[b]++;
    }
}

struct CompPIII
{
    bool operator() (const piii& p1, const piii& p2)
    {
        if (p1.f == p2.f)
        {
            if (p1.s.f == p2.s.f) return p1.s.s > p2.s.s;
            return p1.s.f > p2.s.f;
        }
        return p1.f > p2.f;
    }
};

int main()
{
    ifstream fin ("fencedin.in");
    fin >> A >> B >> N >> M;
    x_fences.resize(N + 2);
    x_fences[0] = 0;
    for (int i = 1; i <= N; i++) fin >> x_fences[i];
    x_fences[N + 1] = A;
    y_fences.resize(M + 2);
    y_fences[0] = 0;
    for (int i = 1; i <= M; i++) fin >> y_fences[i];
    y_fences[M + 1] = B;

    sort(x_fences.begin(), x_fences.end());
    sort(y_fences.begin(), y_fences.end());

    priority_queue<piii, vector<piii>, CompPIII> edges;
    for (int i = 0; i < N + 1; i++)
    {
        for (int j = 0; j < M; j++)
        {
            int w = x_fences[i + 1] - x_fences[i];
            int n1 = Encode(pii(i, j));
            int n2 = Encode(pii(i, j + 1));
            /*
            cout << "edge from " << i << ", " << j << " to " 
                 << i << ", " << j + 1 
                 << " of length " << w << endl;
            */
            edges.push(piii(w, pii(n1, n2)));
        }
    }
    for (int i = 0; i < M + 1; i++)
    {
        for (int j = 0; j < N; j++)
        {
            int w = y_fences[i + 1] - y_fences[i];
            int n1 = Encode(pii(j, i));
            int n2 = Encode(pii(j + 1, i));
            /*
            cout << "edge from " << j << ", " << i << " to " 
                 << j + 1 << ", " << i
                 << " of length " << w << endl;
            */
            edges.push(piii(w, pii(n1, n2)));
        }
    }

    for (int i = 0; i < 5000000; i++) par[i] = i, r[i] = 0;

    long cost = 0;
    int c = 0;
    int e_used = 0;
    while (e_used < (N + 1) * (M + 1) - 1)
    {
        c++;
        piii info = edges.top();
        int w = info.f;
        int n1 = info.s.f;
        int n2 = info.s.s;
        edges.pop();

        if (isSameSet(n1, n2)) continue;
        else e_used++;

        cost += w;
        /*
        cout << "using edge from " << Decode(n1).f << ", " << Decode(n1).s
             << " to " << Decode(n2).f << ", " << Decode(n2).s 
             << " of length " << w << endl;
        */
        Union(n1, n2);
    }
    cout << c << endl;

    ofstream fout ("fencedin.out");
    fout << cost << endl;
    return 0;
}