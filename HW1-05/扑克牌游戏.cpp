#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <algorithm>
#include <cstring>
#include <string>
using namespace std;
typedef int Status;
#define LOVERFLOW	-1
#define	ERROR		-2
#define OK			0

typedef struct Poker {
	char type[128];		//扑克牌花色
	char num[4];		//扑克牌点数
	int getnum() const
	{
		switch (num[0]) {
			case 'A':
				return 1;
			case 'J':
				return 11;
			case 'Q':
				return 12;
			case 'K':
				return 13;
			default:
				if (num[1] == '0')
					return 10;
				else
					return num[0] - '0';
		}
	}
	bool operator<(const Poker& that) const
	{
		return this->getnum() > that.getnum();
	}
}Elemtype;
Elemtype vec[256];

typedef struct DuLNode {
	Elemtype data;			//该节点存放的扑克牌信息
	DuLNode* prior, * next;	//该节点的直接前驱、后继的指针
}* DuLinkList;

Status InitList(DuLinkList& L)
{
	L = (DuLinkList)malloc(sizeof(DuLNode));
	if (!L)
		return LOVERFLOW;
	L->prior = L;
	L->next = L;
	return OK;
}

Status InsertElem(DuLinkList& L, Elemtype e, bool from_head)
{
	DuLinkList newnode = (DuLinkList)malloc(sizeof(DuLNode));
	if (!newnode)
		return LOVERFLOW;
	newnode->data = e;
	if (from_head) {
		L->next->prior = newnode;
		newnode->next = L->next;
		L->next = newnode;
		newnode->prior = L;
	}
	else {
		L->prior->next = newnode;
		newnode->prior = L->prior;
		L->prior = newnode;
		newnode->next = L;
	}
	return OK;
}

Status PopItem(DuLinkList& L, Elemtype& e, bool from_head)
{
	if (L->next == L) {
		strcpy(e.type, "NULL");
		return OK;
	}
	if (from_head) {
		DuLinkList next = L->next;
		e = next->data;
		L->next->next->prior = L;
		L->next = L->next->next;
		free(next);
	}
	else {
		DuLinkList prior = L->prior;
		e = prior->data;
		L->prior->prior->next = L;
		L->prior = L->prior->prior;
		free(prior);
	}
	return OK;
}

Status PrintList(DuLinkList L, bool from_head)
{
	DuLinkList p = from_head ? L->next : L->prior;
	while (p != L) {
		cout << p->data.type << " " << p->data.num << endl;
		p = from_head ? p->next : p->prior;
	}
	return OK;
}

Status ExtractItem(DuLinkList& L, char* type, bool from_head)
{
	DuLinkList p = from_head ? L->next : L->prior, q;
	int vectorp = 0;
	while (p != L) {
		if (strcmp(p->data.type, type) == 0) {
			p->prior->next = p->next;
			p->next->prior = p->prior;
			q = p;
			vec[vectorp++] = p->data;
			p = from_head ? p->next : p->prior;
			free(q);
		}
		else
			p = from_head ? p->next : p->prior;
	}
	sort(vec, vec + vectorp);
	for (int i = 0; i < vectorp; i++) 
		InsertElem(L, vec[i], from_head);
	return OK;
}

int main()
{
	DuLinkList L;
	InitList(L);
	bool from_head = true;
	string input;
	int n;
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> input;
		if (input == "Append") {
			Elemtype cur;
			cin >> cur.type >> cur.num;
			InsertElem(L, cur, !from_head);   //放到牌堆底部
		}
		else if (input == "Revert")
			from_head = !from_head;
		else if (input == "Pop") {
			Elemtype cur;
			PopItem(L, cur, from_head);
			if (strcmp(cur.type, "NULL") == 0)
				cout << cur.type << endl;
			else
				cout << cur.type << " " << cur.num << endl;
		}
		else if (input == "Extract") {
			char input[128];
			cin >> input;
			ExtractItem(L, input, from_head);
		}
	}

	PrintList(L, from_head);
	return 0;
}