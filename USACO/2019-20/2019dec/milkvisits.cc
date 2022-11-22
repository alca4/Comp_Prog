#include<iostream>
#include<fstream>
#include<vector>
#include<bitset>
using namespace std;

typedef vector<int> vi;
typedef vector<vi> vii;

int N, M;
int milk[100001];
int par[100001];
int depth[100001];
vii edges;
string ans;

void ConstructTree(int n)
{
    for (int i = 0; i < edges[n].size(); i++)
    {
        if (edges[n][i] != par[n])
        {
            //cout << edges[n][i] << "'s parent is " << n << endl;
            par[edges[n][i]] = n;
            depth[edges[n][i]] = depth[n] + 1;
            cout << "depth of " << edges[n][i] << " is " << depth[n] + 1 << endl;
            ConstructTree(edges[n][i]);
        }
    }
}

int main()
{
    ifstream fin("milkvisits.in");
    fin >> N >> M;
    edges.resize(N + 1);
    for (int i = 1; i <= N; i++) fin >> milk[i];
    for (int i = 1; i < N; i++)
    {
        int a, b;
        fin >> a >> b;
        edges[a].push_back(b);
        edges[b].push_back(a);
    }
    par[1] = 1;
    depth[1] = 0;
    ans = "";
    for (int i = 0; i < M; i++) ans += '0';
    ConstructTree(1);
    for (int i = 0; i < M; i++)
    {
        int b1, b2, chosen;
        fin >> b1 >> b2 >> chosen;
        if (milk[b1] == chosen || milk[b2] == chosen) 
        {
            ans[i] = '1';
            continue;
        }
        while (b1 != b2)
        {
            if (depth[b1] > depth[b2])
            {
                b1 = par[b1];
                if (milk[b1] == chosen) 
                {
                    ans[i] = '1';
                    break;
                }
            }
            else if (depth[b1] < depth[b2])
            {
                b2 = par[b2];
                if (milk[b2] == chosen) 
                {
                    ans[i] = '1';
                    break;
                }
            }
            else if (depth[b1] == depth[b2])
            {
                b1 = par[b1];
                b2 = par[b2];
                //cout << b1 << " " << b2 << endl;
                if (milk[b1] == chosen || milk[b2] == chosen) 
                {
                    ans[i] = '1';
                    break;
                }
            }
        }
    }
    ofstream fout ("milkvisits.out");
    fout << ans << endl;
    return 0;
}