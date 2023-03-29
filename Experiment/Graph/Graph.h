#ifndef __GRAH_H__
#define __GRAH_H__

#include "Arc.h"
#include "Vertex.h"
#include "Assistance.h"
#include <iostream>
#include <cstring>
#include <vector>
#include <queue>
using namespace std;

template <class VexType, class WeightType>
class Graph
{
private:
    int vexNum, arcNum, vexMaxNum;         // 顶点数量，弧的数量，最大顶点数量
    Vertex<VexType, WeightType> *vexTable; // 顶点表

    void Clear();
    bool IsPathDFS(int v1, int v2, vector<bool> &visited);
    bool IsPathBFS(int v1, int v2, vector<bool> &visited);
    void GetMaxPathLenth(int start, int count, int &len, vector<bool> &visited);
    void IsTreeDFS(int v, int &count, vector<bool> &visited);
    bool TopSortDFS(int v, vector<int> &topsort, vector<int> &flag);
    bool TopSort(vector<int> &topsort);

public:
    Graph(VexType vs[], int vertexNum, int vertexMaxNum = DEFAULT_SIZE);
    ~Graph();

    void InsertArc(int v1, int v2, WeightType w);
    void Display();
    bool IsPath(int v1, int v2);
    bool IsPathLenth(int len);
    bool IsTree();
    int GetMaxPathLenth();
    void TopSort();
};

template <class VexType, class WeightType>
Graph<VexType, WeightType>::Graph(VexType vs[], int vertexNum, int vertexMaxNum)
{
    vexNum = vertexNum;
    vexMaxNum = vertexMaxNum;
    arcNum = 0;

    vexTable = new Vertex<VexType, WeightType>[vexMaxNum];

    for (int i = 0; i < vexNum; i++)
    {
        vexTable[i].data = vs[i];
        vexTable[i].firstarc = NULL;
    }
}

template <class VexType, class WeightType>
Graph<VexType, WeightType>::~Graph()
{
    Clear();
    delete[] vexTable;
}

template <class VexType, class WeightType>
void Graph<VexType, WeightType>::InsertArc(int v1, int v2, WeightType w)
{
    Arc<WeightType> *p, *q;
    p = vexTable[v1].firstarc;
    vexTable[v1].firstarc = new Arc<WeightType>(v2, w, p);
    arcNum++;
}

template <class VexType, class WeightType>
void Graph<VexType, WeightType>::Clear()
{
    Arc<WeightType> *p;
    for (int i = 0; i < vexNum; i++)
    { // 释放边结点
        p = vexTable[i].firstarc;
        while (p != NULL)
        {
            vexTable[i].firstarc = p->nextarc;
            delete p;
            p = vexTable[i].firstarc;
        }
    }
    vexNum = 0;
    arcNum = 0;
}

template <class VexType, class WeightType>
void Graph<VexType, WeightType>::Display()
// 打印邻接表
{
    Arc<WeightType> *p;
    for (int i = 0; i < vexNum; i++)
    {
        cout << vexTable[i].data << " : ";
        p = vexTable[i].firstarc;
        while (p != NULL)
        {
            cout << "(" << vexTable[p->archead].data << ", " << p->weight << ") ";
            p = p->nextarc;
        }
        cout << endl;
    }
}

template <class VexType, class WeightType>
// 传的是顶点的序号
bool Graph<VexType, WeightType>::IsPath(int v1, int v2)
{
    vector<bool> visited(vexNum, false);

    // bool result = IsPathDFS(v1, v2, visited);
    bool result = IsPathBFS(v1, v2, visited);

    return result;
}

template <class VexType, class WeightType>
bool Graph<VexType, WeightType>::IsPathDFS(int v1, int v2, vector<bool> &visited)
{
    if (v1 == v2)
        return true;
    visited[v1] = true;
    Arc<WeightType> *p = vexTable[v1].firstarc;
    while (p != NULL)
    {
        int u = p->archead;
        if (!visited[u] && IsPathDFS(u, v2, visited))
            return true;
        p = p->nextarc;
    }
    visited[v1] = false;
    return false;
}

