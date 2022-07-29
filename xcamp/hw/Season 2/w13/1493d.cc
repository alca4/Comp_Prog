/*
multise erase erases EVERYONE of that value, use find
*/
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <cmath>
using namespace std;

#define ll long long
#define MOD 1000000007

int N, Q, P = 0;
map<int, int> d[200010];
int c[200010];
int id[200010];
vector<multiset<int>> primes;

int main()
{
    c[1] = 1;
    for (int i = 2; i <= 200000; i++)
    {
        if (c[i] > 0) continue;
        id[i] = P;
        P++;
        for (int j = i; j <= 200000; j += i) c[j] = i;
    }
    primes.resize(P);

    ll gcd = 1;
    scanf("%d%d", &N, &Q);
    for (int i = 1; i <= N; i++)
    {
        int a;
        scanf("%d", &a);
        while (c[a] != 1)
        {
            int p = c[a];
            a /= p;
            int old = primes[id[p]].size() < N ? 0 : *primes[id[p]].begin();
            if (d[i].find(p) != d[i].end()) 
                primes[id[p]].erase(primes[id[p]].find(d[i][p]));
            d[i][p]++;
            primes[id[p]].insert(d[i][p]);
            int now = *primes[id[p]].begin();
            if (primes[id[p]].size() == N) 
            {
                //cout << now << " " << old << endl;
                gcd *= pow(p, now - old);
            }
        }
    }
    /*
    for (int i = 0; i < 2; i++)
    {
        for (auto n : primes[i])
            cout << n << " ";
        cout << endl;
    }
    */
    //cout << gcd << endl;
    for (int i = 0; i < Q; i++)
    {
        int a, x;
        scanf("%d%d", &a, &x);
        while (c[x] != 1)
        {
            int p = c[x];
            x /= p;
            int old = primes[id[p]].size() < N ? 0 : *primes[id[p]].begin();
            if (d[a].find(p) != d[a].end()) 
                primes[id[p]].erase(primes[id[p]].find(d[a][p]));
            d[a][p]++;
            primes[id[p]].insert(d[a][p]);
            int now = *primes[id[p]].begin();
            if (primes[id[p]].size() == N) 
            {
                //cout << now << " " << old << endl;
                gcd *= pow(p, now - old);
                gcd = (gcd % MOD);
            }
        }
        printf("%lld\n", gcd);
    }
    return 0;
}
