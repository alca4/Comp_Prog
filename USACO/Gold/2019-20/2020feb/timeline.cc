#include<iostream>
#include<fstream>
#include<vector>
#include<queue>
#include<algorithm>
using namespace std;

typedef vector<int> vi;
typedef pair<int, int> pii;
typedef vector<pii> vpii;
#define f first
#define s second

int N, M, C;
vector<vpii> memories;
vi ans;
vi indeg;

int main()
{
    ifstream fin("timeline.in");
    fin >> N >> M >> C;
    ans.resize(N + 1);
    indeg.resize(N + 1);
    memories.resize(N + 1);
    for (int i = 1; i <= N; i++) fin >> ans[i];
    for (int i = 1; i <= C; i++)
    {
        int a, b, c;
        fin >> a >> b >> c;
        memories[a].push_back(pii(b, c));
        indeg[b]++;
    }

    queue<int> topsort;
    for (int i = 1; i <= N; i++)
        if (indeg[i] == 0) topsort.push(i);

    while (!topsort.empty())
    {
        int n = topsort.front();
        topsort.pop();

        for (int i = 0; i < memories[n].size(); i++)
        {
            int d = memories[n][i].f;
            int w = memories[n][i].s;
            if (ans[d] < ans[n] + w) ans[d] = ans[n] + w;
            indeg[d]--;
            if (indeg[d] == 0) topsort.push(d);
        }
    }

    ofstream fout("timeline.out");
    for (int i = 1; i <= N; i++) fout << ans[i] << endl;
    return 0;
}