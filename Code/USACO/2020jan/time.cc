#include<iostream>
#include<fstream>
#include<vector>
#include<queue>
#include<algorithm>
using namespace std;

typedef pair<int, int> pii;
#define f first
#define s second
typedef vector<int> vi;
typedef vector<pii> vpii;

int N, M, C;
vi rev;
vpii roads;
vpii home;
vi memo;

int main()
{
    ifstream fin ("time.in");
    fin >> N >> M >> C;
    rev.resize(N + 1);
    home.resize(N + 1);
    memo.resize(N + 1);
    roads.resize(M);
    for (int i = 1; i <= N; i++) fin >> rev[i];
    for (int i = 0; i < M; i++) fin >> roads[i].f >> roads[i].s;

    
}
