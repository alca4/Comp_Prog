#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
using namespace std;

#define ll long long

int N, P;
int S = -1;
int c[510];
ll pow2[510];
ll pow3[510];
ll fast[256][100];
vector<int> primes;

int value(int mask, int x)
{
    int val = 0;
    for (int i = 1; i <= N; i++)
    {
        if (i % x == 0)
        {
            int temp = i / x;
            for (int j = 0; j < S; j++)
                while (temp % primes[j] == 0 && ((mask | (1 << j)) == mask))
                    temp /= primes[j];
            if (temp == 1) val++;
        }
    }
    //cout << mask << " and " << x << " have val1: " << val << endl;
    return val;
}
int value2(int m1, int m2)
{
    int val = 0;
    for (int i = 2; i <= N; i++)
    {
        int temp = i;
        for (int j = 0; j < S; j++)
            while (temp % primes[j] == 0 &&
                   ((m1 | (1 << j)) == m1) &&
                   ((m2 | (1 << j)) != m2)) 
                temp /= primes[j];
        if (temp == 1) val++;
    }
    //cout << m1 << " and " << m2 << " have val2: " << val << endl;
    return val;
}
ll con(int a, int b)
{
    ll first = 1;
    for (int i = S; i < primes.size(); i++)
    {
        ll v1 = pow2[fast[a][i]];
        ll v2 = pow2[fast[b][i]];
        first = (first * (v1 + v2 - 1)) % P;
    }
    ll second = 1;
    second = (second * pow2[value2(a, b)]) % P;
    second = (second * pow2[value2(b, a)]) % P;
    //cout << a << " " << b << " contribute " << first << " and " << second << endl;
    //cout << first * second << endl;
    return (first * second) % P;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N >> P;
    pow2[0] = 1;
    for (int i = 1; i <= 500; i++) pow2[i] = (2 * pow2[i - 1]) % P;
    pow3[0] = 1;
    for (int i = 1; i <= 500; i++) pow3[i] = (3 * pow3[i - 1]) % P;
    for (int i = 2; i <= N; i++)
    {
        if (c[i]) continue;
        if (S == -1 && i > sqrt(N)) S = primes.size();
        primes.push_back(i);
        for (int j = 2 * i; j <= N; j += i) c[j] = 1;
    }
    for (int i = 0; i < (1 << S); i++)
        for (int j = S; j < primes.size(); j++)
            fast[i][j] = value(i, primes[j]);

    ll ans = 0;
    for (int i = 0; i < pow(3, S); i++)
    {
        int m1 = 0;
        int m2 = 0;
        int par = 0;
        for (int j = 0; j < S; j++)
        {
            if ((i / pow3[j]) % 3 == 1)
            {
                m1 |= (1 << j);
                par++;
            }
            if ((i / pow3[j]) % 3 == 2)
            {
                m2 |= (1 << j);
                par++;
            }
        }
        if ((S % 2 + 1 - par % 2) % 2) ans += con(m1, m2);
        else ans += P - con(m1, m2);
    }
    cout << ans % P << endl;
    return 0;
}