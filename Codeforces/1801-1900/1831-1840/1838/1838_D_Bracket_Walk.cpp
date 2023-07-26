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
#define endl "\n"
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

const int MAXN = 200010;
int N, Q;

int arr[MAXN];
int narr[MAXN];

set<int> two, ntwo;

int main()
{
    // freopen(".in", "r", stdin);
    // freopen(".out", "w", stdout);
    srand(time(NULL));
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N >> Q;
    for (int i = 1; i <= N; i++) {
        char c;
        cin >> c;

        if (c == '(') arr[i] = 1;
        else arr[i] = -1;
    }

    for (int i = 1; i < N; i++) {
        narr[i] = arr[i] + arr[i + 1];
        if (narr[i] == 2) two.insert(i);
        if (narr[i] == -2) ntwo.insert(i);
    }

    int talk = (N % 2 == 0);

    while (Q--) {
        int c;
        cin >> c;
        // cout << "editing " << c << " " << arr[c] << endl;
        if (arr[c] > 0) {
            if (narr[c] == 2) {
                // cout << c << " is no longer 2" << endl;
                if (c < N) two.erase(c);
            }
            if (narr[c - 1] == 2) {
                // cout << c - 1 << " is no longer 2" << endl;
                if (c > 1) two.erase(c - 1);
            }

            narr[c] -= 2;
            narr[c - 1] -= 2;

            if (narr[c] == -2) {
                // cout << c << " became -2" << endl;
                if (c < N) ntwo.insert(c);
            }
            if (narr[c - 1] == -2) {
                // cout << c - 1 << " became -2" << endl;
                if (c > 1) ntwo.insert(c - 1);
            }
        }
        else {
            if (narr[c] == -2) {
                // cout << c << " is no longer -2" << endl;
                if (c < N) ntwo.erase(c);
            }
            if (narr[c - 1] == -2) {
                // cout << c - 1 << " is no longer -2" << endl;
                if (c > 1) ntwo.erase(c - 1);
            }

            narr[c] += 2;
            narr[c - 1] += 2;

            if (narr[c] == 2) {
                // cout << c << " became -2" << endl;
                if (c < N) two.insert(c);
            }
            if (narr[c - 1] == 2) {
                // cout << c - 1 << " became -2" << endl;
                if (c > 1) two.insert(c - 1);
            }
        }

        int c1 = 1;
        if ((two.empty() && !ntwo.empty()) || 
            ((!two.empty() && !ntwo.empty()) && *two.begin() > *ntwo.begin())) c1 = 0;
        int c2 = 1;
        if ((ntwo.empty() && !two.empty()) || 
            ((!two.empty() && !ntwo.empty()) && *two.rbegin() > *ntwo.rbegin())) c2 = 0;
        

        arr[c] = -arr[c];
        // cout << c1 << " " << c2 << " " << c3 << endl;
        
        if (talk && c1 && c2 && arr[1] == 1 && arr[N] == -1) cout << "YES" << endl;
        else cout << "NO" << endl;
        
    }

    return 0;
} 