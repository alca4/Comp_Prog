#include<iostream>
#include<fstream>
#include<bitset>
#include<algorithm>
#include<vector>
using namespace std;

typedef vector<int> vi;

int N;
vi b1, e1, b2, e2;

int main()
{
    ifstream fin("cardgame.in");
    fin >> N;
    b1.reserve(N / 2 + 1), b1.push_back(0);
    b2.reserve(N + 1), b2.push_back(0);
    e1.assign(N / 2 + 1, 0);
    e2.assign(N / 2 + 1, 0);
    bitset<100001> e_has;

    for (int i = 1; i <= N / 2; i++) {fin >> e1[i]; e_has.flip(e1[i]);}
    for (int i = 1; i <= N / 2; i++) {fin >> e2[i]; e_has.flip(e2[i]);}
    for (int i = 1; i <= N * 2; i++) if (!e_has[i]) b2.push_back(i);
    
    sort(b2.begin(), b2.end());

    for (int i = N / 2 + 1; i <= N; i++) b1.push_back(b2[i]);
    b2.resize(N / 2 + 1);
    sort(e1.begin(), e1.end());
    sort(e2.begin(), e2.end());

    int points = 0;
    int b = 1, e = 1;
    while (b <= N / 2 && e <= N / 2)
    {
        if (b1[b] > e1[e]) 
        {
            points++;
            b++;
            e++;
        }
        else b++;
    }

    b = N / 2, e = N / 2;
    while (b >= 1 && e >= 1)
    {
        if (b2[b] < e2[e]) 
        {
            points++;
            b--;
            e--;
        }
        else b--;
    }

    ofstream fout ("cardgame.out");
    fout << points << endl;

    return 0;
}