#include<iostream>
#include<fstream>
#include<vector>
#include<algorithm>
using namespace std;

typedef vector<long> vi;
typedef pair<long, long> pii;
typedef vector<pii> vpii;
#define x first
#define y second

int N;
vpii cows;

int main()
{
    ifstream fin ("split.in");
    fin >> N;
    cows.resize(N);
    for (int i = 0; i < N; i++) fin >> cows[i].x >> cows[i].y;

    sort(cows.begin(), cows.end());

    vi left_sums(N);
    long min_y = 1e9;
    long max_y = 0;
    for (int i = 0; i < N; i++)
    {
        min_y = min(min_y, cows[i].y);
        max_y = max(max_y, cows[i].y);
        left_sums[i] = (cows[i].x - cows[0].x) * 
                       (max_y - min_y);
    }

    vi right_sums(N);
    min_y = 1e9;
    max_y = 0;
    for (int i = N - 1; i >= 0; i--)
    {
        min_y = min(min_y, cows[i].y);
        max_y = max(max_y, cows[i].y);
        right_sums[i] = (cows[N - 1].x - cows[i].x) * 
                       (max_y - min_y);
    }

    long tot_sum = right_sums[0];
    long min_sum = tot_sum;
    for (int i = 0; i < N - 1; i++)
        min_sum = min(min_sum, left_sums[i] + right_sums[i + 1]);
    
    ofstream fout ("split.out");
    fout << tot_sum - min_sum << endl;
    return 0;
}