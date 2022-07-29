#include<iostream>
#include<algorithm>
#include<set>
#include<map>
#include<vector>
using namespace std;

typedef vector<int> vi;
typedef pair<int, int> pii;
typedef vector<pii> vpii;

class Fenwick
{
    private:
        vi ft;
        int LSO(int a) {return a & -a;}
    public:
        Fenwick(int N) {ft.assign(N + 1, 0);}

        void PU(int i, int d) 
        {
            while (i < ft.size())
            {
                ft[i] += d;
                i += LSO(i);
            }            
        }

        int RSQ(int a)
        {
            int sum = 0;
            while (a > 0)
            {
                sum += ft[a];
                a -= LSO(a);
            }
            return sum;
        }

        int RSQ(int a, int b)
        {
            return RSQ(b) - RSQ(a - 1);
        }
};

int N;
vi perm;

int main()
{
    cin >> N;
    perm.resize(N + 1);
    for (int i = 1; i <= N; i++) cin >> perm[i];
    map<int, int> upper;
    map<int, int> lower;
    map<int, int> uorder;
    map<int, int> lorder;
    Fenwick visited(N);
    int ub = N + 1;
    int lb = -1;
    for (int i = 2; i <= N; i++)
    {
        int cur = perm[i];
        int prev = perm[i - 1];
        if (cur < prev)
        {
            if (visited.RSQ(cur, cur) == 0) visited.PU(cur, 1);
            if (visited.RSQ(prev, prev) == 0) visited.PU(prev, 1);
            upper[prev] = visited.RSQ(prev + 1, N);
            cout << prev << " has " << visited.RSQ(prev + 1, N) << 
                           " greater elements" << endl;
            lower[cur] = visited.RSQ(1, cur - 1);
            cout << cur << " has " << visited.RSQ(1, cur - 1) << 
                            " lesser elements" << endl;
            uorder[prev] = i;
            lorder[cur] = i;
        }
    }
    vi ans(N + 1);
    for (int i = 0; i <= N; i++)
    {
        if (i == 0) ans[i] = lower[1];
        else if (i == N) ans[i] = upper[N];
        else 
        {
            cout << "i is: " << i << endl;
            cout << "has " << lower[i] << " less than it and " 
                 << upper[i + 1] + 1 << " greater" << endl;
            if (uorder[i + 1] >= lorder[i]) 
                ans[i] = min(lower[i] + 1, upper[i]);
            else ans[i] = min(lower[i] + 1, upper[i + 1] + 1);
        }
    }
    for (int i = 0; i <= N; i++) cout << ans[i] << endl;
    return 0;
}