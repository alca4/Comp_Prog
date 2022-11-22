#include<iostream>
#include<fstream>
#include<string.h>
#include<vector>
#include<map>
#include<algorithm>
using namespace std;

typedef pair<int, int> pii;
typedef vector<pii> vpii;

#define f first
#define s second

int N;
map<string, int> substrs;
vpii barn;
vector<string> sigs;

int main()
{
    ifstream fin("lights.in");
    fin >> N;
    barn.resize(N);
    for (int i = 0; i < N; i++)
    {
        int x, y;
        fin >> x >> y;
        barn[i] = pii(x, y);
    }
    barn.push_back(barn[0]);

    sigs.resize(N);
    for (int i = 0; i < N; i++)
    {
        //sigs[i] = DistAndDir(i);
    }
}