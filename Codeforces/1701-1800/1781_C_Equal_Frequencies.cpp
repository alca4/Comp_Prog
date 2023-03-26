/*
  ___
 (o,o)
<  .  >
--"-"---
Rowlet is orz
  _      _      _
>(.)__ <(.)__ =(.)__
 (___/  (___/  (___/
I am dum duck

Praise to the Cow God
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
ll INF = INT_MAX;
ll LINF = LONG_MAX;
ll MOD = 1000000007;
// ll MOD = 998244353;

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
ll power(ll a, ll b)
{
    ll n = b;
    ll ans = 1;

    ll binexp[64];
    binexp[0] = a;
    for (int i = 1; i < 64; i++) binexp[i] = mult(binexp[i - 1], binexp[i - 1]);

    while (n > 0)
    {
        int id = (int) log2(n & -n);
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

int rand32()
{
    int a = rand();
    int b = rand();
    return (a << 16) | b;
}

ll rand64()
{
    ll a = rand32();
    ll b = rand32();
    return (a << 32) | b;
}

const int MAXN = 0;
int N;
ll fact[MAXN], factinv[MAXN];

ll choose(int a, int b)
{
    return mult(fact[a], mult(factinv[b], factinv[a - b]));
}

void get_fact(int x)
{
    fact[0] = 1;
    for (int i = 1; i <= x; i++) fact[i] = mult(i, fact[i - 1]);
    factinv[x] = divide(1, fact[x]);
    for (int i = x - 1; i >= 0; i--) factinv[i] = mult(factinv[i + 1], i + 1);
}

void solve()
{
    // cout << "==========" << endl;
    cin >> N;

    string str;
    cin >> str;

    map<char, int> freq;
    for (int i = 0; i < N; i++) freq[str[i]]++;

    pair<int, string> best = {INF, ""};
    for (int i = 1; i <= N; i++) if (N % i == 0 && i * 26 >= N)
    {
        // cout << "trying " << i << endl;
        int over = 0, under = 0;
        vector<pair<int, char>> hi, lo;
        for (auto n : freq) 
        {
            if (n.SS > i) 
            {
                over += n.SS - i;
                hi.pb({n.SS, n.FF});
            }
            if (n.SS < i) 
            {
                under += i - n.SS;
                lo.pb({n.SS, n.FF});
            }
        }

        sort(lo.rbegin(), lo.rend());

        while (lo.size() && (under > over || (over - under) % i))
        {
            hi.pb(lo.back());
            over += lo.back().FF;
            under -= i - lo.back().FF;
            lo.pop_back();
        }

        for (char c = 'a'; c <= 'z'; c++) if (!freq.count(c)) lo.pb({1, c});

        // cout << "hi" << endl;
        // for (auto n : hi) cout << n.SS << " ";
        // cout << endl;

        // cout << "lo" << endl;
        // for (auto n : lo) cout << n.SS << " ";
        // cout << endl;

        map<char, int> seen;

        map<char, int> extra;

        int ptr = 0;

        string tmp = str;
        for (int k = 0; k < N; k++) 
        {
            int is_high = 0;
            for (int j = 0; j < hi.size(); j++) if (hi[j].SS == tmp[k]) is_high = 1;

            bool b = 1;
            if (freq[tmp[k]] >= i) b = (seen[tmp[k]] == i);

            if (is_high && b)
            {
                while (ptr < lo.size() && 
                       extra[lo[ptr].SS] + freq[lo[ptr].SS] == i) ptr++;

                tmp[k] = lo[ptr].SS;
                seen[lo[ptr].SS]++;
                extra[lo[ptr].SS]++;
            }
            else seen[tmp[k]]++;
        }

        best = min(best, {over, tmp});
    }

    cout << best.FF << endl;
    cout << best.SS << endl;
}

int main()
{
    // freopen('.in', 'r', cin);
    // freopen('.out', 'w', cout);
    srand(time(NULL));
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int T;
    cin >> T;
    while (T--) solve();

    return 0;
} 