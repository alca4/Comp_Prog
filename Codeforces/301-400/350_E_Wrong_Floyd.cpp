#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

#define v vector
typedef pair<int, int> pii;

int N, M, K;
int adjmat[51][51];
v<int> marked;
v<int> unmarked;
int visited[51];
v<pii> edges;

int main()
{
    cin >> N >> M >> K;
    for (int i = 1; i <= K; i++) 
    {
        int k;
        cin >> k;
        marked.push_back(k);
    }
    int id = 0;
    for (int i = 1; i <= N; i++)
    {
        bool mark = false;
        for (int j = 0; j < K; j++)
            if (marked[j] == i) mark = true;
        if (!mark) 
            unmarked.push_back(i);
    }
    /*
    for (int i = 0; i < marked.size(); i++) cout << marked[i] << " ";
    cout << endl;
    for (int i = 0; i < unmarked.size(); i++) cout << unmarked[i] << " ";
    cout << endl;
    */

    if (M > N * (N - 1) / 2 - K + 1 || K == N)
    {
        cout << -1 << endl;
        return 0;
    }

    for (int i = 0; i < marked.size(); i++)
    {
        edges.push_back(pii(marked[i], unmarked[0]));
        M--;
    }
    for (int i = 1; i < unmarked.size(); i++)
    {
        edges.push_back(pii(marked[0], unmarked[i]));
        M--;
    }

    for (int i = 1; i < marked.size(); i++)
        for (int j = 1; j < unmarked.size(); j++)
        {
            if (M == 0) {break;}
            edges.push_back(pii(marked[i], unmarked[j]));
            M--;
        }

    for (int i = 0; i < unmarked.size(); i++)
        for (int j = i + 1; j < unmarked.size(); j++)
        {
            if (M == 0) {break;}
            edges.push_back(pii(unmarked[i], unmarked[j]));
            M--;
        }
    
    for (int i = 1; i < marked.size(); i++)
        for (int j = i + 1; j < marked.size(); j++)
        {
            if (M == 0) {break;}
            edges.push_back(pii(marked[i], marked[j]));
            M--;
        }

    for (int i = 0; i < edges.size(); i++)
        printf("%d %d\n", edges[i].first, edges[i].second);

    return 0;
}