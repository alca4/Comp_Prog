#include<iostream>
#include<fstream>
#include<vector>
#include<map>
#include<algorithm>
using namespace std;

typedef vector<int> vi;

int N;
vi H;
map<vi, int> memo;

int DP(vi temp)
{
    if (memo.find(temp) != memo.end()) return memo[temp];
    int ans = 1;
    for (int i = 0; i < temp.size(); i++)
    {
        if (temp[i] < H[i] && temp[i + 1] < H[i + 1])
        {
            temp[i]++;
            temp[i + 1]++;
            return DP(temp);
        }
    }
}

int main()
{
    cin >> N;
    for (int i = 0; i < N; i++) cin >> H[i];
    vi temp(N - 1);
    DP(temp);
}