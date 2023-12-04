#include <iostream>
using namespace std;
typedef int Status;
#define LOVERFLOW	-2
#define ERROR		-1
#define OK			0

typedef struct item {
	int p;		//项的系数
	int e;		//项的指数
}ElemType;

typedef struct LNode {
	ElemType data;		//存放的数据
	LNode* next;		//直接后继的指针
}*Linklist;

/* 建表 */
Status CreateList(Linklist& L, int n)
{
	Linklist p = NULL, q;
	q = L = (Linklist)malloc(sizeof(LNode));
	if (!L)
		return LOVERFLOW;
	L->next = NULL;   //带头节点的空链表
	for (int i = 0; i < n; i++) {
		p = (Linklist)malloc(sizeof(LNode));
		if (!p)
			return LOVERFLOW;
		getchar();
		cin >> p->data.p;
		getchar();
		cin >> p->data.e;
		q->next = p;
		q = p;
	}
	if(p)
		p->next = NULL;
	return OK;
}

/* 表的销毁 */
Status DestroyList(Linklist& L)
{
	Linklist p = L, q;
	while (p) {
		q = p->next;
		free(p);
		p = q;
	}
	return OK;
}

/* 取元素 */
Status GetElem(Linklist L, int i, ElemType& e)
{
	Linklist p = L->next;
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

/* 插入元素 */
Status ListInsert(Linklist& L, int i, ElemType e)
{
	Linklist p = L;
	int j = 0;
	while (p && j < i - 1) {
		p = p->next;
		++j;
	}
	if (!p || j > i - 1)
		return ERROR;
	Linklist s = (Linklist)malloc(sizeof(LNode));
	if (!s)
		return LOVERFLOW;
	s->data = e;
	s->next = p->next;
	p->next = s;
	return OK;
}

/* 删除元素 */
Status ListDelete(Linklist& L, int i, ElemType e)
{
	Linklist p = L, q;
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
	free(q);
	return OK;
}

/* 多项式相加 */
Status AddPolynomial(Linklist L1, Linklist L2, Linklist& sum, int mulp = 1, int mule = 0)
{
	Linklist p = L1->next, q = L2->next;
	ElemType cur;
	int cnt = 1;
	while (p && q) {
		if (p->data.e == q->data.e + mule) {
			cur.e = p->data.e;
			cur.p = p->data.p + q->data.p * mulp;
			ListInsert(sum, cnt++, cur);
			p = p->next;
			q = q->next;
		}
		else if (p->data.e < q->data.e + mule) {
			ListInsert(sum, cnt++, p->data);
			p = p->next;
		}
		else {
			cur.p = q->data.p * mulp;
			cur.e = q->data.e + mule;
			ListInsert(sum, cnt++, cur);
			q = q->next;
		}
	}
	if (!p)
		while (q) {
			cur.p = q->data.p * mulp;
			cur.e = q->data.e + mule;
			ListInsert(sum, cnt++, cur);
			q = q->next;
		}
	else
		while (p) {
			ListInsert(sum, cnt++, p->data);
			p = p->next;
		}
	return OK;
}

/* 多项式相乘 */
Status MulPolynomial(Linklist L1, Linklist L2, Linklist& ans)
{
	Linklist p = L1->next, newans;
	while (p) {
		CreateList(newans, 0);
		AddPolynomial(ans, L2, newans, p->data.p, p->data.e);
		DestroyList(ans);
		ans = newans;
		p = p->next;
	}
	return OK;
}

int main()
{
	Linklist L1, L2, ADD, MUL;
	int n, m;
	cin >> n;
	CreateList(L1, n);
	cin >> n;
	CreateList(L2, n);
	CreateList(ADD, 0);
	CreateList(MUL, 0);

	cin >> m;
	switch (m)
	{
		case 2:
		case 0:
			AddPolynomial(L1, L2, ADD);
			ElemType e;
			for (int i = 1; GetElem(ADD, i, e) == OK; i++)
				cout << e.p << " " << e.e << " ";
			cout << endl;
			if(!m)
				break;
		case 1:
			MulPolynomial(L1, L2, MUL);
			for (int i = 1; GetElem(MUL, i, e) == OK; i++)
				cout  << e.p << " " << e.e << " ";
			cout << endl;
			break;
	}

	/* 销毁链表 */
	DestroyList(L1);
	DestroyList(L2);
	DestroyList(ADD);
	DestroyList(MUL);

	return 0;
}