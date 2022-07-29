#include<iostream>
#include<vector>
#include<cmath>
#include<algorithm>
using namespace std;

#define ll long long
typedef pair<string, int> pii;

int N;
string words[100010];

ll MergeSort(int s, int e)
{
    //cout << s << " " << e << endl;
    if (s == e) return 0;
    int m = (s + e) / 2;
    ll ret = MergeSort(s, m) +
              MergeSort(m + 1, e);
    int i = s;
    int j = m + 1;
    vector<string> sorted;
    while (i <= m && j <= e)
    {
        if (words[j] < words[i]) 
        {
            ret += m - i + 1;
            sorted.push_back(words[j]);
            j++;
        }
        else
        {
            sorted.push_back(words[i]);
            i++;
        }
    }
    if (i > m) while (j <= e) sorted.push_back(words[j]), j++;
    if (j > e) while (i <= m) sorted.push_back(words[i]), i++;
    for (int h = 0; h < sorted.size(); h++)
        words[s + h] = sorted[h];
    return ret;
}

int main()
{
    cin >> N;
    for (int i = 0; i < N; i++) cin >> words[i];
    sort(words, words + N);
    for (int i = 0; i < N; i++) reverse(words[i].begin(), words[i].end());
    cout << MergeSort(0, N - 1) << endl;
    return 0;
}