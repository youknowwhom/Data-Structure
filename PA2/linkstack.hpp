#pragma once
#include <iostream>
using namespace std;

typedef int Status;
#define LOVERFLOW -2
#define ERROR -1
#define OK	0

/* 链表节点 */
template <class LElemType>
class LNode {
public:
	LElemType data;		//存放的数据
	LNode* next;	    //直接后继的指针
};

/* 链表方式实现的栈 */
template <class LElemType>
struct LinkStack {
private:
	LNode<LElemType>* head;			//链表的头指针
public:
	LinkStack();					//构造空栈
	~LinkStack();					//销毁已有的栈
	Status ClearStack();		//把现有栈置空栈
	Status Top(LElemType& e);	//取栈顶元素
	Status Pop(LElemType& e);	//弹出栈顶元素
	Status Push(LElemType e);	//新元素入栈
	bool StackEmpty();			//是否为空栈
};

/**
 * @brief 构造空栈
 * @tparam LElemType 栈的元素类型
*/
template <class LElemType>
LinkStack<LElemType>::LinkStack()
{
	head = new(nothrow) LNode<LElemType>;		//头结点的建立
	if (!head)
		exit(LOVERFLOW);
	head->next = NULL;
}

/**
 * @brief 栈的销毁
 * @tparam LElemType 栈的元素类型
*/
template <class LElemType>
LinkStack<LElemType>::~LinkStack()
{
	LNode<LElemType>* p = head, * q;
	while (p) {
		q = p->next;
		delete p;
		p = q;
	}
}

/**
 * @brief 栈的清空
 * @tparam LElemType 栈的元素类型
*/
template <class LElemType>
Status LinkStack<LElemType>::ClearStack()
{
	LNode<LElemType>* p = head->next, q;
	while (p) {
		q = p->next;
		delete p;
		p = q;
	}
	head->next = NULL;	//头结点指向空
}

/**
 * @brief 取栈顶元素
 * @tparam LElemType 栈的元素类型
 * @param e 取的栈顶元素值
*/
template <class LElemType>
Status LinkStack<LElemType>::Top(LElemType& e)
{
	if (!head->next)
		return ERROR;
	e = head->next->data;
	return OK;
}

/**
 * @brief 弹出栈顶元素
 * @tparam LElemType 栈的元素类型
 * @param e 弹出的栈顶元素
*/
template <class LElemType>
Status LinkStack<LElemType>::Pop(LElemType& e)
{
	if (!head->next)
		return ERROR;
	LNode<LElemType>* p;
	p = head->next;
	e = p->data;
	head->next = p->next;
	delete p;
	return OK;
}

/**
 * @brief 新元素入栈
 * @tparam LElemType 栈的元素类型
 * @param e 入栈的元素
*/
template <class LElemType>
Status LinkStack<LElemType>::Push(LElemType e)
{
	LNode<LElemType>* q;
	q = new(nothrow) LNode<LElemType>;
	if (!q)
		exit(LOVERFLOW);
	q->data = e;
	q->next = head->next;
	head->next = q;
	return OK;
}

/**
 * @brief 栈是否为空
 * @tparam LElemType 栈的元素类型
*/
template <class LElemType>
bool LinkStack<LElemType> ::StackEmpty()
{
	return head->next == NULL;
}