template <class VexType, class WeightType>
bool Graph<VexType, WeightType>::IsPathBFS(int v1, int v2, vector<bool> &visited)
{
    queue<Vertex<VexType, WeightType>> que;
    que.push(vexTable[v1]);
    visited[v1] = true;

    while (!que.empty())
    {
        Vertex<VexType, WeightType> vex = que.front();
        que.pop();

        if (vex.data == vexTable[v2].data)
            return true;

        Arc<WeightType> *p = vex.firstarc;
        while (p != NULL)
        {
            int u = p->archead;
            if (!visited[u])
            {
                que.push(vexTable[u]);
                visited[u] = true;
            }
            p = p->nextarc;
        }
    }

    return false;
}

template <class VexType, class WeightType>
bool Graph<VexType, WeightType>::IsPathLenth(int len)
{
    int maxLen = 0;
    vector<bool> visited(vexNum, false);
    for (int start = 0; start < vexNum; ++start)
    {
        GetMaxPathLenth(start, 0, maxLen, visited);
        if (maxLen >= len)
            return true;
    }
    return false;
}

template <class VexType, class WeightType>
void Graph<VexType, WeightType>::GetMaxPathLenth(int start, int cnt, int &len, vector<bool> &visited)
{
    len = max(len, cnt);
    visited[start] = true;

    Arc<WeightType> *p = vexTable[start].firstarc;
    while (p != NULL)
    {
        if (!visited[p->archead])
        {
            GetMaxPathLenth(p->archead, cnt + 1, len, visited);
        }
        p = p->nextarc;
    }

    visited[start] = false;
}

template <class VexType, class WeightType>
int Graph<VexType, WeightType>::GetMaxPathLenth()
{
    int maxLen = 0;
    vector<bool> visited(vexNum, false);
    for (int start = 0; start < vexNum; ++start)
        GetMaxPathLenth(start, 0, maxLen, visited);
    return maxLen;
}

template <class VexType, class WeightType>
bool Graph<VexType, WeightType>::IsTree()
{
    if (vexNum != arcNum + 1)
        return false;
    int count = 0;
    vector<bool> visited(vexNum, false);
    IsTreeDFS(0, count, visited);
    return count == vexNum;
}

template <class VexType, class WeightType>
void Graph<VexType, WeightType>::IsTreeDFS(int v, int &count, vector<bool> &visited)
{
    count++;
    visited[v] = true;
    Arc<WeightType> *p = vexTable[v].firstarc;
    while (p != NULL)
    {
        int u = p->archead;
        if (!visited[u])
            IsTreeDFS(u, count, visited);
        p = p->nextarc;
    }
    visited[v] = false;
}

template <class VexType, class WeightType>
void Graph<VexType, WeightType>::TopSort()
{
    vector<int> topsort;
    if (TopSort(topsort))
    {
        cout << "拓扑序列为: ";
        for (int i = topsort.size() - 1; i >= 0; --i)
        {
            cout << topsort[i];
            if (i != 0)
                cout << ", ";
        }
        cout << endl;
    }
    else
        cout << "不存在拓扑序列" << endl;
}

template <class VexType, class WeightType>
bool Graph<VexType, WeightType>::TopSort(vector<int> &topsort)
{
    vector<int> flag(vexNum, 0);
    for (int i = 0; i < vexNum; ++i)
    {
        if (flag[i] == 0 && !TopSortDFS(i, topsort, flag))
            return false;
    }
    return true;
}

template <class VexType, class WeightType>
// flag = 0: 未被访问过
// flag = -1: 表示在本次路径中已经访问过了
// flag = 1: 表示已经加到了拓扑序列
bool Graph<VexType, WeightType>::TopSortDFS(int v, vector<int> &topsort, vector<int> &flag)
{
    flag[v] = -1;
    Arc<WeightType> *p = vexTable[v].firstarc;
    while (p != NULL)
    {
        if (flag[p->archead] == -1)
            return false;
        else if (flag[p->archead] == 0 && !TopSortDFS(p->archead, topsort, flag))
            return false;
        p = p->nextarc;
    }
    flag[v] = 1;
    topsort.push_back(v);
    return true;
}

#endif