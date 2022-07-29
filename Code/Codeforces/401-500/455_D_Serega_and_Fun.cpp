#include <iostream>
#include <algorithm>
#include <vector>
#include <deque>
#include <map>
using namespace std;

int N, Q;
deque<int> blocks[400];
int cnt[400][100010];
int S = 350;

int main()
{
    scanf("%d", &N);
    int added = 0;
    for (int i = 0; i < S; i++)
    {
        for (int j = 0; j < S; j++)
        {
            if (added == N) break;
            int a;
            scanf("%d", &a);
            blocks[i].push_back(a);
            cnt[i][a]++;
            added++;
        }
    }

    scanf("%d", &Q);
    int lastans = 0;
    while (Q--)
    {
        int t, l, r;
        scanf("%d%d%d", &t, &l, &r);
        l = (l + lastans - 1) % N;
        r = (r + lastans - 1) % N;
        if (l > r) swap(l, r);
        int lb, rb, li, ri;
        lb = l / S;
        li = l % S;
        rb = r / S;
        ri = r % S;
        if (t == 1)
        {
            int rval = blocks[rb][ri];
            if (lb == rb)
            {
                blocks[lb].insert(blocks[lb].begin() + li, rval);
                blocks[lb].erase(blocks[lb].begin() + ri + 1);
            }
            else
            {
                int carry = blocks[lb].back();
                blocks[lb].insert(blocks[lb].begin() + li, rval);
                blocks[lb].pop_back();
                cnt[lb][rval]++;
                cnt[lb][carry]--;

                for (int i = lb + 1; i <= rb - 1; i++)
                {
                    blocks[i].push_front(carry);
                    cnt[i][carry]++;
                    carry = blocks[i].back();
                    blocks[i].pop_back();
                    cnt[i][carry]--;
                }

                blocks[rb].push_front(carry);
                blocks[rb].erase(blocks[rb].begin() + ri + 1);
                cnt[rb][carry]++;
                cnt[rb][rval]--;
            }
        }
        else
        {
            int k;
            scanf("%d", &k);
            k = (k + lastans - 1) % N + 1;
            int ans = 0;
            if (lb == rb)
            {
                for (int i = li; i <= ri; i++)
                    if (blocks[lb][i] == k) ans++;
            }
            else
            {
                for (int i = li; i < blocks[lb].size(); i++)
                    if (blocks[lb][i] == k) ans++;
                for (int i = lb + 1; i <= rb - 1; i++)
                    ans += cnt[i][k];
                for (int i = 0; i <= ri; i++)
                    if (blocks[rb][i] == k) ans++;
            }
            printf("%d\n", ans);
            lastans = ans;
        }
        /*
        for (int i = 0; i < S; i++)
            for (int j = 0; j < blocks[i].size(); j++)
                cout << blocks[i][j] << " ";
        cout << endl;
        */
    }
    return 0;
}