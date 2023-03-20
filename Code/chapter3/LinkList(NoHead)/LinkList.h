#ifndef __LK_LIST_H__
#define __LK_LIST_H__

#include "Node.h"					// 结点类
#include "Assistance.h"

// 单链表类
template <class ElemType>
class LinkList 
{
protected:
//  单链表的数据成员
	Node<ElemType> *head;				// 头结点指针
	int length;							// 单链表长度 

public:
//  单链表的函数成员 
	LinkList();							// 无参数的构造函数，已实现
	LinkList(ElemType v[], int n);		// 有参数的构造函数，已实现
	virtual ~LinkList();				// 析构函数
	int GetLength() const;				// 求单链表长度，已实现	 
	bool IsEmpty() const;	 			// 判断单链表是否为空，已实现
	void Clear();						// 将单链表清空
	void Reverse();						// 将单链表倒转
	void Traverse(void (*Visit)(const ElemType &)) const;// 遍历单链表
	int LocateElem(const ElemType &e) const;	         // 元素定位 
	Status GetElem(int position, ElemType &e) const;	 // 求指定位置的元素	
	Status SetElem(int position, const ElemType &e);	 // 设置指定位置的元素值
	Status DeleteElem(int position, ElemType &e);		 // 删除元素，已实现
	Status InsertElem(int position, const ElemType &e);	 // 在制定位置插入元素，已实现
	Status InsertElem(const ElemType &e);	             // 在表尾插入元素
	LinkList(const LinkList<ElemType> &la);            // 复制构造函数
	LinkList<ElemType> &operator =(const LinkList<ElemType> &la); // 重载赋值运算 
};


// 单链表类的实现部分


template <class ElemType>
LinkList<ElemType>::LinkList()
// 操作结果：构造一个空链表
{
	head = NULL;					// 构造头结点 
	length = 0;						// 初始化单链表长度为0 
}

template <class ElemType>
LinkList<ElemType>::LinkList(ElemType v[], int n)
// 操作结果：根据数组v中的元素构造单链表
{
    Node<ElemType> *p;
	for (int i = 0; i < n; i++) {
	    p = new Node<ElemType>(v[i],NULL);
		assert(p);            // 构造元素结点失败，终止程序运行 
		if (i == 0)
			head = p;
	    p = p->next;
    }
	length = n;						// 初始化单链表长度为n
}

template <class ElemType>
LinkList<ElemType>::~LinkList()
// 操作结果：销毁单链表
{
	Clear();			// 清空单链表
	head = NULL;
}

template <class ElemType>
int LinkList<ElemType>::GetLength() const
// 操作结果：返回单链表的长度 
{
	return length;
}

template <class ElemType>
bool LinkList<ElemType>::IsEmpty() const
// 操作结果：如单链表为空，则返回true，否则返回false
{
	return head == NULL;
}

template <class ElemType>
void LinkList<ElemType>::Clear()
// 操作结果：清空单链表,删除单链表中所有元素结点 
{
    Node<ElemType> *p = head;
	while (p != NULL) {
		head = p->next;
        delete p; 
		p = head;
	}
	length = 0;
}

template <class ElemType>
void LinkList<ElemType>::Reverse()
// 操作结果：倒转单链表
{
    Node<ElemType> *p = head, *q;			// p 记录尚未倒转的单链表的第一个节点
	head = NULL;							// 以 head 为头节点的链表是已经倒转的单链表
	while(p != NULL){						// 如果 p->next 为 NULL，证明已经没有节点尚未倒转了
		q = p->next;						// 用 q 记录 p 的下一个节点
		p->next = head;						// 要把 p 插到头节点 head 之前
		head = p;							// p 成为新的头节点
		p = q;								// p 去到尚未倒转的单链表的第一个节点
	}
}

template <class ElemType>
void LinkList<ElemType>::Traverse(void (*Visit)(const ElemType &)) const 
// 操作结果：依次对单链表的每个元素调用函数(*visit)访问
{
    Node<ElemType> *p = head;
	while (p != NULL) {
		(*Visit)(p->data);	// 对单链表中每个元素调用函数(*visit)访问 
		p = p->next;
	}
}

template <class ElemType>
int LinkList<ElemType>::LocateElem(const ElemType &e) const
// 元素定位 
{
    Node<ElemType> *p = head;
    int count = 1;
	while (p != NULL && p->data != e) {
	    count++;
		p = p->next;
	}
    return  (p != NULL) ? count : 0;
}

template <class ElemType>
Status LinkList<ElemType>::GetElem(int i, ElemType &e) const
// 操作结果：当单链表存在第i个元素时，用e返回其值，函数返回ENTRY_FOUND,
//	否则函数返回NOT_PRESENT
{
	if (i < 1 || i > length)
		return RANGE_ERROR;   			 
 	else	{
		Node<ElemType> *p = head;
		int count;
		for (count = 1; count < i; count++)
		  p = p->next;	            // p指向第i个结点
		e = p->data;				// 用e返回第i个元素的值
		return ENTRY_FOUND;
	}
}

