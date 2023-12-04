#include <iostream>
#include <queue>
using namespace std;

//二叉排序树的结点
struct node {
	int value;		//结点数值
	int times;		//出现的次数
	node* lchild, * rchild;
};

/**
 * @brief 创建新结点
 * @param n 新结点指针	
 * @param value 数值
*/
void CreateNode(node*& n, int value)
{
	n = new(nothrow) node;
	if (!n)
		exit(-1);
	n->value = value;
	n->times = 1;
	n->lchild = n->rchild = NULL;
}

/**
 * @brief 在二叉树插入新结点
 * @param T 当前搜索的结点
 * @param value 新结点的数值
*/
void Insert(node*& T, int value)
{
	//根结点
	if (!T)
		CreateNode(T, value);
	else if (T->value == value) {
		T->times++;
	}
	else if (T->value > value) {
		if (T->lchild)
			Insert(T->lchild, value);
		else
			CreateNode(T->lchild, value);
	}
	else {
		if (T->rchild)
			Insert(T->rchild, value);
		else
			CreateNode(T->rchild, value);
	}
}

/**
 * @brief 在二叉树中查找结点
 * @param T 当前搜索的结点
 * @param value 查找的结点数值
*/
int Search(node* T, int value)
{
	if (!T)
		return 0;
	else if (T->value == value)
		return T->times;
	else if (T->value > value) 
		Search(T->lchild, value);
	else 
		Search(T->rchild, value);
}

/**
 * @brief 删除二叉树中的结点
 * @param T 当前搜索的结点
 * @param value 删除的结点值
 * @return 是否成功删除
*/
bool Delete(node*& T, int value)
{
	if (!T)
		return false;  //没有该元素
	else if (T->value == value) {
		if (T->times != 1)
			T->times--;
		//只有单边子树
		else if (!T->rchild) {
			node* q = T;
			T = T->lchild;
			delete q;
		}
		else if (!T->lchild) {
			node* q = T;
			T = T->rchild;
			delete q;
		}
		//有左右两子树
		else {
			node* q = T, * s = T->lchild;
			while (s->rchild) {
				q = s;
				s = s->rchild;
			}
			T->value = s->value;
			T->times = s->times;
			//特判如果一开始左孩子没有右子树 则q没有空出的右孩子来接s的左孩子
			//(s原先在哪里就有哪边孩子空出)
			if (q != T)
				q->rchild = s->lchild;
			else
				q->lchild = s->lchild;
			delete s;
		}
		return true;
	}
	else if (T->value > value)
		return Delete(T->lchild, value);
	else
		return Delete(T->rchild, value);
}

/**
 * @brief 查询二叉查找树内最小值
 * @param T 当前搜索的结点
*/
int GetMin(node* T)
{
	if (T->lchild)
		return GetMin(T->lchild);
	else
		return T->value;
}

/**
 * @brief 中序遍历二叉查找树 记录到队列q中
 * @param T 当前遍历的结点
 * @param q 用于记录的队列
*/
void Traverse(node* T, queue<int>& q)
{
	if (!T)
		return;
	Traverse(T->lchild, q);
	q.push(T->value);
	Traverse(T->rchild, q);
}

int main()
{
	int n;
	node* root = NULL;
	cin >> n;
	for (int i = 0; i < n; i++) {
		int opt;
		queue<int> q;
		cin >> opt;
		switch (opt) {
			int x;
			case 1:
				cin >> x;
				Insert(root, x);
				break;
			case 2:
				cin >> x;
				if (!Delete(root, x))
					cout << "None" << endl;
				break;
			case 3:
				cin >> x;
				cout << Search(root, x) << endl;
				break;
			case 4:
				cout << GetMin(root) << endl;
				break;
			case 5:
				cin >> x;
				Traverse(root, q);
				int ans = -1;
				while (!q.empty() && q.front() < x) {
					ans = q.front();
					q.pop();
				}
				if (ans == -1)
					cout << "None" << endl;
				else
					cout << ans << endl;
		}
	}
	return 0;
}