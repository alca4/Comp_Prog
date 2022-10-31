/*
Idea: graph
Resolve cycles by turning any subset of their edges
*/
#include <iostream>
#include <algorithm>
#include <vector>
#include <stack>
#include <map>
using namespace std;

#define v vector
#define MOD 1000000007

int N;
int e[200010];
int lowlink[200010];
int vis[200010];
int indeg[200010];
int in_stack[200010];
long long pow2[200010];
map<int, int> groups;

void DFS(int cur, int start)
{
    if (vis[cur])
    {
        if (lowlink[cur] == 0) lowlink[cur] = start;
        return;
    }
    vis[cur] = 1;
    DFS(e[cur], start);
    lowlink[cur] = min(start, lowlink[e[cur]]);
    groups[lowlink[cur]]++;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> N;
    for (int i = 1; i <= N; i++) cin >> e[i];
    pow2[0] = 1;
    for (int i = 1; i <= N; i++) pow2[i] = (pow2[i - 1] * 2) % MOD;

    long long ans = 1;
    for (int i = 1; i <= N; i++)
    {
        if (vis[i]) continue;
        DFS(i, i);
    }

    for (auto n : groups)
    {
        stack<int> towns;
        towns.push(n.first);
        while (!in_stack[towns.top()])
        {
            in_stack[towns.top()] = 1;
            towns.push(e[towns.top()]);
        }
        int dup = towns.top();
        int count = 1;
        towns.pop();
        while (towns.top() != dup) towns.pop(), count++;
        long long a = (ans % MOD);
        long long b = ((pow2[count] - 2) * (pow2[n.second - count])) % MOD;
        ans = (a * b) % MOD;
    }
    cout << ans << endl;

    //for (int i = 1; i <= N; i++) cout << lowlink[i] << endl;
    //for (auto n : groups) cout << n.first << " group has size " << n.second << endl;
    return 0;
}