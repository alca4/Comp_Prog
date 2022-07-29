#include<iostream>
#include<fstream>
#include<set>
#include<climits>
#include<math.h>
#include<algorithm>
using namespace std;

int N;
long M;
long flavor[100000];
long spicy[100000];

int main()
{
    ifstream fin ("hayfeast.in");
    fin >> N >> M;
    for (int i = 0; i < N; i++)
    {
        fin >> flavor[i] >> spicy[i];
    }
    int i = 0;
    int j = -1;
    long total_flavor = 0;
    multiset<long, greater<long>> max_spicy;
    long min_spicy = 1e18;
    while (i < N && j < N)
    {
        //cout << "i and j are " << i << ", " << j << endl;
        //cout << "total flavor is " << total_flavor << endl;
        multiset<long>::iterator it = max_spicy.begin();
        /*
        while (it != max_spicy.end())
        {
            cout << *it << " ";
            it++;
        }
        cout << endl;
        */
        if (total_flavor >= M)
        {
            min_spicy = min(min_spicy, *max_spicy.begin());
            total_flavor -= flavor[i];
            max_spicy.erase(max_spicy.find(spicy[i]));
            i++;
            if (i <= j) continue;
        }
        if (total_flavor < M || i > j)
        {
            if (j == N - 1) break;
            j++;
            total_flavor += flavor[j];
            max_spicy.insert(spicy[j]);
        }
    }
    ofstream fout ("hayfeast.out");
    fout << min_spicy << endl;
    return 0;
}