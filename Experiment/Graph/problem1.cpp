#include <iostream>
#include "Graph.h"
#include <cstdio>
using namespace std;

int main()
{
    freopen("text1.in", "r", stdin);
    freopen("result.out", "w", stdout);
    int n, m;
    cin >> n >> m;

    int vs[DEFAULT_SIZE];
    for (int i = 0; i < n; ++i)
        cin >> vs[i];
    Graph<int, int> g(vs, n);

    int v1, v2, w;
    for (int i = 0; i < m; ++i)
    {
        cin >> v1 >> v2 >> w;
        g.InsertArc(v1, v2, w);
    }

    // g.Display();

    int st, ed;
    cin >> st >> ed;
    if (g.IsPath(st, ed))
        cout << "存在 " << st << " 到 " << ed << " 的路径" << endl;
    else
        cout << "不存在 " << st << " 到 " << ed << " 的路径" << endl;

    int len;
    cin >> len;
    if (g.IsPathLenth(len))
        cout << "存在长度为 " << len << " 的路径" << endl;
    else
        cout << "不存在长度为 " << len << " 的路径" << endl;

    if (g.IsTree())
        cout << "图 G 是一棵树" << endl;
    else
        cout << "图 G 不是一棵树" << endl;

    g.TopSort();

    system("pause");
    return 0;
}