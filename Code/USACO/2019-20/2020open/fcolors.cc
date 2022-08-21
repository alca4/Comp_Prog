#include<iostream>
#include<fstream>
#include<algorithm>
#include<map>
#include<vector>
using namespace std;

typedef vector<int> vi;
typedef vector<vi> vii;

int Root(int a) {return (par[a] == a) ? a : Root(par[a]);}

int N, M;
vi next_node;
vi par;
vii alist;
map<int, vi> buckets;
vi bucket;

void DFS(int id)
{
    
}

int main()
{
    ifstream fin ("fcolors.in");
    fin >> N >> M;
    par.resize(N + 1);
    next_node.resize(N + 1);
    alist.resize(M);
    bucket.resize(N + 1);
    for (int i = 0; i < M; i++) 
    {
        int a, b;
        fin >> a >> b;
        alist[b].push_back(a);
    }
}