#include<iostream>
#include<fstream>
#include<vector>
#include<deque>
#include<stack>
#include<set>
using namespace std;

typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<vi> vii;

int N;
int dirty[100000];
int soap_index[100000];
deque<stack<int>> soapy;
stack<int> clean;

int main()
{
    ifstream fin ("dishes.in");
    fin >> N;
    for (int i = 0; i < N; i++) fin >> dirty[i];
    int smallest = 1;
    multiset<int> bs;
    ofstream fout ("dishes.out");
    for (int i = 0; i < N; i++)
    {
        for (auto n : bs) cout << n << endl;
        while (soapy.size() > 0 &&
               !soapy[0].empty() && 
               soapy[0].top() == smallest)
        {
            smallest++;
            clean.push(soapy[0].top());
            soapy[0].pop();
        }
        if (bs.upper_bound(dirty[i]) == bs.end())
        {
            cout << "new stack" << endl;
            bs.insert(dirty[i]);
            soap_index[i] = soapy.size();
            stack<int> temp;
            temp.push(dirty[i]);
            soapy.push_back(temp);
            cout << dirty[i] << " gets new stack" << endl;
        }
        else
        {
            cout << "no new stack " << endl;
            cout << *bs.upper_bound(dirty[i]) << endl;
            int upper_id = soap_index[*bs.upper_bound(dirty[i])]; 
            if (dirty[i] > soapy[upper_id].top())
            {
                if (upper_id == 0 && (clean.empty() || 
                                      clean.top() < soapy[upper_id].top()))
                {
                    cout << "replacement " << endl;
                    smallest = soapy[upper_id].top() + 1;
                    clean.push(soapy[upper_id].top());
                    soapy[upper_id].pop();
                    soapy[upper_id].push(dirty[i]);
                    cout << clean.top() << " replaced by " << soapy[upper_id].top() << endl;
                }
                else
                {
                    cout << "cannot fit " << dirty[i] << endl;
                    fout << i << endl;
                    return 0;
                }
            }
            else
            {
                cout << dirty[i] << " joined " << soapy[upper_id].top() << endl;
                soapy[upper_id].push(dirty[i]);
            }
        }
    }
    fout << N << endl;
    return 0;
}