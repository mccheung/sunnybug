#include "list.h"

void CListHead::remove()  //���б���ȥ��������ǰ��㣩
{
    //if(next!=this)
	{
	    prev->next = next;
	    next->prev = prev;
	    prev = next = this;
	}
}

CListHead *CListHead::removeHead(bool bHead)  //���б���ȥ������ǰ��㣩��һ��
{
	CListHead *t =next;
	if(next!=this||bHead)
	{
	    next->remove();
	}
	else return 0;
	return t;
}

void CListHead::add(CListHead *item)   //����thisǰ
{
	item->prev = prev;
	item->next = this;
	prev->next = item;
	prev = item;
}

void CListHead::addHead(CListHead *item)  //����this��
{
	item->prev = this;
	item->next = next;
	next->prev = item;
	next = item;
}
