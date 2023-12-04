#pragma once
#include <iostream>
using namespace std;

#define STACK_INIT_SIZE 100000
#define STACKINCREMENT 10

typedef int Status;
#define SOVERFLOW -2
#define ERROR -1
#define OK	0

/* 顺序表方式实现的栈 */
template <class LElemType>
struct SqStack {
private:
	LElemType* base;
	LElemType* top;
	int stacksize;
public:
	SqStack();					//构造空栈
	~SqStack();					//销毁已有的栈
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
SqStack<LElemType>::SqStack()
{
	base = new(nothrow) LElemType[STACK_INIT_SIZE];
	if (!base)
		exit(SOVERFLOW);
	top = base;
	stacksize = STACK_INIT_SIZE;
}

/**
 * @brief 栈的销毁
 * @tparam LElemType 栈的元素类型
*/
template <class LElemType>
SqStack<LElemType>::~SqStack()
{
	if (base)
		delete base;
	stacksize = 0;
}

/**
 * @brief 栈的清空
 * @tparam LElemType 栈的元素类型
*/
template <class LElemType>
Status SqStack<LElemType>::ClearStack()
{
	//先销毁原有空间
	if (base)
		delete base;
	//重新申请
	base = new(nothrow) LElemType[STACK_INIT_SIZE];
	if (!base)
		exit(SOVERFLOW);
	top = base;
	stacksize = STACK_INIT_SIZE;
	return OK;
}

/**
 * @brief 取栈顶元素
 * @tparam LElemType 栈的元素类型
 * @param e 取的栈顶元素值
*/
template <class LElemType>
Status SqStack<LElemType>::Top(LElemType& e)
{
	if (top == base)
		return ERROR;
	e = *(top - 1);
	return OK;
}

/**
 * @brief 弹出栈顶元素
 * @tparam LElemType 栈的元素类型
 * @param e 弹出的栈顶元素
*/
template <class LElemType>
Status SqStack<LElemType>::Pop(LElemType& e)
{
	if (top == base)
		return ERROR;
	e = *(--top);
	return OK;
}

/**
 * @brief 新元素入栈
 * @tparam LElemType 栈的元素类型
 * @param e 入栈的元素
*/
template <class LElemType>
Status SqStack<LElemType>::Push(LElemType e)
{
	if (top - base >= stacksize) {
		LElemType* newbase = new(nothrow) LElemType[stacksize + STACKINCREMENT];
		if (!newbase)
			exit(SOVERFLOW);
		memcpy(newbase, base, sizeof(LElemType) * stacksize);
		delete base;
		base = newbase;
		top = base + stacksize;
		stacksize += STACKINCREMENT;
	}
	*top = e;
	top++;
	return OK;
}

/**
 * @brief 栈是否为空
 * @tparam LElemType 栈的元素类型
*/
template <class LElemType>
bool SqStack<LElemType> ::StackEmpty()
{
	return base == top;
}