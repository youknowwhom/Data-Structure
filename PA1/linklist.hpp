#pragma once
typedef int Status;
#define LOVERFLOW	-1
#define ERROR		-2
#define OK			0
using namespace std;

/* 链表节点 */
template <class LinkList_ElemType>
class LNode {
public:
	LinkList_ElemType data;		//存放的数据
	LNode* next;				//直接后继的指针
};

/* 链表 */
template <class LinkList_ElemType>
class LinkList {
	LNode <LinkList_ElemType>* base;
	typedef LNode<LinkList_ElemType> LNode_;
	typedef LNode<LinkList_ElemType>* LNodep;
public:
	//建立带头节点的空链表
	LinkList();
	//表的销毁
	~LinkList();
	//插入元素
	Status ListInsert(int i, const LinkList_ElemType& e);
	//删除元素
	Status ListDelete(int i, LinkList_ElemType& e);
	//取元素
	Status GetElem(int i, LinkList_ElemType& e);
	//取元素地址
	Status LocatePosition(const LinkList_ElemType& e, LinkList_ElemType*& ep);
	//返回第一个链表中该元素的index 若不存在返回NULL
	int LocateElem(const LinkList_ElemType& e);
	//找到第一个链表中的该元素，并替换(重载元素=后可以用于查找详细信息)
	Status SearchElem(LinkList_ElemType& e);
};

/**
 * @brief 建立带头节点的空链表
 * @tparam LinkList_ElemType 链表元素
*/
template <class LinkList_ElemType>
LinkList<LinkList_ElemType>::LinkList()
{
	this->base = new(nothrow) LNode_;
	if (!base)
		exit(LOVERFLOW);
	base->next = NULL;   //带头节点的空链表
}

/**
 * @brief 链表的销毁
 * @tparam LinkList_ElemType 链表元素
*/
template <class LinkList_ElemType>
LinkList<LinkList_ElemType>::~LinkList()
{
	LNodep p = base, q;
	while (p) {
		q = p->next;
		delete p;
		p = q;
	}

}

/**
 * @brief 向链表中位置i处插入元素
 * @tparam LinkList_ElemType 链表元素
 * @param i 位置i
 * @param e 插入的元素
 * @return 插入状态
*/
template <class LinkList_ElemType>
Status LinkList<LinkList_ElemType>::ListInsert(int i, const LinkList_ElemType& e)
{
	LNodep p = base;
	int j = 0;
	while (p && j < i - 1) {
		p = p->next;
		++j;
	}
	if (!p || j > i - 1)
		return ERROR;
	LNodep s = new(nothrow)LNode_;
	if (!s)
		return LOVERFLOW;
	s->data = e;
	s->next = p->next;
	p->next = s;
	return OK;
}


/**
 * @brief 在链表中位置i处删除元素
 * @tparam LinkList_ElemType 链表元素
 * @param i 删除位置i
 * @param e 取出删除的元素
 * @return 删除状态
*/
template <class LinkList_ElemType>
Status LinkList<LinkList_ElemType>::ListDelete(int i, LinkList_ElemType& e)
{
	LNodep p = base, q;
	int j = 0;
	while (p->next && j < i - 1) {
		p = p->next;
		++j;
	}
	if (!(p->next) || j > i - 1)
		return ERROR;
	q = p->next;
	p->next = q->next;
	e = q->data;
	delete q;
	return OK;
}


/**
 * @brief 取出链表中位置i处的元素
 * @tparam LinkList_ElemType 链表元素 
 * @param i 元素的位置i
 * @param e 取出的元素
 * @return 取出状态
*/
template <class LinkList_ElemType>
Status LinkList<LinkList_ElemType>::GetElem(int i, LinkList_ElemType& e)
{
	LNodep p = base->next;
	int j = 1;
	while (p && j < i) {
		p = p->next;
		++j;
	}
	if (!p || j > i)
		return ERROR;
	e = p->data;
	return OK;
}


/**
 * @brief 取出链表中相应元素的地址
 * @tparam LinkList_ElemType 链表元素
 * @param e 欲取出地址的元素
 * @param ep 取出的元素地址
 * @return 取出状态
*/
template <class LinkList_ElemType>
Status LinkList<LinkList_ElemType>::LocatePosition(const LinkList_ElemType& e, LinkList_ElemType*& ep)
{
	LNodep p = base->next;
	while (p) {
		if (p->data == e) {
			ep = &p->data;
			return OK;
		}
		p = p->next;
	}
	return ERROR;  //没有该元素
}


/**
 * @brief 返回第一个链表中该元素的index 若不存在返回NULL
 * @tparam LinkList_ElemType 链表元素
 * @param e 查找的元素
 * @return 查找状态
*/
template <class LinkList_ElemType>
int LinkList<LinkList_ElemType>::LocateElem(const LinkList_ElemType& e)
{
	LNodep p = base;
	int j = 0;
	while (p->next) {
		p = p->next;
		++j;
		if (p->data == e) {
			return j;
		}
	}
	return NULL;
}

/**
 * @brief 找元素的详细信息(通过重载=通过某个结构体成员变量找到对应元素 直接取出所有信息)
 * @tparam LinkList_ElemType 链表元素
 * @param e 查找的元素
 * @return 查找状态
*/
template <class LinkList_ElemType>
Status LinkList<LinkList_ElemType>::SearchElem(LinkList_ElemType& e)
{
	LNodep p = base->next;
	while (p) {
		if (p->data == e) {
			e = p->data;
			return OK;
		}
		p = p->next;
	}
	return ERROR;  //没有该元素
}