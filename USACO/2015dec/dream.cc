#include<iostream>
#include<fstream>
#include<vector>
#include<queue>
#include<algorithm>
using namespace std;

#define f first
#define s second

typedef pair<int, int> pii;
typedef vector<int> vi;

int N, M;
int grid[1000][1000];
int memo[1000][1000];

int Encode(pii i) {return i.f * 1000 + i.s;}
pii Decode(int i) {return pii(i / 1000, i % 1000);}
int Inc(int i) {return i > 0 ? ++i : --i;}
pii Move(pii loc, int dir)
{
    if (dir == 1) return pii(loc.f + 1, loc.s);
    if (dir == 2) return pii(loc.f, loc.s + 1);
    if (dir == 3) return pii(loc.f - 1, loc.s);
                  return pii(loc.f, loc.s - 1);
}

// dir: 1 x + 1, 2 y + 1, 3 x - 1, 4 y - 1
// len > 0: not oranges, len < 0: oranges
pii Visit(int dir, const pii& vis, int len)
{
    int x = vis.f;
    int y = vis.s;

    if (x >= N || y >= M || x < 0 || y < 0) return pii(-1, len);
    if (grid[x][y] == 0 || (grid[x][y] == 3 && len > 0)) return pii(-1, len);

    if (grid[x][y] == 1 || (grid[x][y] == 3 && len < 0)) 
        return pii(Encode(vis), Inc(len));
    if (grid[x][y] == 2) return pii(Encode(vis), -1 * abs(Inc(len)));

    pii end = Visit(dir, Move(vis, dir), abs(Inc(len)));
    if (end.f == -1) return vis;
    else return end;
}

int main()
{
    ifstream fin("dream.in");
    fin >> N >> M;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++) 
        {
            fin >> grid[i][j];
            memo[i][j] = 0;
        }
    }

    queue<pii> q;
    q.push(pii(0, 1));
    ofstream fout("dream.out");
    while (!q.empty())
    {
        pii coords = Decode(q.front().f);
        int x = coords.f;
        int y = coords.s;
        int len = q.front().s;     
        q.pop();
        /*
        cout << "============================" << endl;
        cout << "visiting " << x << " " << y << endl;
        cout << "length is " << len << endl;
        */

        if (x == N - 1 && y == M - 1)
        {
            fout << abs(len) - 1 << endl;
            return 0;
        }

        if (memo[x][y] == 1) continue;
        memo[x][y] = 1;

        vector<pii> nbs;
        nbs.push_back(Visit(1, pii(x + 1, y), len));
        nbs.push_back(Visit(2, pii(x, y + 1), len));
        nbs.push_back(Visit(3, pii(x - 1, y), len));
        nbs.push_back(Visit(4, pii(x, y - 1), len));

        for (auto n : nbs) 
        {
            pii target = Decode(n.f);
            
            if (n.f != -1 && memo[target.f][target.s] == 0) 
            {
                //cout << "going to " << target.f << " " << target.s << endl;
                q.push(n);
            }
        }
    }
    fout << -1 << endl;
    return 0;
}