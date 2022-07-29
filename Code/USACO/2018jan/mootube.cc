#include<iostream>
#include<fstream>
#include<vector>
#include<utility>
#include<algorithm>
using namespace std;

typedef pair<int, int> pii;
typedef vector<int> vi;

struct query
{
    int video;
    int min_r;
    int id;    
};

int N, Q;
int par[100001];
int gsize[100001];
// weight, n1, n2
vector<pair<int, pii>> edges(100001);
vector<query> qs(100001);
int ans[100001];

bool CompR(const query& q1, const query& q2)
{
    return q1.min_r < q2.min_r;
}

int Root(int a)
{
    int temp = a;
    while (temp != par[temp]) temp = par[temp];
    return temp;
}

void Combine(int a, int b)
{
    a = Root(a);
    b = Root(b);
    if (gsize[a] > gsize[b]) 
    {
        gsize[a] += gsize[b];
        par[b] = a;
    }
    else
    {
        gsize[b] += gsize[a];
        par[a] = b;
    }
}

int main()
{
    ifstream fin ("mootube.in");
    fin >> N >> Q;
    for (int i = 0; i < N - 1; i++)
    {
        fin >> edges[i].second.first >> edges[i].second.second
            >> edges[i].first;
    }
    for (int i = 1; i <= Q; i++)
    {
        fin >> qs[i].min_r >> qs[i].video;
        qs[i].id = i;
    }
    for (int i = 1; i <= N; i++) 
    {
        gsize[i] = 1;
        par[i] = i;
    }

    sort(qs.rbegin(), qs.rend(), CompR);
    sort(edges.rbegin(), edges.rend());

    int e_index = 0;
    for (int i = 0; i < Q; i++)
    {
        /*
        for (int i = 1; i <= N; i++)
        {
            cout << "parent of " << i << " is " << par[i] << endl;
            cout << "group size of " << i << " is " << gsize[i] << endl;
        }
        */
        //cout << "answering " << i + 1 << " query" << endl;
        while (e_index < edges.size() && edges[e_index].first >= qs[i].min_r)
        {
            
            pair<int, pii>& edge = edges[e_index];
            Combine(edge.second.first, edge.second.second);
            e_index++;
            /*
            cout << "opened edge between " << edge.second.first
                 << " and " << edge.second.second << endl;
            */
        }
        //cout << "answer is " << gsize[qs[i].video] - 1 << endl;
        ans[qs[i].id] = gsize[Root(qs[i].video)] - 1;
    }
    ofstream fout ("mootube.out");
    for (int i = 1; i <= Q; i++) fout << ans[i] << endl;
    return 0;
}
