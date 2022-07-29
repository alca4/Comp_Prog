#include<iostream>
#include<fstream>
#include<cmath>
#include<vector>
#include<queue>
#include<algorithm>
using namespace std;

typedef vector<int> vi;

int N;
vi start(100000);
vi barn(100000);

int main()
{
    ifstream fin ("cbarn.in");
    fin >> N;
    int id = 0;
    for (int i = 0; i < N; i++) 
    {
        fin >> barn[i];
        for (int k = 0; k < barn[i]; k++) start[id++] = i;
    }

    int min_change = 0;
    int change = 0;
    for (int i = 0; i < N; i++)
    {
        change += (barn[i] - 1);
        min_change = min(min_change, change);
    }
    min_change *= -1;

    long cost = 0;
    for (int i = 0; i < N; i++)
        cost += pow((min_change + i - start[i] + N) % N, 2);
    ofstream fout ("cbarn.out");
    fout << cost << endl;
    return 0;
}