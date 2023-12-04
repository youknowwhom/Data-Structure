#include <iostream>
using namespace std;
#define LIST_INIT_SIZE	100
#define LISTINCREMENT	10

typedef int ElemType;

typedef int Status;
#define LOVERFLOW	-1
#define ERROR		-2
#define OK			0

struct SqList{
	ElemType *beg;
	int	length;
	int	listsize;
};

/*
*Status InitList(SqList& L)
* @para L需要初始化的顺序表的指针
*/
Status InitList(SqList& L)  //空线性表的建立
{
	L.beg = (ElemType*)malloc(LIST_INIT_SIZE * sizeof(ElemType));
	if (!L.beg)
		exit(LOVERFLOW);
	L.length = 0;
	L.listsize = LIST_INIT_SIZE;
	return OK;
}

/* 线性表的销毁 */
Status DestroyList(SqList& L)
{
	if (L.beg)
		free(L.beg);
	L.length = 0;
	L.listsize = 0;
	return OK;
}

/* 求表长 */
int ListLength(SqList L)
{
	return L.length;
}

/* 插入元素 */
Status ListInsert(SqList& L, int i, ElemType e)
{
	if (i < 1 || i > L.length + 1)
		return ERROR;
	if (L.length >= L.listsize) {
		ElemType* newbeg = (ElemType*)realloc(L.beg, (L.listsize + LISTINCREMENT) * sizeof(ElemType));
		if (!newbeg)
			exit(LOVERFLOW);
		L.beg = newbeg;
		L.listsize += LISTINCREMENT;
	}
	ElemType* q = &(L.beg[i - 1]);
	for (ElemType* p = &(L.beg[L.length - 1]); p >= q; --p)
		*(p + 1) = *p;
	*q = e;
	++L.length;
	return OK;
}

/* 删除元素 */
Status ListDelete(SqList& L, int i, ElemType& e)
{
	if (i < 1 || i > L.length)
		return ERROR;
	ElemType* p = &(L.beg[i - 1]), * q = L.beg + L.length - 1;
	e = *p;
	for (++p; p <= q; ++p)
		*(p - 1) = *p;
	--L.length;
	return OK;
}

/* 取表中元素 */
Status GetElem(SqList& L, int i, ElemType& e)
{
	if (i < 1 || i > L.length)
		return ERROR;
	e = L.beg[i - 1];
	return OK;
}

int main()
{
	int n;
	SqList L;
	InitList(L);

	cin >> n;
	for (int i = 0; i < n; i++) {
		ElemType e;
		cin >> e;
		ListInsert(L, ListLength(L) + 1, e);
	}

	for (int i = 0; i < ListLength(L); i++) {
		for (int j = i + 1; j < ListLength(L); j++) {
			ElemType iv, jv;
			GetElem(L, i + 1, iv);
			GetElem(L, j + 1, jv);
			if (iv == jv) {
				ListDelete(L, j + 1, jv);
				j--;
			}
		}
	}
	for (int i = 0; i < ListLength(L); i++) {
		ElemType out;
		GetElem(L, i + 1, out);
		cout << out << " ";
	}

	DestroyList(L);
	cout << endl;

	return 0;
}