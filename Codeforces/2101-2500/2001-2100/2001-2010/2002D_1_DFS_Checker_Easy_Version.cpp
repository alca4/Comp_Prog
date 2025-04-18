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

const int MAXN = 0;
int N, Q;
int arr[1 << 16];
int level[1 << 16];

bool is_valid(int a) {
    return a >= 1 && a <= N;
}

bool compare(int parent, int child) {
    return arr[child] / 2 == arr[parent];
}

bool check(int i, int N0) {
    bool trust = 1;

    int other_back = i - (1 << (N0 - level[i] + 1));
    int par = (level[i] == level[i - 1] + 1 ? i - 1 : other_back);
    if (i > 1 && !compare(par, i)) trust = 0;

    // cout << i << " " << trust << endl;

    int other_front = i + (1 << (N0 - level[i]));
    if (level[i] != N0 &&
        !((!is_valid(i + 1) || compare(i, i + 1)) &&
         ((!is_valid(other_front) || compare(i, other_front)))))
        trust = 0;

    // cout << i << " " << trust << endl;
    
    return trust;
}

void solve() {
    cin >> N >> Q;
    for (int i = 1; i < N; i++) {
        int n;
        cin >> n;
    }
    for (int i = 1; i <= N; i++) cin >> arr[i];

    int N0 = 32 - __builtin_clz(N);

    // cout << N << " " << N0 << endl;

    vector<int> paint;
    paint.pb(1);
    level[1] = 1;
    vector<int> tpaint;
    for (int i = 1; i < N0; i++) {
        for (int n : paint) {
            level[n + 1] = i + 1;
            tpaint.pb(n + 1);
            level[n + (1 << (N0 - i))] = i + 1;
            tpaint.pb(n + (1 << (N0 - i)));
        }

        paint = tpaint;
        tpaint.clear();
    }
    

    int good = 0;
    for (int i = 1; i <= N; i++) if (check(i, N0)) good++;

    while (Q--) {
        int x, y;
        cin >> x >> y;

        set<int> vals_to_check;
        vals_to_check.insert(x);
        int par = (level[x] == level[x - 1] + 1 ? x - 1 : x - (1 << (N0 - level[x] + 1)));
        vals_to_check.insert(par);

        vals_to_check.insert(x + 1);
        vals_to_check.insert(x + (1 << (N0 - level[x])));

        vals_to_check.insert(y);
        par = (level[y] == level[y - 1] + 1 ? y - 1 : y - (1 << (N0 - level[y] + 1)));
        vals_to_check.insert(par);

        vals_to_check.insert(y + 1);
        vals_to_check.insert(y + (1 << (N0 - level[y])));

        for (int i : vals_to_check) if (is_valid(i) && check(i, N0)) good--;

        swap(arr[x], arr[y]);

        for (int i : vals_to_check) if (is_valid(i) && check(i, N0)) good++;


        // cout << good << endl;

        if (good == N) cout << "YES" << endl;
        else cout << "NO" << endl;
    }

    for (int i = 1; i <= N; i++) arr[i] = level[i] = 0;
}

int main() {
    // freopen("tc.in", "r", stdin);
    // freopen("tc.out", "w", stdout);
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int T;
    // T = 1;
    cin >> T;
    // T = "change";
    while (T--) solve();

    return 0;
} 