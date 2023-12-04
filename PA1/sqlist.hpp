#pragma once
#include <iostream>
#include <cstring>
#define LIST_INIT_SIZE	50
#define LISTINCREMENT	10
typedef int Status;
#define LOVERFLOW	-1
#define ERROR		-2
#define OK			0
using namespace std;

template <class SqList_ElemType>
/* 顺序表 */
class SqList {
	SqList_ElemType* base;		//头指针
	int	length;					//表长
	int	listsize;				//申请的表空间
public:
	//顺序表的建立
	SqList();
	//顺序表的销毁
	~SqList();
	//重载等于号 目的是在复制顺序表时不仅做浅拷贝 防止反复delete
	const SqList& operator=(const SqList& that);
	//求表长
	int ListLength();
	//插入元素
	Status ListInsert(int i, SqList_ElemType e);
	//取表中元素
	Status GetElem(int i, SqList_ElemType& e);
	//查找元素是否在顺序表中
	bool IsInList(const SqList_ElemType& e);
};


/**
 * @brief 顺序表的建立
 * @tparam SqList_ElemType 顺序表元素
*/
template <class SqList_ElemType>
SqList<SqList_ElemType>::SqList()
{
	this->base = new(nothrow) SqList_ElemType[LIST_INIT_SIZE];
	if (!this->base)
		exit(LOVERFLOW);
	this->length = 0;
	this->listsize = LIST_INIT_SIZE;
}


/**
 * @brief 顺序表的销毁
 * @tparam SqList_ElemType 顺序表元素
*/
template <class SqList_ElemType>
SqList<SqList_ElemType>::~SqList()
{
	if (this->base)
		delete[] this->base;
	this->base = NULL;
	this->length = 0;
	this->listsize = 0;

}


/**
 * @brief 重载等于号 目的是在复制线性表时不仅做浅拷贝 防止反复delete
 * @tparam SqList_ElemType 顺序表元素
 * @param that 赋值的另一个顺序表
 * @return 赋值后结果
*/
template <class SqList_ElemType>
const SqList<SqList_ElemType>& SqList<SqList_ElemType>::SqList::operator=(const SqList<SqList_ElemType>& that)
{
	length = that.length;
	listsize = that.listsize;
	base = new(nothrow) SqList_ElemType[listsize];
	if (!base)
		exit(LOVERFLOW);
	memcpy(base, that.base, listsize * sizeof(SqList_ElemType));
	return *this;
}


/**
 * @brief 求顺序表表长
 * @tparam SqList_ElemType 顺序表元素
 * @return 表长
*/
template <class SqList_ElemType>
int SqList<SqList_ElemType>::ListLength()
{
	return this->length;
}


/**
 * @brief 在顺序表位置i处插入元素
 * @tparam SqList_ElemType 顺序表元素
 * @param i 插入位置i
 * @param e 欲插入的元素
 * @return 插入状态
*/
template <class SqList_ElemType>
Status SqList<SqList_ElemType>::ListInsert(int i, SqList_ElemType e)
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


/**
 * @brief 取出顺序表位置i的元素
 * @tparam SqList_ElemType 顺序表元素
 * @param i 元素位置i
 * @param e 取出的元素
 * @return 取出状态
*/
template <class SqList_ElemType>
Status SqList<SqList_ElemType>::GetElem(int i, SqList_ElemType& e)
{
	if (i < 1 || i > this->length)
		return ERROR;
	e = this->base[i - 1];
	return OK;
}

/**
 * @brief 查找元素是否在顺序表中
 * @tparam SqList_ElemType 顺序表元素
 * @param e 查找的元素
 * @return 是否在表中
*/
template <class SqList_ElemType>
bool SqList<SqList_ElemType>::IsInList(const SqList_ElemType& e)
{
	for (int i = 0; i < length; i++) {
		if (base[i] == e)
			return true;
	}
	return false;
}