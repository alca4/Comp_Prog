#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include <set>
using namespace std;

#define ll long long

int N;
int color[100010];
set<int> child[100010];
map<int, int> occ[100010]; // maps color to number of appearances
map<int, ll> freq[100010];
ll ans[100010];
int at[100010];

void insert(int n, int v, int t)
{
    if (occ[at[n]].find(v) == occ[at[n]].end()) freq[at[n]][t] += v;
    else
    {
        freq[at[n]][occ[n][v]] -= v;
        freq[at[n]][occ[n][v] + t] += v;
    }
    occ[at[n]][v] += t;
}

int combine(int i, int j)
{
    if (occ[i].size() < occ[j].size()) swap(i, j);
    for (auto n : occ[j]) insert(i, n.first, n.second);
    return i;
}

void solve(int n)
{
    insert(n, color[n], 1);
    for (auto c : child[n])
    {
        solve(c);
        at[n] = combine(at[n], at[c]);
    }
    ans[n] = freq[at[n]].rbegin()->second;
}

void DFS(int n)
{
    for (auto c : child[n])
    {
        child[c].erase(n);
        DFS(c);
    }
}

int main()
{
    scanf("%d", &N);
    for (int i = 1; i <= N; i++) 
    {
        at[i] = i;
        scanf("%d", &color[i]);
    }
    for (int i = 1; i <= N - 1; i++)
    {
        int a, b;
        scanf("%d%d", &a, &b);
        child[a].insert(b);
        child[b].insert(a);
    }

    DFS(1);
    solve(1);
    for (int i = 1; i <= N; i++) printf("%lld ", ans[i]);
    printf("\n");
    return 0;
}