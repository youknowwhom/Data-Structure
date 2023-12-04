#pragma once
#include <iostream>
using namespace std;

#define OK 0
#define ERROR -1
#define OVER_FLOW -2

typedef int Status;

template <class QElemType>
class SqQueue {
private:
	QElemType* base;
	int MAXQSIZE;
	int front;
	int rear;
public:
	SqQueue(int maxqsize);		//建立空队列（构造函数）
	~SqQueue();					//销毁队列（析构函数）
	int QueueLength();		    //获取队列长度
	Status EnQueue(QElemType e);		//新元素入队
	Status DeQueue(QElemType& e);		//队首元素出队
	Status GetHead(QElemType& e);		//获取队首元素
	Status ClearQueue();	//清空队列
	bool QueueEmpty();		//判断队列是否为空
};

template <class QElemType>
SqQueue <QElemType>::SqQueue(int maxqsize)
{
	MAXQSIZE = maxqsize + 1;  //空一个位置以区分满和空
	base = new(nothrow) QElemType[MAXQSIZE];
	if (!base)
		exit(OVER_FLOW);
	front = rear = 0;
}

template <class QElemType>
SqQueue <QElemType>::~SqQueue()
{
	if (base)
		delete base;
	front = rear = 0;
}

template <class QElemType>
Status SqQueue <QElemType>::ClearQueue()
{
	front = rear = 0;
	return OK;
}

template <class QElemType>
int SqQueue <QElemType> ::QueueLength()
{
	return (rear - front + MAXQSIZE) % MAXQSIZE;
}

template <class QElemType>
Status SqQueue <QElemType> ::EnQueue(QElemType e)
{
	if ((rear + 1) % MAXQSIZE == front)
		return ERROR;
	base[rear] = e;
	rear = (rear + 1) % MAXQSIZE;
	return OK;
}

template <class QElemType>
Status SqQueue <QElemType> ::DeQueue(QElemType& e)
{
	if (front == rear)
		return ERROR;
	e = base[front];
	front = (front + 1) % MAXQSIZE;
	return OK;
}

template <class QElemType>
Status SqQueue <QElemType> ::GetHead(QElemType& e)
{
	if (front == rear)
		return ERROR;
	e = base[front];
	return OK;
}

template <class QElemType>
bool SqQueue <QElemType>::QueueEmpty()
{
	return front == rear;
}
