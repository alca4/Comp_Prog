#include<iostream>
#include<fstream>
#include<algorithm>
using namespace std;

int N, K;
int snakes[400];
int memo[401][401][401]; // index, size of current group, k

int DP(int i, int k)
{
    
}

int main()
{
    ifstream fin("snakes.in");
    fin >> N >> K;
    for (int i = 0; i < N; i++) fin >> snakes[i];
    for (int i = 1; i <= N; i++)
    {
        for (int j = 1; j <= N; j++)
        {
            for (int k = 1; k <= N; k++) memo[i][j][k] = 0;
        }
    }
}