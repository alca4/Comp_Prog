struct BIT {
    ll arr[MAXN];

    void update(int a, ll v) {
        while (a <= N) {
            arr[a] += v;
            a += (a & -a);
        }
    }

    ll query(int a) {
        ll ans = 0;
        while (a) {
            ans += arr[a];
            a -= (a & -a);
        }
        return ans;
    }

    ll query(int a, int b) {return query(b) - query(a - 1);}
}