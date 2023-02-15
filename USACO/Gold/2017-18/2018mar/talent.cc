#include<iostream>
#include<vector>
#include<fstream>
#include<algorithm>
using namespace std;

struct Cow
{
    

    double w;
    double t;
    double r;
};

int N, W;
vector<Cow> herd;
double dp[250][250];

double FindBestRange(int start, int end) // inclusive
{
    if (start == end) return herd[start].r;
    if (dp[start][end] >= 0) return dp[start][end];

    double best = 0;
    for (int i = start; i < end; i++)
    {
        int best_here = max(max(FindBestRange(start, i), FindBestRange(i + 1, end)),
                                FindBestRange(start, i) + FindBestRange(i + 1, end));
    }
}

int main()
{
    ifstream fin ("talent.in");
    fin >> N >> W;
    herd.resize(N);

    for (int i = 0; i < N; i++) 
    {
        fin >> herd[i].w >> herd[i].t;
        herd[i].r = herd[i].t / herd[i].w;
    }

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++) dp[i][j] = -1;
    }

    //for (int i = 0; i < N; i++) cout << herd[i].r << endl;

    ofstream fout ("talent.out");
    fout << n << endl;
}