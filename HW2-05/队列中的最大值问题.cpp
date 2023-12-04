#include <iostream>
#include <cstring>
using namespace std;
char input[100010];
bool valid[100010];

int MAX_SIZE;

typedef int Status;
#define SOVERFLOW -3
#define FULL	  -2
#define EMPTY -1
#define OK	0

typedef int ElemType;
struct SqStack {
private:
	ElemType* base;
	ElemType* top;
	int stacksize;
public:
	SqStack();					//构造空栈
	~SqStack();					//销毁已有的栈
	Status ClearStack();		//把现有栈置空栈
	Status Top(ElemType& e);	//取栈顶元素
	Status Pop(ElemType& e);	//弹出栈顶元素
	Status Push(ElemType e);	//新元素入栈
	bool StackEmpty();			//是否为空栈
};

SqStack::SqStack()
{
	base = new(nothrow) ElemType[MAX_SIZE];
	if (!base)
		exit(SOVERFLOW);
	top = base;
	stacksize = MAX_SIZE;
}

SqStack::~SqStack()
{
	if (base)
		delete base;
	stacksize = 0;
}

Status SqStack::ClearStack()
{
	//先销毁原有空间
	if (base)
		delete base;
	//重新申请
	base = new(nothrow) ElemType[MAX_SIZE];
	if (!base)
		exit(SOVERFLOW);
	top = base;
	stacksize = MAX_SIZE;
	return OK;
}

Status SqStack::Top(ElemType& e)
{
	if (top == base)
		return EMPTY;
	e = *(top - 1);
	return OK;
}

Status SqStack::Pop(ElemType& e)
{
	if (top == base)
		return EMPTY;
	e = *(--top);
	return OK;
}

Status SqStack::Push(ElemType e)
{
	if (top - base >= stacksize) 
		return FULL;
	*top = e;
	top++;
	return OK;
}

bool SqStack::StackEmpty()
{
	return base == top;
}


class SqStack_WithMax {
private:
	SqStack Value, Max;
public:
	Status Top(ElemType& e);		//取栈顶元素
	Status Pop(ElemType& e);		//弹出栈顶元素
	Status Push(ElemType e);		//新元素入栈
	Status GetMax(ElemType& e);		//取栈中元素最大值
	bool StackEmpty();				//是否为空栈
};

Status SqStack_WithMax::Top(ElemType& e)
{
	return Value.Top(e);
}

Status SqStack_WithMax::Pop(ElemType& e)
{
	ElemType max;
	Max.Top(max);
	if (Value.StackEmpty())
		return EMPTY;
	Value.Pop(e);
	
	if (e == max)
		Max.Pop(max);
	return OK;
}

Status SqStack_WithMax::Push(ElemType e)
{
	ElemType max;
	Max.Top(max);
	if (Value.Push(e) == FULL)
		return FULL;
	if (Max.StackEmpty() || e >= max) {
		Max.Push(e);
	}
	return OK;
}

Status SqStack_WithMax::GetMax(ElemType& e)
{
	return Max.Top(e);
}

bool SqStack_WithMax::StackEmpty()
{
	return Value.StackEmpty();
}

class SqQueue_WithMax {
private:
	SqStack_WithMax a, b;
	int ElemNum = 0;
public:
	Status EnQueue(ElemType e);		//在队尾插入元素e
	Status DeQueue(ElemType& e);	//弹出队首的元素(若非空)
	Status GetMax(ElemType& e);		//取队列最大值
	bool QueueEmpty();				//判断队列是否为空
};

Status SqQueue_WithMax::EnQueue(ElemType e)
{
	if (ElemNum >= MAX_SIZE)
		return FULL;
	ElemNum++;
	return a.Push(e);
}

Status SqQueue_WithMax::DeQueue(ElemType& e)
{
	if (ElemNum == 0)
		return EMPTY;
	ElemNum--;
	if (!b.StackEmpty())
		return b.Pop(e);
	else {
		ElemType tmp;
		while (!a.StackEmpty()) {
			a.Pop(tmp);
			b.Push(tmp);
		}
		return b.Pop(e);
	}
}

Status SqQueue_WithMax::GetMax(ElemType& e)
{
	if (ElemNum == 0) 
		return EMPTY;
	
	e = 0x80000000;  //先置为最小值
	ElemType e2;
	if (!b.StackEmpty())
		b.GetMax(e);
	if (!a.StackEmpty()) {
		a.GetMax(e2);
		e = max(e, e2);
	}	
	return OK;
}

bool SqQueue_WithMax::QueueEmpty()
{
	return ElemNum == 0;
}

int main()
{
	cin >> MAX_SIZE;
	SqQueue_WithMax Queue;
	char input[32];
	while (true) {
		cin >> input;
		if (strcmp(input, "enqueue") == 0) {
			ElemType e;
			cin >> e;
			if (Queue.EnQueue(e) == FULL)
				cout << "Queue is Full" << endl;
		}
		else if (strcmp(input, "dequeue") == 0) {
			ElemType e;
			if (Queue.DeQueue(e) == EMPTY)
				cout << "Queue is Empty" << endl;
			else
				cout << e << endl;
		}
		else if (strcmp(input, "max") == 0) {
			ElemType e;
			if (Queue.GetMax(e) == EMPTY)
				cout << "Queue is Empty" << endl;
			else
				cout << e << endl;
		}
		else
			break;
	}

	ElemType e;
	while (!Queue.QueueEmpty())
	{
		Queue.DeQueue(e);
		cout << e;
		if(!Queue.QueueEmpty())
			cout << " ";
	}
	cout << endl;
	return 0;
}