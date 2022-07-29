#include<iostream>
#include<fstream>
#include<algorithm>
using namespace std;

int N, M, K;
string combo;
int learning[26][26];

int FindBest(string c)
{
    
}

int main()
{
    ifstream fin ("cowmbat.in");
    fin >> N >> M >> K;
    fin >> combo;
    for (int i = 0; i < M; i++)
    {
        for (int j = 0; j < M; j++) fin >> learning[i][j];
    }

    for (int k = 0; k < M; k++)
    {
        for (int i = 0; i < M; i++)
        {
            for (int j = 0; j < M; j++)
                learning[i][j] = min(learning[i][j],
                                     learning[i][k] + learning[k][j]);
        }
    }

    FindBest(combo);
}