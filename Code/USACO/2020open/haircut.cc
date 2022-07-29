#include<iostream>
#include<fstream>
#include<vector>
#include<map>
#include<algorithm>
using namespace std;

typedef vector<int> vi;

struct Fenwick
{
    vi ft;

    Fenwick(int N)
    {
        ft.assign(N + 1, 0);
    }

    int LSO(int i) {return i & -i;}

    void PU(int i, int n)
    {
        while (i < ft.size())
        {
            ft[i] += n;
            i += LSO(i);
        }
    }

    int RQ(int i)
    {
        int sum = 0;
        while (i > 0)
        {
            sum += ft[i];
            i -= LSO(i);
        }
        return sum;
    }
};

int N;
map<int, vi> occ;
vector<long> ans;

int main()
{
    ifstream fin ("haircut.in");
    fin >> N;
    ans.resize(N + 1);
    Fenwick ft(N);
    for (int i = 1; i <= N; i++) 
    {
        int n;
        fin >> n;
        ft.PU(i, 1);
        occ[n].push_back(i);
    }

    ans[0] = 0;
    long total = 0;
    for (int j = 0; j < N - 1; j++)
    {
        if (occ.find(j) == occ.end()) 
        {
            ans[j + 1] = total;
            continue;
        }
        
        for (int i = 0; i < occ[j].size(); i++)
        {
            //cout << "found hair with length " << j << " at " << occ[j][i] << endl;
            ft.PU(occ[j][i], -1);
            total += ft.RQ(occ[j][i] - 1);
            //cout << "total is now " << total << endl;
        }
        ans[j + 1] = total;
    }

    ofstream fout ("haircut.out");
    for (int i = 0; i < N; i++)
    {
        fout << ans[i] << endl;
    }
    return 0;
}