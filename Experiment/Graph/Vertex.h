#ifndef __VERTEX_H__
#define __VERTEX_H__

#include "Arc.h"

template <class VexType, class WeightType>
struct Vertex
{
    VexType data;              // 顶点的数据
    Arc<WeightType> *firstarc; // 与顶点关联的第一条弧的指针

    Vertex();                                         // 无参数的构造函数
    Vertex(VexType val, Arc<WeightType> *adj = NULL); // 有参数的构造函数
};

// 邻接表网顶点结点类的实现部分
template <class VexType, class WeightType>
Vertex<VexType, WeightType>::Vertex()
// 操作结果：构造一个空顶点结点——无参构造函数
{
    firstarc = NULL;
}

template <class VexType, class WeightType>
Vertex<VexType, WeightType>::Vertex(VexType val, Arc<WeightType> *adj)
// 操作结果：构造数据为val,边为eg的顶点
{
    data = val;
    firstarc = adj;
}
#endif