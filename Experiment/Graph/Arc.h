#ifndef __ARC_H__
#define __ARC_H__

template <class WeightType>
struct Arc
{
    /* data */
    int archead;              // 弧头序号
    WeightType weight;        // 边的权值
    Arc<WeightType> *nextarc; // 下一条弧结点的指针

    Arc(/* args */);
    Arc(int v, WeightType w, Arc<WeightType> *next);
};

template <class WeightType>
Arc<WeightType>::Arc(/* args */)
{
    archead = -1;
}

template <class WeightType>
Arc<WeightType>::Arc(int v, WeightType w, Arc<WeightType> *next)
// 操作结果：构造邻接点序号为v，边的权为w，下一条边结点的指针为next的邻接边
{
	archead = v;
	weight = w;
	nextarc = next;
}

#endif