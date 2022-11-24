#include<iostream>
#include<cmath>
#include<vector>
#include<set>
#include<map>
#include<algorithm>
using namespace std;

typedef long long ll;
#define v vector
#define f first
#define s second

typedef pair<int, int> pii;

ll N, Q, S;
v<v<ll>> blocks;
v<map<ll, int>> sorted_blocks;
v<ll> ud;

int BlockId(int id) {return id / sqrt(N);}

void Replace(int bi, int d, int j)
{
    sorted_blocks[bi][blocks[bi][j]]--;
    if (sorted_blocks[bi][blocks[bi][j]] == 0)
        sorted_blocks[bi].erase(blocks[bi][j]);
    blocks[bi][j] += d;
    sorted_blocks[bi][blocks[bi][j]]++;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    cout.tie(NULL);
    
    cin >> N >> Q;
    S = sqrt(N) + 1;
    blocks.resize(S);
    sorted_blocks.resize(S);
    ud.resize(S);
    int added = 0;
    for (int i = 0; i < S; i++)
    {
        blocks[i].resize(S);
        for (int j = 0; j < S; j++)
        {
            if (added == N) break;
            cin >> blocks[i][j];
            sorted_blocks[i][blocks[i][j]]++;
            added++;
        }
    }
    for (int i = 0; i < Q; i++)
    {
        int type;
        cin >> type;
        if (type == 1)
        {
            int fi, li, d;
            cin >> fi >> li >> d;
            fi--, li--;
            int fbi = fi / S;
            int lbi = li / S;
            fi %= S;
            li %= S;
            for (int j = fbi + 1; j < lbi; j++) ud[j] += d;
            if (fbi == lbi)
            {
                for (int j = fi; j <= li; j++) Replace(fbi, d, j);
            }
            else
            {
                if (fi == 0) ud[fbi] += d;
                else for (int j = fi; j < S; j++) Replace(fbi, d, j);
                if (li == S - 1) ud[lbi] += d;
                else for (int j = 0; j <= li; j++) Replace(lbi, d, j);
            }
        }
        if (type == 2)
        {
            ll y;
            cin >> y;
            int si = N + 1, ei = -1;
            for (int j = 0; j < S; j++)
            {
            	ll temp = y;
            	temp -= ud[j];
                if (sorted_blocks[j].find(temp) != sorted_blocks[j].end())
                {
                    for (int k = 0; k < S; k++) if (blocks[j][k] == temp)
                    {
                        si = j * S + k;
                        break;
                    }
                }
                if (si != N + 1) break;
            }
            
            for (int j = S - 1; j >= 0; j--)
            {
            	ll temp = y;
            	if (ud[j] != 0) temp -= ud[j];
                if (sorted_blocks[j].find(temp) != sorted_blocks[j].end())
                {
                    for (int k = S - 1; k >= 0; k--) if (blocks[j][k] == temp)
                    {
                        ei = j * S + k;
                        break;
                    }
                }
                if (ei != -1) break;
            }
            if (si == N + 1) cout << -1 << endl;
            else cout << ei - si << endl;
        }
    }
    return 0;
}