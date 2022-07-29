#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>
using namespace std;

struct Suffix
{
    int id;
    int r;
    int oldr;
};

bool Comp(const Suffix& s1, const Suffix& s2)
{
    return make_pair(s1.oldr, s1.r) < make_pair(s2.oldr, s2.r);
}

int N;
Suffix s[10010];
int r[10010];
string str;

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);

    cin >> N;
    for (int i = 0; i < N; i++)
    {
        cin >> str;
        memset(s, 0, sizeof(s));
        memset(r, 0, sizeof(r));
        for (int j = 0; j < str.length(); j++)
        {
            s[j].id = j;
            s[j].oldr = 0;
            s[j].r = str[j] - 'a';
        }

        sort(s, s + str.length(), Comp);
        r[s[0].id] = 0;
        for (int k = 1; k < str.length(); k++)
        {
            if (Comp(s[k - 1], s[k])) r[s[k].id] = r[s[k - 1].id] + 1;
            else r[s[k].id] = r[s[k - 1].id];
        }

        for (int j = 1; j < str.length(); j *= 2)
        {
            //cout << "looking " << j << " char " << endl;
            for (int k = 0; k < str.length(); k++)
                s[k].oldr = r[s[k].id];

            for (int k = 0; k < str.length(); k++)
                s[k].r = r[(s[k].id + j) % str.length()];
            
            sort(s, s + str.length(), Comp);
            r[s[0].id] = 0;
            for (int k = 1; k < str.length(); k++)
            {
                if (Comp(s[k - 1], s[k])) r[s[k].id] = r[s[k - 1].id] + 1;
                else r[s[k].id] = r[s[k - 1].id];
            }
        }
        /*
        for (int j = 0; j < str.length(); j++)
        {
            cout << "rank " << r[s[j].id] << ": ";
            for (int k = 0; k < str.length(); k++)
                cout << str[(s[j].id + k) % str.length()];
            cout << endl;
        }
        */

        int minId = str.length();
        for (int j = 0; j < str.length(); j++)
            if (r[s[j].id] == 0) minId = min(minId, s[j].id);

        cout << minId + 1 << endl;
    }
    return 0;
}