#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

const int INFINITY = 0x3f3f3f3f;
const int N = 1e2 + 10;
int g[N][N];
bool visit[N];
int m, n, res;

void dfs(int u, int cnt, int len)
{
    if (cnt == len)
    {
        res++;
        return;
    }
    visit[u] = true;
    for (int i = 0; i < n; ++i)
    {
        int dist = g[u][i];
        if (!visit[i] && dist < INFINITY)
        {
            dfs(i, cnt + 1, len);
        }
    }
    visit[u] = false;
}

void IsPathLenth(int len)
{
    for (int i = 0; i < n; ++i)
        dfs(i, 0, len);
}

int main()
{
    cin >> n >> m;

    memset(g, 0x3f, sizeof(g));
    memset(visit, 0, sizeof(visit));
    
    int u, v, w;
    while (m--)
    {
        cin >> u >> v >> w;
        g[u][v] = w;
    }

    int len;
    cin >> len;

    IsPathLenth(len);
    cout << res << endl;

    system("pause");
    return 0;
}