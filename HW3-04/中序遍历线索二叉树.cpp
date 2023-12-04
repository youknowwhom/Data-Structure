#include <iostream>
#include <cstring>
#define OK 1
#define ERROR 0
#define TOVERFLOW -1
#define LOVERFLOW	-1
#define LIST_INIT_SIZE	10000
#define LISTINCREMENT	1000
typedef int Status;
using namespace std;

enum class PointerTag { LINK, THREAD };
typedef char TElemType;
typedef struct BiThrNode {
	TElemType data;						//结点元素
	BiThrNode* lchild, * rchild;		//左右孩子
	PointerTag LTag, RTag;				//左右孩子的Tag
}*BiThrTree;

typedef BiThrTree SqList_ElemType;
class SqList {
	SqList_ElemType* base;		//头指针
	int	length;					//表长
	int	listsize;				//申请的表空间
public:
	//顺序表的建立
	SqList();
	//顺序表的销毁
	~SqList();
	//重载等于号 目的是在复制线性表时不仅做浅拷贝 防止反复delete
	const SqList& operator=(const SqList& that);
	//求表长
	int ListLength();
	//插入元素
	Status ListInsert(int i, SqList_ElemType e);
	//取表中元素
	Status GetElem(int i, SqList_ElemType& e);
};


//顺序表的建立
SqList::SqList()
{
	this->base = new(nothrow) SqList_ElemType[LIST_INIT_SIZE];
	if (!this->base)
		exit(LOVERFLOW);
	this->length = 0;
	this->listsize = LIST_INIT_SIZE;
}

//顺序表的销毁
SqList::~SqList()
{
	if (this->base)
		delete[] this->base;
	this->base = NULL;
	this->length = 0;
	this->listsize = 0;

}

//重载等于号 目的是在复制线性表时不仅做浅拷贝 防止反复delete
const SqList& SqList::operator=(const SqList& that)
{
	length = that.length;
	listsize = that.listsize;
	base = new(nothrow) SqList_ElemType[listsize];
	if (!base)
		exit(LOVERFLOW);
	memcpy(base, that.base, listsize * sizeof(SqList_ElemType));
	return *this;
}

//求表长
int SqList::ListLength()
{
	return this->length;
}

//插入元素
Status SqList::ListInsert(int i, SqList_ElemType e)
{
	if (i < 1 || i > this->length + 1)
		return ERROR;
	if (this->length >= this->listsize) {
		SqList_ElemType* newbase = new SqList_ElemType[this->length + LISTINCREMENT];
		if (!newbase)
			exit(LOVERFLOW);
		memcpy(newbase, this->base, this->length * sizeof(SqList_ElemType));
		delete[] this->base;
		this->base = newbase;
		this->listsize += LISTINCREMENT;
	}
	SqList_ElemType* q = &(this->base[i - 1]);
	for (SqList_ElemType* p = &(this->base[this->length - 1]); p >= q; --p)
		*(p + 1) = *p;
	*q = e;
	++this->length;
	return OK;
}

//取表中元素
Status SqList::GetElem(int i, SqList_ElemType& e)
{
	if (i < 1 || i > this->length)
		return ERROR;
	e = base[i - 1];
	return OK;
}

//以下是树

Status CreateBiTree(BiThrTree& T)
{
	char e;
	cin >> e;
	if (e == '#')
		T = NULL;
	else {
		T = new(nothrow) BiThrNode;
		if (!T)
			exit(TOVERFLOW);
		T->data = e;
		T->LTag = T->RTag = PointerTag::LINK;
		CreateBiTree(T->lchild);
		CreateBiTree(T->rchild);
	}
	return OK;
}

void InTHREADing(BiThrTree p, BiThrTree& pre)
{
	if (p) {
		InTHREADing(p->lchild, pre);		//左子树线索化
		if (!p->lchild) {
			p->LTag = PointerTag::THREAD;
			p->lchild = pre;
		}

		if (!pre->rchild) {
			pre->RTag = PointerTag::THREAD;
			pre->rchild = p;
		}

		pre = p;
		InTHREADing(p->rchild, pre);		//右子树线索化
	}
}

Status InOrderTHREADing(BiThrTree& Thrt, BiThrTree T)
{
	BiThrTree pre;
	Thrt = new(nothrow) BiThrNode;
	if (!Thrt)
		exit(TOVERFLOW);
	Thrt->LTag = PointerTag::LINK;
	Thrt->RTag = PointerTag::THREAD;
	Thrt->rchild = Thrt;				//右指针回指
	if (!T)
		Thrt->lchild = Thrt;			//空树
	else {
		Thrt->lchild = T;
		pre = Thrt;
		InTHREADing(T, pre);
		pre->rchild = Thrt;
		pre->RTag = PointerTag::THREAD;
		Thrt->rchild = pre;
	}

	return OK;
}

Status InorderTraverse_Thr(BiThrTree T, SqList& traverse, Status(*Visit)(BiThrTree e, SqList& traverse))
{
	BiThrTree p = T->lchild;		//根节点
	TElemType last = -1;
	bool need_print = false;
	while (p != T) {
		//向左走到底
		while (p->LTag == PointerTag::LINK)
			p = p->lchild;
		if (Visit(p, traverse) != OK)
			return ERROR;
		while (p->RTag == PointerTag::THREAD && p->rchild != T) {
			p = p->rchild;
			Visit(p, traverse);
		}
		p = p->rchild;
	}

	return OK;
}

Status MyPrint(BiThrTree e, SqList& traverse)
{
	cout << e->data;
	return OK;
}

Status MyVisit(BiThrTree e, SqList& traverse)
{
	traverse.ListInsert(traverse.ListLength() + 1, e);

	return OK;
}

Status FindTarget(char tgt, SqList& traverse)
{
	BiThrTree p, q;
	bool is_found = false;
	for (int i = 1; i <= traverse.ListLength(); i++) {
		traverse.GetElem(i, p);
		if (p->data != tgt)
			continue;
		//是要寻找的
		is_found = true;

		cout << "succ is ";
		if (traverse.GetElem(i + 1, q) == OK)
			cout << q->data << (q->RTag == PointerTag::THREAD) << endl;
		else
			cout << "NULL" << endl;

		cout << "prev is ";
		if (traverse.GetElem(i - 1, q) == OK)
			cout << q->data << (q->LTag == PointerTag::THREAD) << endl;
		else
			cout << "NULL" << endl;
	}
	if (!is_found)
		cout << "Not found";
	return OK;
}

int main()
{
	BiThrTree treehead, tree;
	SqList traverse;
	char tgt;
	CreateBiTree(tree);
	cin >> tgt;

	InOrderTHREADing(treehead, tree);

	InorderTraverse_Thr(treehead, traverse, MyPrint);
	cout << endl;
	InorderTraverse_Thr(treehead, traverse, MyVisit);
	
	FindTarget(tgt, traverse);

	return 0;
}