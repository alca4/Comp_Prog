/*
Idea: Greedy
Just find the three points with the greatest distance. 
*/
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <math.h>
#include <bitset>
#include <vector>
using namespace std;

struct Seg
{
    int i;
    int j;
    double dist;
};

bool operator < (const Seg& s1, const Seg& s2) {return s1.dist < s2.dist;}

int N;
double ans;
double x[3001];
double y[3001];
vector<Seg> dists;
bitset<3001> nbs[3001];

double Dist(int a, int b) 
{
    return pow(x[a] - x[b], 2.0) + pow(y[a] - y[b], 2.0);
}


int main()
{
    cin >> N;
    for (int i = 1; i <= N; i++) cin >> x[i] >> y[i];
    for (int i = 1; i < N; i++)
    {
        for (int j = i + 1; j <= N; j++) 
        {
            if (i == j) continue;
            Seg s;
            s.i = i;
            s.j = j;
            s.dist = Dist(i, j);
            dists.push_back(s);
        }   
    }

    sort(dists.rbegin(), dists.rend());

    for (int k = 0; k < dists.size(); k++)
    {
        int i = dists[k].i;
        int j = dists[k].j;
        if ((nbs[dists[k].i] & nbs[dists[k].j]).any())
        {
            cout << setprecision(12) << sqrt(dists[k].dist) / 2 << endl;
            return 0;
        }
        nbs[i][j] = 1;
        nbs[j][i] = 1;
    }
    return 0;
}