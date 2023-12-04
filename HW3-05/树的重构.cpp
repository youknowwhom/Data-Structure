#include <iostream>
#include <string>
#include <string.h>
#define OK 1
#define ERROR 0
#define TOVERFLOW -1
#define QERROR -1
#define QOVERFLOW -2
#define SOVERFLOW -2

#define STACK_INIT_SIZE 100000
#define STACKINCREMENT 10
using namespace std;

typedef int Status;
typedef int TElemType;

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
	int QueueLength();		//获取队列长度
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
		exit(QOVERFLOW);
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
		return QERROR;
	base[rear] = e;
	rear = (rear + 1) % MAXQSIZE;
	return OK;
}

template <class QElemType>
Status SqQueue <QElemType> ::DeQueue(QElemType& e)
{
	if (front == rear)
		return QERROR;
	e = base[front];
	front = (front + 1) % MAXQSIZE;
	return OK;
}

template <class QElemType>
Status SqQueue <QElemType> ::GetHead(QElemType& e)
{
	if (front == rear)
		return QERROR;
	e = base[front];
	return OK;
}

template <class QElemType>
bool SqQueue <QElemType>::QueueEmpty()
{
	return front == rear;
}

typedef struct BiTNode {
	TElemType data;
	BiTNode* lchild, * rchild;
}*BiTree;


template <class SElemType>
struct SqStack {
private:
	SElemType* base;
	SElemType* top;
	int stacksize;
public:
	SqStack();					//构造空栈
	~SqStack();					//销毁已有的栈
	Status ClearStack();		//把现有栈置空栈
	Status Top(SElemType& e);	//取栈顶元素
	Status Pop(SElemType& e);	//弹出栈顶元素
	Status Push(SElemType e);	//新元素入栈
	bool StackEmpty();			//是否为空栈
};

template <class SElemType>
SqStack<SElemType>::SqStack()
{
	base = new(nothrow) SElemType[STACK_INIT_SIZE];
	if (!base)
		exit(SOVERFLOW);
	top = base;
	stacksize = STACK_INIT_SIZE;
}

template <class SElemType>
SqStack<SElemType>::~SqStack()
{
	if (base)
		delete base;
	stacksize = 0;
}

template <class SElemType>
Status SqStack<SElemType>::ClearStack()
{
	//先销毁原有空间
	if (base)
		delete base;
	//重新申请
	base = new(nothrow) SElemType[STACK_INIT_SIZE];
	if (!base)
		exit(SOVERFLOW);
	top = base;
	stacksize = STACK_INIT_SIZE;
	return OK;
}

template <class SElemType>
Status SqStack<SElemType>::Top(SElemType& e)
{
	if (top == base)
		return ERROR;
	e = *(top - 1);
	return OK;
}

template <class SElemType>
Status SqStack<SElemType>::Pop(SElemType& e)
{
	if (top == base)
		return ERROR;
	e = *(--top);
	return OK;
}

template <class SElemType>
Status SqStack<SElemType>::Push(SElemType e)
{
	if (top - base >= stacksize) {
		SElemType* newbase = new(nothrow) SElemType[stacksize + STACKINCREMENT];
		if (!newbase)
			exit(SOVERFLOW);
		memcpy(newbase, base, sizeof(SElemType) * stacksize);
		delete base;
		base = newbase;
		top = base + stacksize;
		stacksize += STACKINCREMENT;
	}
	*top = e;
	top++;
	return OK;
}

template <class SElemType>
bool SqStack<SElemType> ::StackEmpty()
{
	return base == top;
}


int CreateBiTree(BiTree& T, string input)
{
	struct VisitNode {
		BiTree node;
		bool visit;
		VisitNode(BiTree nn = NULL, bool vv = false)
		{
			node = nn;
			visit = vv;
		}
	}q;
	SqStack<VisitNode> stack;

	BiTree last = NULL;
	BiTree p = new(nothrow) BiTNode;
	if (!p)
		exit(TOVERFLOW);
	p->lchild = p->rchild = NULL;
	stack.Push(VisitNode(p, false));
	T = p;

	int depth = 0, nowdepth = 0;

	for (unsigned int i = 0; i < input.size(); i++) {
		switch (input[i]) {
			case 'd':
				nowdepth++;
				depth = max(depth, nowdepth);
				stack.Pop(q);
				p = new(nothrow) BiTNode;
				if (!p)
					exit(TOVERFLOW);
				p->lchild = p->rchild = NULL;
				if (!q.visit) {	//还没有访问子节点
					q.visit = true;
					q.node->lchild = p;
					stack.Push(q);
				}
				else {			//是回溯回来的其他子节点 接到第一个左节点的后面
					stack.Push(q);
					last->rchild = p;
				}
				stack.Push(VisitNode(p, false));
				break;
			case 'u':
				nowdepth--;
				stack.Pop(q);
				last = q.node;
				break;
		}
	}

		return depth;
}

int GetDepth(BiTree T)
{
	struct NodeWithDepth {
		BiTree node;
		int depth;
		NodeWithDepth(BiTree bb = NULL, int dd = 1)
		{
			node = bb;
			depth = dd;
		}
	};
	SqQueue<NodeWithDepth> queue(20000);  //queue的最大长度
	queue.EnQueue(NodeWithDepth(T, 1));
	NodeWithDepth p;
	int depth = 0;
	while (!queue.QueueEmpty()) {
		if (queue.DeQueue(p) != OK)
			return ERROR;
		depth = max(depth, p.depth);
		if (p.node->lchild)
			queue.EnQueue(NodeWithDepth(p.node->lchild, p.depth + 1));
		if (p.node->rchild)
			queue.EnQueue(NodeWithDepth(p.node->rchild, p.depth + 1));
	}
	return depth;
}

int main()
{
	BiTree tree;
	string input;

	for (int i = 1; ; i++) {
		cin >> input;
		if (input == "#")
			break;
		
		cout << "Tree " << i << ": " << CreateBiTree(tree, input);
		cout << " => " << GetDepth(tree) - 1 << endl;
	}

	return 0;
}