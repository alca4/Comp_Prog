#include<iostream>
#include<fstream>
#include<algorithm>
#include<vector>
#include<bitset>
#include<map>
using namespace std;

typedef pair<int, int> pii;
typedef pair<pii, pii> ppii;
typedef vector<int> vi;
typedef vector<ppii> v;
#define f first
#define s second

int N, P;
map<int, int> mappy;
v boards(100000);

bool Comp(const ppii& p1, const ppii& p2)
{
    return (p1.f.f + p1.f.s < p2.f.f + p2.f.s);
}

struct Segment
{
    
};

int main()
{
    ifstream fin("boards.in");
    fin >> N >> P;
    for (int i = 0; i < P; i++) 
        fin >> boards[i].f.f >> boards[i].f.s >> boards[i].s.f >> boards[i].s.s;
    sort(boards.rbegin(), boards.rend(), Comp);
    for (int i = 0; i < P; i++) 
        cout << boards[i].f.f << " " << boards[i].f.s << " "
             << boards[i].s.f << " " << boards[i].s.s << endl;
    for (int i = 0; i < P; i++)
    {
         
    }
}