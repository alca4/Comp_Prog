/*
  ___
 (o,o)
<  .  >
--"-"---
Rowlet is orz
  _      _      _
>(.)__ >(.)__ >(.)__
 (___/  (___/  (___/
I am dum duck
*/
#include <bits/stdc++.h>
using namespace std;

#define FF first
#define SS second
#define pb push_back
#define ll long long
#define ld long double
#define ull unsigned ll
// #define endl "\n"
#define EPS 1e-9
ll INF = 1000000000;
ll LINF = 1000000000000000000;
ll MOD = 0;

typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

ll add(const ll& a, const ll& b) 
{
    ll x = a + b;
    if (a + b >= MOD) x -= MOD;
    return x;
}
ll sub(const ll& a, const ll& b) 
{
    ll x = a - b;
    if (a - b < 0) x += MOD;
    return x;
}
ll mult(const ll& a, const ll& b) {return (a * b) % MOD;}
ll binexp[32];
ll power(ll a, ll b)
{
    ll n = b;
    ll ans = 1;

    binexp[0] = a;
    for (int i = 1; i < 32; i++) binexp[i] = mult(binexp[i - 1], binexp[i - 1]);

    while (n > 0)
    {
        int id = __builtin_ctz(n & -n);
        ans = mult(ans, binexp[id]);
        n -= (n & -n);
    }

    return ans;
}
ll divide(const ll& a, const ll& b) {return (a * power(b, MOD - 2)) % MOD;}
template<class X, class Y> void maxeq(X &x, Y y) {if (x < y) x = y;}
template<class X, class Y> void mineq(X &x, Y y) {if (x > y) x = y;}
template<class X, class Y> void addeq(X &x, Y y) {x = add(x, y);}
template<class X, class Y> void subeq(X &x, Y y) {x = sub(x, y);}
template<class X, class Y> void multeq(X &x, Y y) {x = mult(x, y);}
template<class X, class Y> void diveq(X &x, Y y) {x = divide(x, y);}

const int MAXN = 310;
int N;
int arr[MAXN];
int dp[MAXN][MAXN * MAXN];
int before[MAXN][MAXN * MAXN];

int main()
{
    // freopen(".in", "r", stdin);
    // freopen(".out", "w", stdout);
    srand(time(NULL));
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N;
    int sum = 0;
    for (int i = 1; i <= N; i++) {
        cin >> arr[i];
        sum += arr[i];
    }

    dp[0][0] = 1;
    for (int i = 1; i <= N; i++) for (int j = 90000; j >= 0; j--) {
        if (dp[i - 1][j]) {
            if (j + arr[i] <= 90000) {
                dp[i][j + arr[i]] = 1;
                before[i][j + arr[i]] = j;
            }
            dp[i][j] = 1;
            before[i][j] = j;
        }
    }
    
    int best = 0;
    for (int j = 90000; j >= 0; j--) 
        if (dp[N][j] && abs((sum + 1) / 2 - best) > abs((sum + 1) / 2 - j)) best = j;
    
    set<int> s1;
    for (int i = N; i >= 1; i--) if (before[i][best] != best) {
        s1.insert(i);
        best = before[i][best];
    }
    set<int> s2;
    set<int> m;
    for (int i = 1; i <= N; i++) {
        if (!s1.count(i)) s2.insert(i);
        m.insert(i);
    }
    
    if (sum % 2 == 0 && dp[N][sum / 2]) {
        cout << "Second" << endl;
        int j = 4;
        while (1) {
            cin >> j;
            if (j == 0) return 0;
            if (s2.count(j)) s1.swap(s2);
            int i = *s2.begin();
            cout << i << endl;
            int d = min(arr[i], arr[j]);
            arr[i] -= d;
            arr[j] -= d;
            if (arr[i] == 0) s2.erase(i);
            if (arr[j] == 0) s1.erase(j);
        }
    }
    else {
        cout << "First" << endl;
        int j = 4;
        while (1) {
            int i = *m.begin();
            cout << i << endl;
            cin >> j;
            if (j == 0) return 0;
            int d = min(arr[i], arr[j]);
            arr[i] -= d;
            arr[j] -= d;
            if (arr[i] == 0) m.erase(i);
            if (arr[j] == 0) m.erase(j);
        }
    }

    return 0;
} 