#include<iostream>
#include<fstream>
#include<algorithm>
using namespace std;

int N, K;
int best[10000];
int skill[10000];

void DP()
{
    int max_skill = -1e9;
    for (int i = 0; i < K; i++)
    {
        max_skill = max(max_skill, skill[i]);
        best[i] = (i + 1) * max_skill;
    }

    for (int i = K; i < N; i++)
    {
        int best_choice = -1e9;
        max_skill = -1e9;
        for (int j = 0; j < K; j++)
        {
            max_skill = max(max_skill, skill[i - j]);
            best_choice = max(best_choice, (j + 1) * max_skill + best[i - j - 1]);
        }
        best[i] = best_choice;
    }
}

int main()
{
    ifstream fin ("teamwork.in");
    fin >> N >> K;
    for (int i = 0; i < N; i++)
    {
        fin >> skill[i];
    }

    DP();
    ofstream fout ("teamwork.out");
    fout << best[N - 1] << endl;
}