/*
{O,O}
/)_)
 " "
Rowlet the Owlet
*/

#include <iostream>
#include <algorithm>
#include <vector>
#include <bitset>
#include <map>
using namespace std;

#define ll long long

int N;
int q[100010][3];
int vals[200010];
map<ll, int> id;

struct ST
{
    int tot;
    int sz;
    vector<int> seg;
    vector<int> ud; 

    ST(int s)
    {
        sz = s + 1;
        seg.resize(sz * 4);
        ud.resize(sz * 4);
    }

    void Update(int a, int b, int t) {Update(a, b, t, 1, 1, sz);}
    void Update(int a, int b, int t, int cid, int ss, int se)
    {
        if (a <= ss && se <= b)
        {
            if (t == 1 || t == 2) ud[cid] = t;
            else ud[cid] = 3 - ud[cid];
        }

        if (ud[cid] == 1)
        {
            seg[cid] = (se - ss + 1);
            //cout << "propagated 1 down" << endl;
            if (ss != se)
            {
                ud[cid * 2] = 1;
                ud[cid * 2 + 1] = 1;
            }
        }
        if (ud[cid] == 2)
        {
            seg[cid] = 0;
            //cout << "propagated 2 down" << endl;
            if (ss != se)
            {
                ud[cid * 2] = 2;
                ud[cid * 2 + 1] = 2;
            }
        }
        if (ud[cid] == 3)
        {
            seg[cid] = (se - ss + 1) - seg[cid];
            //cout << "propagated 3 down" << endl;
            if (ss != se)
            {
                ud[cid * 2] = 3 - ud[cid * 2];
                ud[cid * 2 + 1] = 3 - ud[cid * 2 + 1];
            }
        }
        ud[cid] = 0;

        if (a <= ss && se <= b) return;
        if (ss == se) return;

        int mid = (ss + se) / 2;
        if (a <= mid) Update(a, b, t, cid * 2, ss, mid);
        if (b >= mid + 1) Update(a, b, t, cid * 2 + 1, mid + 1, se);
        seg[cid] = seg[cid * 2] + seg[cid * 2 + 1];
    }

    ll Query() 
    {
        ll ans = Query(1, 1, sz);
        if (ans == 0) return 1;
        return vals[ans];
    }
    ll Query(int cid, int ss, int se)
    {
        //cout << "Querying: " << ss << " " << se << endl;
        //if (ud[cid] != 0) cout << "resolving updates" << endl;
        if (ud[cid] == 1)
        {
            seg[cid] = (se - ss + 1);
            if (ss != se)
            {
                ud[cid * 2] = 1;
                ud[cid * 2 + 1] = 1;
            }
        }
        if (ud[cid] == 2)
        {
            seg[cid] = 0;
            if (ss != se)
            {
                ud[cid * 2] = 2;
                ud[cid * 2 + 1] = 2;
            }
        }
        if (ud[cid] == 3)
        {
            seg[cid] = (se - ss + 1) - seg[cid];
            if (ss != se)
            {
                ud[cid * 2] = 3 - ud[cid * 2];
                ud[cid * 2 + 1] = 3 - ud[cid * 2 + 1];
            }
        }
        ud[cid] = 0;

        if (seg[cid] == (se - ss + 1)) 
        {
            //cout << ss << " to " << se << " is occupied :|" << endl;
            return 1e18;
        }
        if (ss == se) 
        {
            //cout << ss << " is empty!" << endl;
            return ss;
        }
        
        int mid = (ss + se) / 2;
        ll ans = 1e18;
        ans = min(ans, Query(cid * 2, ss, mid));
        if (ans == 1e18) ans = min(ans, Query(cid * 2 + 1, mid + 1, se));
        seg[cid] = seg[cid * 2] + seg[cid * 2 + 1];
        return ans;
    }

    void Print() {Print(1, 1, sz);/* cout << endl*/;}
    void Print(int cid, int ss, int se)
    {
        for (int i = 1; i < seg.size() / 2; i++) cout << seg[i] << " ";
        cout << endl;
        for (int i = 1; i < ud.size() / 2; i++) cout << ud[i] << " ";
        cout << endl;
        /*
        if (ud[cid] == 1)
        {
            seg[cid] = (se - ss + 1);
            if (ss != se)
            {
                ud[cid * 2] = 1;
                ud[cid * 2 + 1] = 1;
            }
        }
        if (ud[cid] == 2)
        {
            seg[cid] = 0;
            if (ss != se)
            {
                ud[cid * 2] = 2;
                ud[cid * 2 + 1] = 2;
            }
        }
        if (ud[cid] == 3)
        {
            seg[cid] = (se - ss + 1) - seg[cid];
            if (ss != se)
            {
                ud[cid * 2] = 3 - ud[cid * 2];
                ud[cid * 2 + 1] = 3 - ud[cid * 2 + 1];
            }
        }

        int mid = (ss + se) / 2;
        //cout << seg[cid] << " ";
        if (ss != se) Print(cid * 2, ss, mid);
        if (ss != se) Print(cid * 2 + 1, mid + 1, se);
        */
    }
};

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);

    cin >> N;
    for (int i = 1; i <= N; i++)
    {
        cin >> q[i][0] >> q[i][1] >> q[i][2];
        q[i][2]++;
        id[q[i][1]] = 0;
        id[q[i][2]] = 0;
    }

    int count = 1;
    for (auto n : id)
    {
        id[n.first] = count;
        vals[count] = n.first;
        //cout << vals[count] << " ";
        count++;
    }        
    //cout << endl;

    ST seg(id.size()); // discounting 0
    for (int i = 1; i <= N; i++)
    {
        //cout << q[i][0] << " " << id[q[i][1]] << " " << id[q[i][2] + 1] - 1 << endl;
        seg.Update(id[q[i][1]], id[q[i][2]] - 1, q[i][0]);
        //seg.Print();
        cout << seg.Query() << endl;
    }
    return 0;
}