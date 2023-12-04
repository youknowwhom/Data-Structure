#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <string>
using namespace std;
#define LIST_INIT_SIZE	100
#define LISTINCREMENT	10

typedef struct info{
	char id[32];
	char name[32];
}ElemType;

typedef int Status;
#define LOVERFLOW	-1
#define ERROR		-2
#define OK			0

struct SqList {
	ElemType* beg;
	int	length;
	int	listsize;
};

/* 空线性表的建立 */
Status InitList(SqList& L)
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
	memcpy(q, &e, sizeof(e));
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
		cin >> e.id >> e.name;
		ListInsert(L, ListLength(L) + 1, e);
	}

	while (true) {
		string input;
		cin >> input;
		if (input == "end") {
			cout << ListLength(L) << endl;
			break;
		}
		else if (input == "insert"){
			int i;
			ElemType e;
			cin >> i >> e.id >> e.name;
			Status ret = ListInsert(L, i, e);
			if (ret == ERROR)
				cout << "-1" << endl;
			else
				cout << "0" << endl;
		}
		else if (input == "remove") {
			int i;
			ElemType e;
			cin >> i;
			Status ret = ListDelete(L, i, e);
			if (ret == ERROR)
				cout << "-1" << endl;
			else
				cout << "0" << endl;
		}
		else {
			string input2;
			int i;
			char name[128], id[128];
			cin >> input2;
			if (input2 == "no")
				cin >> id;
			else
				cin >> name;
			ElemType cur;
			for (i = 0; i < ListLength(L); i++) {
				GetElem(L, i + 1, cur);
				if (input2 == "name" && strcmp(cur.name,name) == 0)
					break;
				else if (input2 == "no" && strcmp(cur.id, id) == 0)
					break;
			}
			if (i == ListLength(L)) {
				cout << "-1" << endl;
			}
			else
				cout << i + 1 << " " << cur.id << " " << cur.name << endl;
		}
	}
	DestroyList(L);
	return 0;
}