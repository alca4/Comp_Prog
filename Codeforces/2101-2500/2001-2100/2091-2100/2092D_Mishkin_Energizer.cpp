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

#define ll long long
#define ld long double
#define ull unsigned ll

#define endl "\n"
#define EPS 1e-9

#define size(v) (int) v.size()
#define pb push_back
#define pf push_front
#define ppb pop_back
#define ppf pop_front
// #define cout cerr

ll INF = 1000000000;
ll LINF = 1000000000000000000;
ll MOD = 0;

typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef complex<ld> cd;
typedef vector<int> vi;
typedef vector<vi> vii;
typedef vector<pii> vpii;

#define add(a, b) ((a + b) >= MOD ? a + b - MOD : a + b)
#define sub(a, b) ((a - b) >= 0 ? a - b : a + MOD - b)
#define mult(a, b) ((a * b) % MOD)
inline ll power(ll a, ll b) {
    ll n = a;
    ll ans = 1;

    for (int i = 0; i < 64; i++) {
        if (b & 1) ans = (ans * n) % MOD;
        n = (n * n) % MOD;
        b >>= 1;
    }

    return ans;
}
#define divide(a, b) ((a * power(b, MOD - 2)) % MOD)

#define maxeq(x, y) if (x < y) x = y
#define mineq(x, y) if (x > y) x = y
#define addeq(x, y) x = add(x, y)
#define subeq(x, y) x = sub(x, y)
#define multeq(x, y) x = mult(x, y)
#define diveq(x, y) x = divide(x, y)

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
// mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

const int MAXN = 0;
int N;

void reset_tc() {

}

void solve() {
    cin >> N;
    string str;
    cin >> str;

    pair<int, char> freq[3];
    freq[0].SS = 'T';
    freq[1].SS = 'I';
    freq[2].SS = 'L';
    for (int i = 0; i < N; i++) {
        if (str[i] == 'T') freq[0].FF++;
        if (str[i] == 'I') freq[1].FF++;
        if (str[i] == 'L') freq[2].FF++;
    }

    // LIILITT
    // 12345

    // cout << freq[0].FF << " " << freq[1].FF << " " << freq[2].FF << endl;
    sort(freq, freq + 3);
    // cout << freq[0].SS << " " << freq[1].SS << " " << freq[2].SS << endl;

    if (freq[0].FF == 0 && freq[1].FF == 0) {
        cout << -1 << endl;
        return;
    }

    vi ops;
    string tmp = "";
    tmp += str[0];
    int aah = 0;
    for (int i = 1; i < N; i++) {
        if (!aah && str[i] == freq[0].SS && str[i - 1] == freq[1].SS) {
            tmp += freq[2].SS;
            freq[2].FF++;
            ops.pb(i);
            aah = 1;
        }
        else if (!aah && str[i] == freq[1].SS && str[i - 1] == freq[0].SS) {
            tmp += freq[2].SS;
            freq[2].FF++;
            ops.pb(i);
            aah = 1;
        }
        tmp += str[i];
    }
    if (aah) N++;
    str = tmp;
    // cout << str << endl;

    // cout << freq[0].SS << " " << freq[1].SS << " " << freq[2].SS << endl;

    for (int i = 1; i < N; i++) {
        if (str[i] == freq[0].SS && str[i - 1] == freq[2].SS && freq[0].FF == freq[1].FF) 
            swap(freq[0], freq[1]);
        if (str[i] == freq[1].SS && str[i - 1] == freq[2].SS) {
            // cout << "found" << endl;
            while (freq[1].FF < freq[2].FF || freq[0].FF < freq[2].FF) {
                ops.pb(i);
                ops.pb(i);
                freq[1].FF++;
                freq[0].FF++;
            }
            while (freq[2].FF < freq[1].FF || freq[0].FF < freq[1].FF) {
                ops.pb(i + 1);
                ops.pb(i + 1);
                freq[2].FF++;
                freq[0].FF++;
            }
            assert(freq[0].FF == freq[1].FF && freq[1].FF == freq[2].FF);
            break;
        }
        if (str[i] == freq[2].SS && str[i - 1] == freq[0].SS && freq[0].FF == freq[1].FF) 
            swap(freq[0], freq[1]);
        if (str[i] == freq[2].SS && str[i - 1] == freq[1].SS) {
            // cout << "found" << endl;
            int guy = i;
            while (freq[1].FF < freq[2].FF || freq[0].FF < freq[2].FF) {
                ops.pb(guy);
                guy++;
                ops.pb(guy);
                guy++;
                freq[1].FF++;
                freq[0].FF++;
            }
            guy--;
            while (freq[2].FF < freq[1].FF || freq[0].FF < freq[1].FF) {
                ops.pb(guy);
                guy++;
                ops.pb(guy);
                guy++;
                freq[2].FF++;
                freq[0].FF++;
            }
            assert(freq[0].FF == freq[1].FF && freq[1].FF == freq[2].FF);
            break;
        }
    }

    cout << size(ops) << endl;
    for (int n : ops) cout << n << endl;

    reset_tc();
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