/*
LEARNINGS:
Arrays should not take up much space
Queues might, so check if something absolutely needs to enter a queue
before actually inserting it in
*/
#include<iostream>
#include<algorithm>
#include<vector>
#include<bitset>
#include<queue>
#include<set>
using namespace std;

typedef pair<int, int> pii;

int N, M, K;;
int bitland[1010][1010];
//int visited[1010][1010];

set<int> nbs[1000010];
bitset<1000010> vis;
int lo[1000010];
int num[1000010];
int szs[1000010];
int ans[1000010];
bitset<1000010> iscv;

void Sizes(int cur)
{
    szs[cur] = 1;
    vis[cur] = 1;
    for (auto n : nbs[cur])
        if (!vis[n]) 
        {
            Sizes(n);
            szs[cur] += szs[n];           
        }
}

int counter = 0;
void Tarjan(int cur, int prev)
{
    //cout << cur << endl;
    num[cur] = ++counter;
    vis[cur] = 1;
    lo[cur] = num[cur];
    for (auto tar : nbs[cur])
    {
        if (tar == prev) continue;
        if (!num[tar]) 
        {
            Tarjan(tar, cur);
            lo[cur] = min(lo[cur], lo[tar]);
            //szs[cur] += szs[tar];
            if (lo[tar] >= num[cur]) 
            {
                //cout << cur << " gained subtree of size " << szs[tar] << " from " << tar << endl;
                //szs[cur] += szs[tar];
                ans[cur] += szs[tar];
            }
        }
        else if (vis[tar]) lo[cur] = min(lo[cur], num[tar]);
    }
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    cin >> N >> M;
    K = 0;
    for (int i = 0; i <= N + 1; i++)
        for (int j = 0; j <= M + 1; j++)
        {
            if (i == 0 || j == 0 || i > N || j > M) bitland[i][j] = 0;
            else 
                cin >> bitland[i][j], K = max(K, bitland[i][j]);
        }
    for (int i = 0; i <= N; i++)
        for (int j = 0; j <= M; j++)
            {
                if (bitland[i][j] != bitland[i + 1][j])
                {
                    nbs[bitland[i][j]].insert(bitland[i + 1][j]);
                    nbs[bitland[i + 1][j]].insert(bitland[i][j]);
                }
                if (bitland[i][j] != bitland[i][j + 1])
                {
                    nbs[bitland[i][j]].insert(bitland[i][j + 1]);
                    nbs[bitland[i][j + 1]].insert(bitland[i][j]);
                }
            }

    /*
    for (int i = 0; i <= K; i++)
    {
        cout << "Island " << i << " has nbs: ";
        for (auto n : nbs[i])
            cout << n << " ";
        cout << endl;  
    }
    */
    Sizes(0);
    for (int i = 0; i <= K; i++) vis[i] = 0;
    Tarjan(0, -1);
    /*
    for (int i = 0; i <= K; i++)
        cout << lo[i] << " " << num[i] << endl;
        */
    for (int i = 1; i <= K; i++)
        cout << ans[i] << " ";
    cout << endl;
    return 0;
}