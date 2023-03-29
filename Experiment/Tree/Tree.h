#ifndef __TREE__
#define __TREE__

#include <iostream>
using namespace std;

// 树节点的结构体
struct TreeNode
{
    int data;        // 节点的值
    TreeNode *first; // 第一个子节点
    TreeNode *next;  // 兄弟节点
    TreeNode(int d) : data(d), first(NULL), next(NULL) {}
};

// 树的类
class Tree
{
public:
    Tree() : root(NULL) {}
    ~Tree() { delete root; }

    void addNode(int parent, int data); // 添加节点
    int getHeight();                    // 求树的高度
    int getDegree();                    // 求树的度
    int getLeafCount();                 // 求叶子节点个数

private:
    TreeNode *root;                                 // 树的根节点
    TreeNode *findNode(TreeNode *node, int target); // 在以 node 为根的树上找 target
    int getHeight(TreeNode *node);                  // 递归求树的高度
    int getDegree(TreeNode *node);                  // 递归求树的度
    int getLeafCount(TreeNode *node);               // 递归求叶子节点个数
};

TreeNode *Tree::findNode(TreeNode *node, int target)
{
    if (node == NULL)
        return NULL;
    if (node->data == target)
        return node;
    TreeNode *cur = node->first;
    while (cur != NULL)
    {
        TreeNode *temp = findNode(cur, target);
        if (temp != NULL)
            return temp;
        cur = cur->next;
    }
    return NULL;
}

// 添加节点
void Tree::addNode(int parent, int data)
{
    if (root == NULL)
    { // 如果树为空，创建根节点
        root = new TreeNode(data);
        return;
    }
    TreeNode *parentNode = findNode(root, parent);
    if (parentNode == NULL)
    { // 如果未找到父节点，输出错误信息
        cout << "Error: parent node not found." << endl;
        return;
    }

    if (parentNode->first == NULL)
    { // 如果父节点没有子节点，创建第一个子节点
        parentNode->first = new TreeNode(data);
    }
    else
    { // 如果父节点有子节点，创建兄弟节点
        TreeNode *siblingNode = parentNode->first;
        while (siblingNode->next != NULL)
        {
            siblingNode = siblingNode->next;
        }
        siblingNode->next = new TreeNode(data);
    }
}

// 求树的高度
int Tree::getHeight()
{
    return getHeight(root);
}

// 求树的度
int Tree::getDegree()
{
    return getDegree(root);
}

// 求叶子节点个数
int Tree::getLeafCount()
{
    return getLeafCount(root);
}

// 递归求树的高度
int Tree::getHeight(TreeNode *node)
{
    if (node == NULL)
        return 0;
    if (node->first == NULL)
        return 1;
    int childHeight = 0;
    TreeNode *cur = node->first;
    while (cur != NULL)
    {
        childHeight = max(childHeight, getHeight(cur));
        cur = cur->next;
    }
    return childHeight + 1;
}

// 递归求树的度
int Tree::getDegree(TreeNode *node)
{
    if (node == NULL || node->first == NULL)
    { // 如果节点为空，返回0
        return 0;
    }

    int childDegree = 0, count = 0;
    TreeNode *cur = node->first;
    while (cur != NULL) 
    {
        childDegree = max(childDegree, getDegree(cur));
        count++;
        cur = cur->next;
    }

    return max(count, childDegree);
}

// 递归求叶子节点个数
int Tree::getLeafCount(TreeNode *node)
{
    if (node == NULL)
    { // 如果节点为空，返回0
        return 0;
    }
    else if (node->first == NULL)
    { // 如果节点没有子节点，返回1
        return 1;
    }
    else
    { // 否则在所有子节点中累加叶子节点个数
        TreeNode *childNode = node->first;
        int leafCount = 0;
        while (childNode != NULL)
        {
            leafCount += getLeafCount(childNode);
            childNode = childNode->next;

        }
        return leafCount;
    }
}

#endif