#include <iostream>
#include <algorithm>
#include <vector>
#include <numeric>
using namespace std;

#define ll long long
#define INF 1000000000000000000
typedef pair<ll, ll> pll;

int N;
ll A, B, L;
vector<pll> segs;

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N >> A >> B;
    if (A / __gcd(A, B + 1) <= INF / B)
        L = (A / __gcd(A, B + 1)) * B;
    else
        L = INF + 1;

    for (int i = 1; i <= N; i++)
    {
        ll a, b;
        cin >> a >> b;
        if (b - a >= L)
        {
            cout << L << endl;
            return 0;
        }
        a %= L;
        b %= L;
        if (b < a)
        {
            segs.push_back({a, L - 1});
            segs.push_back({0, b});
        }
        else segs.push_back({a, b});
    }

    sort(segs.begin(), segs.end());
    ll end = -1;
    ll ans = 0;
    for (pll p : segs)
    {
        if (p.second <= end) continue;
        ans += min(p.second - p.first + 1, p.second - end);
        end = p.second;
    }
    cout << ans << endl;
    return 0;
}