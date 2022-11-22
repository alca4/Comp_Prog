#include<iostream>
#include<fstream>
#include<vector>
#include<queue>
#include<algorithm>
using namespace std;

int N, K;
int barns[100000];
vector<vector<int>> nbs(100000);

int main()
{
    ifstream fin ("barnpainting.in");
    fin >> N >> K;
    for (int i = 0; i < N - 1; i++)
    {
        int b1, b2;
        fin >> b1 >> b2;
        nbs[b1].push_back(b2);
        nbs[b2].push_back(b1);
    }
    for (int i = 0; i < N; i++) barns[i] = 7;
    for (int i = 0; i < K; i++) fin >> barns[i];
    queue<int> bfs;
    bfs.push(0);
    while (!bfs.empty())
    {
        int n = bfs.front();
        bfs.pop();
        
    }
    return 0;
}