#include<iostream>
#include<fstream>
#include<cmath>
#include<vector>
#include<algorithm>
using namespace std;

struct Point
{
    int x, y;

    Point() {x = 0; y = 0;}
    Point(int a, int b) {x = a; y = b;}

    int Dist(const Point& p2) {return pow((p2.x - x), 2) + pow((p2.y - y), 2);}
    Point Update(char c)
    {
        if (c == 'N') return Point(x, y + 1);
        if (c == 'S') return Point(x, y - 1);
        if (c == 'E') return Point(x + 1, y);
        if (c == 'W') return Point(x - 1, y);
        return Point(0, 0);
    }
};

int N, M;
int memo[1001][1001];
vector<Point> b(1001);
vector<Point> j(1001);

int DP(int bi, int ji)
{
    if (bi > M || ji > N) return 1e9;
    if (bi == M && ji == N) return b[bi].Dist(j[ji]);
    if (memo[bi][ji] == -1)
    {
        memo[bi][ji] = min(min(DP(bi, ji + 1), DP(bi + 1, ji)), 
                           DP(bi + 1, ji + 1)) + 
                    b[bi].Dist(j[ji]);
    }
    return memo[bi][ji];
}

int main()
{
    ifstream fin ("radio.in");
    fin >> N >> M;
    int jx, jy;
    fin >> jx >> jy;
    j[0] = Point(jx, jy);
    int bx, by;
    fin >> bx >> by;
    b[0] = Point(bx, by);

   for (int i = 1; i <= N; i++)
   {
       char c;
       fin >> c;
       j[i] = j[i - 1].Update(c);
   }
   for (int i = 1; i <= M; i++)
   {
       char c;
       fin >> c;
       b[i] = b[i - 1].Update(c);
   }

   for (int i = 0; i <= M; i++)
       for (int k = 0; k <= N; k++) memo[i][k] = -1;

   ofstream fout ("radio.out");
   fout << DP(0, 0) - b[0].Dist(j[0]) << endl;
}
