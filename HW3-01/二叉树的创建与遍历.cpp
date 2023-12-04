#include <iostream>
#define OK 1
#define ERROR 0
#define TOVERFLOW -1
#define QERROR -1
#define QOVERFLOW -2
typedef int Status;
using namespace std;

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

//以下是树
typedef char TElemType;

typedef struct BiTNode {
	TElemType data;
	BiTNode* lchild, * rchild;
}*BiTree;

Status CreateBiTree(BiTree& T)
{
	char e;
	cin >> e;
	if (e == '#')
		T = NULL;
	else {
		T = new(nothrow) BiTNode;
		if (!T)
			exit(TOVERFLOW);
		T->data = e;
		CreateBiTree(T->lchild);
		CreateBiTree(T->rchild);
	}
	return OK;
}

//递归方法-先序遍历
Status PreOrderTraverse(BiTree T, Status(*visit)(TElemType e))
{
	if (T) {
		if ((*visit)(T->data) == OK)
			if (PreOrderTraverse(T->lchild, visit) == OK)
				if (PreOrderTraverse(T->rchild, visit) == OK)
					return OK;
		return ERROR;
	}
	else   //空树返回OK
		return OK;
}

//递归方法-中序遍历
Status InOrderTraverse(BiTree T, Status(*visit)(TElemType e))
{
	if (T) {
		if (InOrderTraverse(T->lchild, visit) == OK)
			if ((*visit)(T->data) == OK)
				if (InOrderTraverse(T->rchild, visit) == OK)
					return OK;
		return ERROR;
	}
	else   //空树返回OK
		return OK;
}

//递归方法-后序遍历
Status PostOrderTraverse(BiTree T, Status(*visit)(TElemType e))
{
	if (T) {
		if (PostOrderTraverse(T->lchild, visit) == OK)
			if (PostOrderTraverse(T->rchild, visit) == OK)
				if ((*visit)(T->data) == OK)
					return OK;
		return ERROR;
	}
	else   //空树返回OK
		return OK;
}

//层次遍历
Status DepthOrderTraverse(BiTree T, Status(*visit)(TElemType e))
{
	SqQueue<BiTree> queue(1000);  //queue的最大长度
	queue.EnQueue(T);
	BiTree p;
	while (!queue.QueueEmpty()) {
		if (queue.DeQueue(p) != OK)
			return ERROR;
		if ((*visit)(p->data) != OK)
			return ERROR;
		if (p->lchild)
			queue.EnQueue(p->lchild);
		if (p->rchild)
			queue.EnQueue(p->rchild);
	}
	return OK;
}

//递归方法-反中序遍历
Status ReverseInOrderTraverse(BiTree T, int depth, Status(*visit)(int depth, TElemType e))
{
	if (T) {
		if (ReverseInOrderTraverse(T->rchild, depth + 1, visit) == OK)
			if ((*visit)(depth, T->data) == OK)
				if (ReverseInOrderTraverse(T->lchild, depth + 1, visit) == OK)
					return OK;
		return ERROR;
	}
	else   //空树返回OK
		return OK;
}

Status VisitPrintNormal(TElemType e)
{
	cout << e;
	return OK;
}

Status VisitPrintConsole(int depth, TElemType e)
{
	for (int i = 0; i < depth; i++)
		cout << "     ";
	cout << e << endl;
	return OK;
}


int main()
{
	BiTree tree;
	CreateBiTree(tree);

	PreOrderTraverse(tree, VisitPrintNormal);
	cout << endl;

	InOrderTraverse(tree, VisitPrintNormal);
	cout << endl;

	PostOrderTraverse(tree, VisitPrintNormal);
	cout << endl;

	DepthOrderTraverse(tree, VisitPrintNormal);
	cout << endl;

	ReverseInOrderTraverse(tree, 0, VisitPrintConsole);

	return 0;
}