#include<iostream>
#include<algorithm>
#include<vector>
#include<map>
using namespace std;

typedef pair<int, int> pii;
#define v vector

int N, P;
pii sus[300010];
map<int, map<int, int>> doubles;
int sus_id[300010];

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> N >> P;
    for (int i = 0; i < N; i++)
    {
        int a, b;
        cin >> a >> b;
        sus[a].first++;
        sus[b].first++;
        doubles[a][b]++;
        doubles[b][a]++;
    }
    for (int i = 1; i <= N; i++) sus[i].second = i;

    sort(sus + 1, sus + N + 1);
    for (int i = 1; i <= N; i++) sus_id[sus[i].second] = i;
    /*
    for (int i = 1; i <= N; i++) cout << sus[i].first << "," << sus[i].second << "  ";
    cout << endl;
    */

    //cout << endl;
    long long ans = 0;
    int sum = sus[N].first;
    int r = N;
    for (int l = 1; l <= N; l++)
    {
        sum += sus[l].first;
        while (sum >= P && r > 0)
        {
            sum -= sus[r].first;
            r--;
            sum += sus[r].first;
        }
        int over = 0;
        for (auto val : doubles[sus[l].second])
        {
            if (sus[l].first + sus[sus_id[val.first]].first >= P && 
                sus[l].first + sus[sus_id[val.first]].first < P + val.second)
            {
                //cout << sus[l].second << " and " << sus[sus_id[val.first]].second << endl;
                over++;
            }
        }
        if (r < l) over++;
        //cout << l << " " << r << endl;
        ans += N - r - over;
        //cout << "adding: " << N - r - over << endl;
        sum -= sus[l].first;
    }

    cout << ans / 2 << endl;
    return 0;
}