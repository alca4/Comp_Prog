#include<iostream>
#include<vector>
using namespace std;

int J, K, M, N;
vector<int> adjlist[400];

int main()
{
    cin >> J >> K >> M >> N;
    for (int i = 0; i <= N; i++)
    {
    	string adj;
    	getline(cin, adj);
    	if (i != 0)
    	{
    		int prev = 0;
    		for (int j = 0; j < adj.length(); j++)
    		{
    			cout << j << endl;
    			if (adj[j] == ' ') 
    			{
    				adjlist[i].push_back(stoi(adj.substr(prev, j - 1)));
    				prev = j + 1;
    			}
    		}
    		adjlist[i].push_back(stoi(adj.substr(prev)));
    	}
    }
    
    return 0;
}