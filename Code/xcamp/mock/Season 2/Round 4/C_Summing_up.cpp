/*
  ___
 (o,o)
<  .  >
--"-"---
Rowlet is orz
*/
#include <bits/stdc++.h>
using namespace std;

#define FF first
#define SS second
#define pb push_back
#define ll long long
#define ld long double
#define INF 1000000000ull
#define MOD 1000000007ull
#define reset(x) memset(x, 0, sizeof(x))
#define all(x) (x).begin(), (x).end()
#define range(x, y, z) (x) + (y), (x) + (y) + (z)

typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

int read()
{
    int a;
    cin >> a;
    return a;
}

const int MAXN = 1000010;
int N, M;
int S, P;
pii sk[MAXN];
pii pk[MAXN];

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N >> M;
    for (int i = 1; i <= N; i++) for (int j = 1; j <= M; j++)
    {
        char c;
        cin >> c;
        if (c == 'S') sk[++S] = {i + j, i - j};
        if (c == 'M') pk[++P] = {i + j, i - j};
    }

    ll p_ans = 0;
    sort(pk + 1, pk + 1 + P);
    for (int i = 1; i <= P; i++)
    {
        p_ans += pk[i].FF * (i - 1);
        p_ans -= pk[i].FF * (P - i);
    }
    for (int i = 1; i <= P; i++) swap(pk[i].FF, pk[i].SS);
    sort(pk + 1, pk + 1 + P);
    for (int i = 1; i <= P; i++)
    {
        p_ans += pk[i].FF * (i - 1);
        p_ans -= pk[i].FF * (P - i);
    }

    cout << p_ans / 2 << " ";

    ll s_ans = 0;
    sort(sk + 1, sk + 1 + S);
    for (int i = 1; i <= S; i++)
    {
        s_ans += sk[i].FF * (i - 1);
        s_ans -= sk[i].FF * (S - i);
    }
    for (int i = 1; i <= S; i++) swap(sk[i].FF, sk[i].SS);
    sort(sk + 1, sk + 1 + S);
    for (int i = 1; i <= S; i++)
    {
        s_ans += sk[i].FF * (i - 1);
        s_ans -= sk[i].FF * (S - i);
    }

    cout << s_ans / 2 << endl;
    return 0;
}