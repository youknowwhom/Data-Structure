#include <iostream>
#include <string>
#include <string.h>
#define OK 1
#define ERROR 0
#define TOVERFLOW -1
#define QERROR -1
#define QOVERFLOW -2
using namespace std;

typedef int Status;
typedef char TElemType;		//树元素的数据类型

template <class QElemType>
class SqQueue {
private:
	QElemType* base;		//申请空间的指针
	int MAXQSIZE;			//队列的最大长度
	int front;				//队首指针
	int rear;				//队尾指针
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


typedef struct BiTNode {
	TElemType data;
	BiTNode* lchild, * rchild;
}*BiTree;

Status CreateBiTree(BiTree& T)
{
	int n;
	cin >> n;
	BiTNode* base = new(nothrow) BiTNode[n];
	bool* vis = new(nothrow) bool[n];
	if (!base || !vis)
		exit(TOVERFLOW);
	memset(vis, 0, n * sizeof(bool));
	for (int i = 0; i < n; i++) {
		char data;
		int lchild, rchild;
		string lchilds, rchilds;
		cin >> data >> lchilds >> rchilds;
		if (lchilds == "-")
			lchild = -1;
		else
			lchild = stoi(lchilds);
		if (rchilds == "-")
			rchild = -1;
		else
			rchild = stoi(rchilds);
		base[i].data = data;

		if (lchild != -1) {
			base[i].lchild = &base[lchild];
			vis[lchild] = true;
		}
		else
			base[i].lchild = NULL;

		if (rchild != -1) {
			base[i].rchild = &base[rchild];
			vis[rchild] = true;
		}
		else
			base[i].rchild = NULL;
	}

	for(int i = 0 ;i <n;i++)
		if (!vis[i]) {
			T = &base[i];
			break;
		}

	return OK;
}

//递归方法-是否同构
bool IsSimilarTree(BiTree T1, BiTree T2)
{
	//两边都走到头了 跳出
	if (!T1 && !T2)
		return true;
	//当前节点不同就跳出
	if ((T1 && !T2) || (!T1 && T2) || T1->data != T2->data)
		return false;

	return ((IsSimilarTree(T1->lchild, T2->lchild) && IsSimilarTree(T1->rchild, T2->rchild))
		 || (IsSimilarTree(T1->lchild, T2->rchild) && IsSimilarTree(T1->rchild, T2->lchild)));
}

//层次遍历
int GetDepth(BiTree T)
{
	struct NodeWithDepth{
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
	BiTree tree1, tree2;
	CreateBiTree(tree1);
	CreateBiTree(tree2);

	cout << (IsSimilarTree(tree1, tree2) ? "Yes" : "No") << endl;
	cout << GetDepth(tree1) << endl;
	cout << GetDepth(tree2) << endl;

	return 0;
}