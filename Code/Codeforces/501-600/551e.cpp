#include<iostream>
#include<cmath>
#include<vector>
#include<set>
#include<map>
#include<algorithm>
using namespace std;

typedef pair<long long, int> pii;
#define v vector
#define ff first
#define ss second

int N, Q, S;
pii blocks[1010][1010];
vector<int> sz;
long long ud[1010];

bool CompV(const pii& p1, const pii& p2)
{
    return p1.ff < p2.ff;
}
bool CompId(const pii& p1, const pii& p2)
{
    return p1.ss < p2.ss;
}

bool Exists(int b, int val)
{
    //cout << "searching for " << val << endl;
    int lo = 0;
    int hi = sz[b] - 1;
    while (lo <= hi)
    {
        int mid = (lo + hi) / 2;
        //cout << "current value is " << blocks[b][mid].ff + ud[b] << endl;
        if (val == blocks[b][mid].ff) return 1;
        if (val > blocks[b][mid].ff) lo = mid + 1;
        if (val < blocks[b][mid].ff) hi = mid - 1;
    }
    return 0;
}

int main()
{
    cin >> N >> Q;
    // input the array and get the blocks ready
    S = 1000;
    int added = 0;
    for (int i = 0; i < S; i++)
    {
        int j = 0;
        for (; j < S; j++)
        {
            if (added == N) break;
            long long a;
            cin >> a;
            blocks[i][j] = pii(a, j);
            added++;
        }
        sz.push_back(j);
        sort(blocks[i], blocks[i] + j);
        if (added == N) break;
    }

    // sort each block in ascending order
    for (int k = 0; k < Q; k++)
    {
        int type;
        cin >> type;
        if (type == 1)
        {
            int s, e, d;
            cin >> s >> e >> d;
            s--, e--;
            int sb, si, eb, ei;
            sb = s / S; si = s % S;
            eb = e / S; ei = e % S;

            // lazy update every block in between
            for (int b = sb + 1; b <= eb - 1; b++) ud[b] += d;
            if (sb == eb)
            {
                // within one block
                for (int i = 0; i < sz[sb]; i++)
                {
                    pii& val = blocks[sb][i];
                    if (si <= val.ss && val.ss <= ei) val.ff += d;
                }
            }
            else
            {
                // update first and last blocks
                for (int i = 0; i < sz[sb]; i++)
                {
                    pii& val = blocks[sb][i];
                    if (si <= val.ss) val.ff += d;
                }
                
                for (int i = 0; i < sz[eb]; i++)
                {
                    pii& val = blocks[eb][i];
                    if (val.ss <= ei) val.ff += d;
                }
            }
            sort(blocks[sb], blocks[sb] + sz[sb], CompV);
            sort(blocks[eb], blocks[eb] + sz[eb], CompV);

            // debug
            /*
            cout << endl;
            for (int i = 0; i < sz.size(); i++)
                for (int j = 0; j < sz[i]; j++)
                    cout << blocks[i][j].ff + ud[i] << " ";
            cout << endl;
            */
            /*
            for (int i = 0; i < S; i++)
                for (pii n : blocks[i])
                    cout << n.ss << " ";
            cout << endl;
            */
        }
        else
        {
            int val;
            cin >> val;
            bool exist = 0;
            int s;
            int e;
            for (int i = 0; i < sz.size(); i++)
            {
                if (!Exists(i, val - ud[i])) continue;
                exist = 1;
                int ans = N;
                for (int j = 0; j < sz[i]; j++)
                    if (blocks[i][j].ff == val - ud[i]) ans = min(ans, blocks[i][j].ss);
                s = i * S + ans;
                break;
            }
            for (int i = sz.size() - 1; i >= 0; i--)
            {
                if (!Exists(i, val - ud[i])) continue;
                int ans = -1;
                for (int j = 0; j < sz[i]; j++)
                    if (blocks[i][j].ff == val - ud[i]) ans = max(ans, blocks[i][j].ss);
                e = i * S + ans;
                break;
            }
            //cout << e << " " << s << endl;
            if (!exist) cout << -1 << endl;
            else cout << e - s << endl;
        }
    }
    /*
    for (int i = 0; i < sz.size(); i++)
        for (int j = 0; j < sz[i]; j++)
            cout << blocks[i][j].ff + ud[i] << " ";
    cout << endl;
    */
    return 0;
}
