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

Tooting Bec
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
// #define cout cerr
ll INF = 1000000000;
ll LINF = 1000000000000000000;
ll MOD = 0;

typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef complex<ld> cd;

ll add(const ll& a, const ll& b) {return (a + b) % MOD;}
ll sub(const ll& a, const ll& b) {return (a - b + MOD) % MOD;}
ll mult(const ll& a, const ll& b) {return (a * b) % MOD;}
ll power(ll a, ll b) {
    ll n = a;
    ll ans = 1;

    for (int i = 0; i < 32; i++) {
        if (b & 1) ans = (ans * n) % MOD;
        n = (n * n) % MOD;
        b >>= 1;
    }

    return ans;
}
ll divide(const ll& a, const ll& b) {return (a * power(b, MOD - 2)) % MOD;}
template<class X, class Y> void maxeq(X& x, Y y) {if (x < y) x = y;}
template<class X, class Y> void mineq(X& x, Y y) {if (x > y) x = y;}
template<class X, class Y> void addeq(X& x, Y y) {x = add(x, y);}
template<class X, class Y> void subeq(X& x, Y y) {x = sub(x, y);}
template<class X, class Y> void multeq(X& x, Y y) {x = mult(x, y);}
template<class X, class Y> void diveq(X& x, Y y) {x = divide(x, y);}

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
// mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

const int MAXN = 110;
int N;
ll fibo[MAXN];
int guys[MAXN];
int only[MAXN];
ll arr[MAXN];

void reset_tc() {
    for (int i = 1; i <= 50; i++) arr[i] = guys[i] = only[i] = 0;
}

void solve() {
    cin >> N;
    int just_one = 0;
    int ans = 1;
    ll sum = 0;
    for (int i = 1; i <= N; i++) {
        cin >> arr[i];
        sum += arr[i];
    }

    int js = 0;
    ll fibsum = 0;
    for (int i = 1; i <= 50; i++) {
        fibsum += fibo[i];
        if (fibsum == sum) {
            js = i;
            break;
        }
        if (fibsum > sum) {
            cout << "NO" << endl;
            reset_tc();
            return;
        }
    }

    for (int i = 1; i <= N; i++) {
        if (arr[i] == 1 && N == 1) just_one = 1;
        for (int j = js; j >= 1; j--) if (arr[i] >= fibo[j]) {
            // cout << arr[i] << " dropping " << fibo[j] << endl;
            arr[i] -= fibo[j];
            guys[j]++;
            if (!arr[i]) only[j]++;

            j--;
        }
        if (arr[i]) ans = 0;
    }

    int odd_taken = 0;
    for (int j = js; j >= 3; j--) {
        if (guys[j] > 1) {
            if (guys[j] == 2 && !odd_taken && (j % 2) == 0 && only[j]) odd_taken = 1;
            else if (j > 3) ans = 0;
        }

        if (guys[j] == 1 && (j % 2) == 1 && odd_taken) ans = 0;

        if (guys[j] == 0 && ((j % 2) == 0 || !odd_taken)) ans = 0;
    }

    if (!just_one && guys[1] + guys[2] + odd_taken != 2) ans = 0;

    if (ans) cout << "YES" << endl;
    else cout << "NO" << endl;

    reset_tc();
}

int main() {
    // freopen("tc.in", "r", stdin);
    // freopen("tc.out", "w", stdout);
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    fibo[1] = 1, fibo[2] = 1;
    for (int i = 3; i <= 50; i++) fibo[i] = fibo[i - 1] + fibo[i - 2];

    int T;
    // T = 1;
    cin >> T;
    // T = "change";
    while (T--) solve();

    return 0;
} 