template <class ElemType>
Status LinkList<ElemType>::SetElem(int i, const ElemType &e)
// 操作结果：将单链表的第i个位置的元素赋值为e,
//	i的取值范围为1≤i≤length,
//	i合法时函数返回SUCCESS,否则函数返回RANGE_ERROR
{
	if (i < 1 || i > length)	
		return RANGE_ERROR;   			 
	else	{	
		Node<ElemType> *p = head;
		int count;
		for (count = 1; count < i; count++)
		  p = p->next;	           // 取出指向第i个结点的指针	
		p->data = e;			   // 修改第i个元素的值为e 
		return SUCCESS;
	}
}

template <class ElemType>
Status LinkList<ElemType>::DeleteElem(int i, ElemType &e)
// 操作结果：删除单链表的第 i 个位置的元素, 并用 e 返回其值,
//	i 的取值范围为 1 ≤ i ≤ length,
//	i 合法时函数返回 SUCCESS,否则函数返回 RANGE_ERROR
{
	if (i < 1 || i > length)		
		return RANGE_ERROR;   // i 范围错		 
 	else	{
		Node<ElemType> *p = head, *q = NULL;
		if (i == 1) {
			q = head;								// q 指向第 i 个结点
			head = head->next;						// 删除结点
		}
		else {
			for(int cnt = 1; cnt < i - 1; ++cnt){	// p 指向第 i - 1 个结点
				p = p->next;
			}
			q = p->next;							// q 指向第 i 个结点
			p->next = q->next;						// 删除结点
		}
		e = q->data;								// 用 e 返回被删结点元素值
		delete q;									// 释放被删结点
		length--;									// 删除成功后元素个数减 1 
		return SUCCESS;
	}
}

template <class ElemType>
Status LinkList<ElemType>::InsertElem(int i, const ElemType &e)
// 操作结果：在单链表的第 i 个位置前插入元素 e
//	i 的取值范围为 1 ≤ i ≤ length +1
//	i 合法时返回 SUCCESS, 否则函数返回 RANGE_ERROR
{
	if (i < 1 || i > length + 1)
		return RANGE_ERROR;   			 
 	else {
		Node<ElemType> *p = head, *q = NULL;
		if(i == 1) {
			q = new Node<ElemType>(e, head);		// 生成新结点q
			assert(q);								// 申请结点失败，终止程序运行
			head = q;
		}
		else {
			for(int cnt = 1; cnt < i - 1; ++cnt){	// p 指向第 i - 1 个结点
				p = p->next;
			}
			q = new Node<ElemType>(e, p->next);		// 生成新结点 q
			assert(q);								// 申请结点失败，终止程序运行
			p->next = q;							// 将 q 插入到链表中
		}
		length++;									// 插入成功后，单链表长度加 1 
		return SUCCESS;
	}
}

template <class ElemType>
Status LinkList<ElemType>::InsertElem(const ElemType &e)
// 操作结果：在单链表的表尾位置插入元素e
{
	Node<ElemType> *p, *q;
	q = new Node<ElemType>(e, NULL);    // 生成新结点q
    assert(q);                          // 申请结点失败，终止程序运行
	if (length == 0) head = q;
	for (p = head; p->next != NULL; p = p->next) ;	// p指向表尾结点	
    p->next = q;                        // 在单链表的表尾位置插入新结点 
	length++;							// 插入成功后，单链表长度加1 
	return SUCCESS;
}

template <class ElemType>
LinkList<ElemType>::LinkList(const LinkList<ElemType> &la)
// 操作结果：复制构造函数，由单链表la构造新单链表
{
	int laLength = la.GetLength();	// 取被复制单链表的长度
	ElemType e;
	length = 0;						// 初始化元素个数

	for (int i = 1; i <= laLength; i++)	{	// 复制数据元素
		la.GetElem(i, e);	       // 取出第i个元素的值放在e中 
		InsertElem(e);		       // 将e插入到当前单链表的表尾 
	}
}

template <class ElemType>
LinkList<ElemType> &LinkList<ElemType>::operator =(const LinkList<ElemType> &la)
// 操作结果：重载赋值运算符，将单链表la赋值给当前单链表
{
	if (&la != this)	{
		int laLength = la.GetLength();// 取被赋值单链表的长度
		ElemType e;
		Clear();							// 清空当前单链表
		for (int i = 1; i <= laLength; i++)		{
			la.GetElem(i, e);		    // 取出第i个元素的值放在e中
			InsertElem(e);		            // 将e插入到当前单链表的表尾
		}
	}
	return *this;
}

#endif

