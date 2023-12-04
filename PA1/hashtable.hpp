#include <iostream>
#include "./sqlist.hpp"
#include "./linklist.hpp"
#define LOVERFLOW	-1
#define ERROR		-2
#define OK			0
#define HASHTABLE_LEN 19997

using namespace std;

template <class Hash_ElemType>
class Hashtable {
private:
	LinkList<Hash_ElemType>* base;
public:
	//构造函数 哈希表的建立
	Hashtable();
	//析构函数 哈希表的销毁
	~Hashtable();
	//在哈希表中插入新元素
	Status TableInsert(const Hash_ElemType& e, int(*GetIndex)(const Hash_ElemType& e));
	//在哈希表中查找已有元素
	Status TableSearch(Hash_ElemType& e, int(*GetIndex)(const Hash_ElemType& e));
	//在哈希表中删除已有元素
	Status TableDelete(Hash_ElemType& e, int(*GetIndex)(const Hash_ElemType& e));
	//在哈希表中取元素的位置(以修改其中内容)
	Status LocateElem(const Hash_ElemType& e, Hash_ElemType*& ep, int(*GetIndex)(const Hash_ElemType& e));
	//查找哈希表中是否有该元素
	bool IsInTable(const Hash_ElemType&e, int(*GetIndex)(const Hash_ElemType& e));
};

/**
 * @brief 空哈希表的建立
 * @tparam Hash_ElemType 哈希表的元素类型
 * @param len 哈希表的长度
*/
template <class Hash_ElemType>
Hashtable<Hash_ElemType>::Hashtable()
{
	base = new(nothrow) LinkList<Hash_ElemType>[HASHTABLE_LEN];
	if (!base)
		exit(LOVERFLOW);
}


/**
 * @brief 哈希表的销毁
 * @tparam Hash_ElemType 哈希表的元素类型
*/
template <class Hash_ElemType>
Hashtable<Hash_ElemType>::~Hashtable()
{
	delete[] base;
}


/**
 * @brief 在哈希表中插入新元素
 * @tparam Hash_ElemType 哈希表的元素类型
 * @param e 当前插入的元素
 * @param GetIndex 取得key值下标的函数
 * @return 是否成功插入
*/
template <class Hash_ElemType>
Status Hashtable<Hash_ElemType>::TableInsert(const Hash_ElemType& e, int(*GetIndex)(const Hash_ElemType& e))
{
	int ret = GetIndex(e);
	if (ret >= HASHTABLE_LEN || ret < 0)
		return ERROR;
	return base[ret].ListInsert(1, e);
}


/**
 * @brief 在哈希表中查找已有元素，返回地址以修改
 * @tparam Hash_ElemType 哈希表的元素类型
 * @param e 当前查找的元素
 * @param ep 找到的元素地址
 * @param GetIndex 取得key值下标的函数
 * @return 是否成功查找
*/
template <class Hash_ElemType>
Status Hashtable<Hash_ElemType>::LocateElem(const Hash_ElemType& e, Hash_ElemType*& ep, int(*GetIndex)(const Hash_ElemType& e))
{
	int ret = GetIndex(e);
	if (ret >= HASHTABLE_LEN || ret < 0)
		return ERROR;
	
	return base[ret].LocatePosition(e, ep);
}


/**
 * @brief 在哈希表中查找已有元素
 * @tparam Hash_ElemType 哈希表的元素类型
 * @param e 当前查找的元素
 * @param GetIndex 取得key值下标的函数
 * @return 是否成功查找
*/
template <class Hash_ElemType>
Status Hashtable<Hash_ElemType>::TableSearch(Hash_ElemType& e, int(*GetIndex)(const Hash_ElemType& e))
{
	int ret = GetIndex(e);
	if (ret >= HASHTABLE_LEN || ret < 0)
		return ERROR;

	return base[ret].SearchElem(e);
}


/**
 * @brief 在哈希表中删除已有元素
 * @tparam Hash_ElemType 哈希表的元素类型
 * @param e 准备删除的元素
 * @param GetIndex 取得key值下标的函数
 * @return 元素本身是否存在
*/
template <class Hash_ElemType>
Status Hashtable<Hash_ElemType>::TableDelete(Hash_ElemType& e, int(*GetIndex)(const Hash_ElemType& e))
{
	int ret = GetIndex(e);
	if (ret >= HASHTABLE_LEN || ret < 0)
		return ERROR;

	int index = base[ret].LocateElem(e);
	//表中不存在该元素
	if (!index)
		return ERROR;

	return base[ret].ListDelete(index, e);
}


/**
 * @brief 在哈希表中查找元素是否存在
 * @tparam Hash_ElemType 哈希表的元素类型
 * @param e 当前查找的元素
 * @param GetIndex 取得key值下标的函数
 * @return 是否存在
*/
template <class Hash_ElemType>
bool Hashtable<Hash_ElemType>::IsInTable(const Hash_ElemType& e, int(*GetIndex)(const Hash_ElemType& e))
{
	int ret = GetIndex(e);
	if (ret >= HASHTABLE_LEN || ret < 0)
		return false;

	int index = base[ret].LocateElem(e);
	return index;		//是否存在对应的链表中
}