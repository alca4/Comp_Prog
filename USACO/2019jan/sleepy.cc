#include<iostream>
#include<fstream>
#include<vector>
#include<set>
#include<algorithm>
using namespace std;

typedef vector<int> vi;

int N;
int cows[100000];

class Fenwick
{
    private:
        vi ft;
        
        int LSO(int n) {return (n & -n);}

    public:

        Fenwick(int N) {ft.assign(N + 1, 0);}

        void Update(int pos, int amount)
        {
            while (pos < ft.size()) 
            {
                ft[pos] += amount;
                pos += LSO(pos);
            }
        }

        int RSQ(int end)
        {
            int ans = 0;
            while (end > 0)
            {
                ans += ft[end];
                end -= LSO(end);
            }
            return ans;
        }

        int RSQ(int start, int end)
        {
            return RSQ(end) - RSQ(start - 1);
        }
};

int main()
{
    ifstream fin ("sleepy.in");
    fin >> N;
    for (int i = 0; i < N; i++) fin >> cows[i];

    vi temp;
    temp.push_back(cows[0]);
    for (int i = 1; i < N; i++)
    {
        if (cows[i] < cows[i - 1]) temp.clear();
        temp.push_back(cows[i]);
    }

    int rcows = N - temp.size();

    ofstream fout ("sleepy.out");
    fout << rcows << endl;

    Fenwick ftree(N);

    for (int i = 0; i < temp.size(); i++) ftree.Update(temp[i], 1);

    for (int i = 0; i < rcows; i++)
    {
        int sorted_cows = N - (rcows - i);
        fout << N - 1 - (sorted_cows - ftree.RSQ(cows[i]));
        ftree.Update(cows[i], 1);
        if (i < rcows - 1) fout << " ";
    }
    fout << endl;
    return 0;
}