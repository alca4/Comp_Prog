#include<iostream>
#include<fstream>
#include<vector>
#include<bitset>
#include<set>
#include<algorithm>
using namespace std;

struct boot
{
    int s;
    int d;
    int id;
};

struct tile
{
    int d;
    int id;
};

int N, B;
vector<boot> inv;
vector<tile> snow;
bitset<100000> ans;
multiset<int, less<int>> interval;
multiset<int, greater<int>> len;


bool CompBootD(const boot& b1, const boot& b2)
{
    return b1.d < b2.d;
}

bool CompTileD(const tile& t1, const tile& t2)
{
    return t1.d < t2.d;
}

void OpenTile(int a)
{
    cout << "trying to open tile " << a << endl;
    auto ub = interval.upper_bound(a);
    auto lb = ub--;
    int lower = *ub;
    int upper = *lb;
    cout << lower << " " << upper << endl;
    len.erase(len.find(upper - lower));
    len.insert(a - lower);
    len.insert(upper - a);
    interval.insert(a);
}

int main()
{
    ifstream fin ("snowboots.in");
    fin >> N >> B;
    int t1, t2;
    fin >> t1;
    inv.resize(N);
    snow.resize(N - 2);
    for (int i = 1; i < N - 1; i++) 
    {
        fin >> snow[i - 1].d;
        snow[i - 1].id = i;
    }
    fin >> t2;
    for (int i = 0; i < B; i++) 
    {
        fin >> inv[i].d >> inv[i].s;
        inv[i].id = i;
    }
    interval.insert(0);
    interval.insert(N - 1);
    len.insert(N - 1);

    sort(inv.begin(), inv.end(), CompBootD);
    sort(snow.rbegin(), snow.rend(), CompTileD);


    for (int i = 0; i < N; i++)
    {
        cout << "trying boot " << inv[i].id << endl;
        while (snow.size() > 0 && inv[i].d >= snow[snow.size() - 1].d)
        {
            OpenTile(snow[snow.size() - 1].id);
            snow.pop_back();
        }
        cout << *len.begin() << " is the max interval " << endl;
        if (*len.begin() <= inv[i].s) ans.flip(inv[i].id);
    }
    ofstream fout ("snowboots.out");
    for (int i = 0; i < B; i++)
    {
        fout << ans[i] << endl;
    }
    return 0;
}