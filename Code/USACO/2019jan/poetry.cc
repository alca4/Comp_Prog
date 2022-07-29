#include<iostream>
#include<fstream>
#include<vector>
#include<map>
#include<bitset>
#include<algorithm>
using namespace std;

typedef vector<int> vi;
typedef vector<vi> vii;
typedef pair<int, int> pii;
typedef vector<pii> vpii;

int N, M, K;
pii words[5000];
int memo[]; // solutions
bitset<5000> visited;
map<char, int> rhyme;

vi DP(int remaining)
{
    //if (visited[remaining]) return memo[remaining];
    visited.flip(remaining);
    vi ans;
    for (int i = 0; i < N; i++)
    {

    }
}

int main()
{
    ifstream fin ("poetry.in");
    fin >> N >> M >> K;
    for (int i = 0; i < N; i++) 
    {
        fin >> words[i].first >> words[i].second;
    }
    for (int i = 0; i < M; i++) 
    {
        char c;
        fin >> c;
        rhyme[c]++;
    }

/*
    for (int i = 0; i < N; i++)
        memo[i].resize(N);
*/
    DP(N);
}