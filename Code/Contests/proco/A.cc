#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

typedef pair<double, int> pii;

int N;
vector<pii> a;

int main()
{
    scanf("%d", &N);
    a.resize(N);
    for (int i = 0; i < N; i++) 
    {
        int id;
        scanf("%d", &id);
        double pt, time;
        scanf("%lf%lf", &pt, &time);
        double ans = pt / time;
        a[i] = pii(ans, id * -1);
    }
    
    sort(a.rbegin(), a.rend());

    for (int i = 0; i < N; i++) printf("%d\n", a[i].second * -1);
    return 0;
}