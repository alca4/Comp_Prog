#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

int N, M;
int city[401][401];
int memo[401][401][401][4];

bool DP(int x, int y, int speed, char dir)
{
    if (memo[x][y][speed][dir])
    bool thing = false;
    if (x < 1 || x > N || y < 1 || y > N) return 0;
    if (dir == 'N') y -= speed;
    if (dir == 'S') y += speed;
    if (dir == 'E') x += speed;
    if (dir == 'W') x -= speed;
    thing |= DP(x, y, speed + 1, dir);
    if (speed != 0) thing |= DP(x, y, speed - 1, dir);
    else
    {
    }
}

int main()
{
    cin >> N >> M;
    for (int i = 1; i <= N; i++)
        for (int j = 1; j <= M; j++) cin >> city[i][j];
    
    DP(1, 1, 0);
}