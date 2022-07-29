/*
LEARNING:
Was straightforward until TLEd on 31 :|
For prime factorization, keep track
of which prime can divide any composite number
*/

#include <iostream>
#include <algorithm>
#include <cmath>
#include <map>
#include <vector>
using namespace std;

int N;
int a[300010];
int p[15000010];
int d[15000010];
int primes[15000010];

int gcd(int a, int b)
{
    if (a < b) swap(a, b);
    if (a % b == 0) return b;
    return gcd(b, a % b);
}

int main()
{
    scanf("%d", &N);
    for (int i = 1; i <= N; i++) scanf("%d", &a[i]);
    int divisor = a[1];
    for (int i = 2; i <= N; i++) divisor = gcd(divisor, a[i]);
    //cout << divisor << endl;

    int P = 0;
    p[1] = 1;
    for (int i = 2; i <= 15000000; i++)
    {
        if (p[i]) continue;
        primes[P] = i;
        p[i] = i;
        P++;
        
        for (int j = i; j <= 15000000; j += i)
            p[j] = primes[P - 1];
    }

    for (int i = 1; i <= N; i++)
    {
        //cout << a[i] << "==" << endl;
        int last = 1;
        int temp = a[i] / divisor;
        
        while (p[temp] != 1)
        {
            if (p[temp] != last) d[p[temp]]++, last = p[temp];
            temp /= p[temp];
        }
    }
    //cout << p.size() << endl;

    int max_num = 0;
    for (int i = 1; i <= 15000000; i++) max_num = max(max_num, d[i]);

    if (max_num == 0) printf("%d\n", -1);
    else printf("%d\n", N - max_num);
    return 0;
}