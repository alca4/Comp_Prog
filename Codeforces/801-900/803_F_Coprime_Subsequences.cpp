#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
using namespace std;

#define MOD 1000000007
#define ll long long

int N;
int a[100010];
ll two[100010];
ll ans[100010];
int multiples[100010];
int composite[100010];
vector<int> primes;

void find_divisors(int n)
{
    if (n != 1) multiples[n]++;
    for (int i = 2; i <= sqrt(n); i++) if (n % i == 0) 
    {
        multiples[i]++;
        if (n / i != i) multiples[n / i]++;
    }   
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> N;

    for (int i = 1; i <= N; i++)
        cin >> a[i];

    two[0] = 1;
    for (int i = 1; i <= 100000; i++) two[i] = (two[i - 1] * 2) % MOD;

    for (int i = 2; i <= 100000; i++) if (!composite[i])
        for (int j = i * 2; j <= 100000; j += i) composite[j] = 1;

    for (int i = 2; i <= 100000; i++)
        if (!composite[i]) primes.push_back(i);

    for (int i = 1; i <= N; i++)
        find_divisors(a[i]);
    
    for (int i = 100000; i >= 1; i--)
    {
        ans[i] = two[multiples[i]] - 1;
        for (int j = 2; i * j <= 100000; j++)
            ans[i] = (ans[i] - ans[i * j] + MOD) % MOD;
    }

    int total = two[N] - 1;
    for (int i = 2; i <= 100000; i++) total = (total - ans[i] + MOD) % MOD;
    cout << total << endl;
    return 0;
}