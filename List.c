#include <stdlib.h>
#include <D:\MyLib\List.h>

//Functions of List_1D

//Initializing a list(double type).Use once at first.
void List_1D_Init(struct List_1D * list)
{
	list->FirstItem=0;
	list->Length=0;
	return;
}

//Check the item is exist or not.
unsigned char List_1D_IExt(struct List_1D * list,unsigned int index)
{
	if (list==0) return 1;
	LI1D * ptr;
	for (ptr=list->FirstItem;ptr!=0;ptr=ptr->next)
		if (ptr->index==index)
			return 1;
	return 0;
}

//Add data to the head.Return 1 if succeed,or return 0 if failed.Change the data type if it is not double type.
unsigned char List_1D_Add(struct List_1D * list,unsigned int index,double dat)
{
	if (list==0) return 0;
	if (List_1D_IExt(list,index))//item exist
	{
		if (dat!=0)//not 0,edit the data
			if (List_1D_Edit(list,index,dat))
				return 1;
			else
				return 0;
		else//dat==0,delete the item
			List_1D_Del(list,index);
		return 1;
	}
	else//index not exist
	{
		struct ListItem_1D * nitem=(struct List_1D*)malloc(LI1Dsize);
		if (nitem==0) return 0;
		nitem->dat=dat;
		nitem->index=index;
		nitem->next=list->FirstItem;
		list->FirstItem=nitem;
		list->Length++;
		return 1;
	}
}

//Edit data of a item.Return 1 if succeed.
unsigned char List_1D_Edit(struct List_1D * list,unsigned int index,double dat)
{
	if (list==0) return 0;
	LI1D * ptr;
	for (ptr=list->FirstItem;ptr!=0;ptr=ptr->next)
		if (ptr->index==index)
		{
			ptr->dat=dat;
			return 1;
		}
	return 0;
}

//Delete a selected data.
void List_1D_Del(struct List_1D * list,unsigned int index)
{
	if (list==0) return;
	LI1D * ptr=list->FirstItem;
	if (ptr==0) return;
	if (ptr->index!=index)//is not the first
	{
		LI1D * last;//the item behind ptr
		for (last=ptr,ptr=ptr->next;ptr!=0;last=ptr,ptr=ptr->next)//go through
		{
			if (ptr->index==index)//find the item
			{
				last->next=ptr->next;
				free(ptr);
				list->Length--;
				return;
			}
		}
	}
	else//delete the first item
	{
		list->FirstItem=ptr->next;
		free(ptr);
		list->Length--;
	}
	return;
}

//Clear all data.
void List_1D_Clr(struct List_1D * list)
{
	if (list==0) return;
	LI1D * ptr;
	for (ptr=list->FirstItem;ptr!=0;ptr=list->FirstItem)
	{
		list->FirstItem=ptr->next;
		free(ptr);
	}
	list->Length=0;
	return;
}

//Seek the address.
LI1D * List_1D_Seek(struct List_1D * list,unsigned int index)
{
	if (list==0) return 0;
	LI1D * ptr;
	for (ptr=list->FirstItem;ptr!=0;ptr=ptr->next)
		if (ptr->index==index)
			return ptr;
	return 0;
}

//Get data by index.
double List_1D_Get(struct List_1D * list,unsigned int index)
{
	if (list==0) return 0;
	LI1D * pos;
	for (pos=list->FirstItem;pos!=0;pos=pos->next)
		if (pos->index==index)
			return pos->dat;
	return 0;
}

//Functions about Stack
//Initializing a stack.
void InitStk(pStack * stk)
{
	stk->top.ptr=0;
	stk->top.psize=0;
	stk->top.next=0;
	return;
}

void PushStk(pStack * stk,void * ptr,unsigned char psize)
{
	StkItem * tmp=malloc(SIsize);
	tmp->ptr=ptr;
	tmp->psize=psize;
	tmp->next=stk->top.next;
	stk->top.next=tmp;
	return;
}

void * PopStk(pStack * stk,unsigned char * psize)
{
	StkItem * tmp=stk->top.next;void * r=0;
	if (tmp!=0)
	{
		r=tmp->ptr;
		*psize=tmp->psize;
		stk->top.next=tmp->next;
		free(tmp);
	}
	return r;
}

void * PeekStk(pStack * stk,unsigned char * psize)
{
	if (stk->top.next!=0)
	{
		*psize=stk->top.next->psize;
		return stk->top.next->ptr;
	}
	else
	{
		*psize=0;
		return 0;
	}
}

unsigned int StkLen(pStack * stk)
{
	unsigned int i=0;
	StkItem * tmp=stk->top.next;
	while (tmp!=0)
	{
		i++;
		tmp=tmp->next;
	}
	return i;
}

//queue
void InitQue(pQueue * que)
{
	que->head.ptr=que->tail.ptr=0;
	que->head.psize=que->tail.psize=0;
	que->head.next=&(que->tail);
	que->head.last=que->tail.next=0;
	que->tail.last=&(que->head);
	return;
}

void PushQue(pQueue * que,void * ptr,unsigned char psize)
{
	QItem * tmp=malloc(QIsize);
	if (tmp!=0)
	{
		tmp->ptr=ptr;
		tmp->psize=psize;
		tmp->next=que->head.next;
		tmp->last=&(que->head);
		que->head.next->last=tmp;
		que->head.next=tmp;
	}
	return;
}

void * PopQue(pQueue * que,unsigned char * psize)
{
	QItem * tmp=que->tail.last;void * r=0;
	if (tmp!=&(que->head))
	{
		r=tmp->ptr;
		*psize=tmp->psize;
		tmp->last->next=&(que->tail);
		que->tail.last=tmp->last;
		free(tmp);
	}
	return r;
}

void * PeekQue(pQueue * que,unsigned char * psize)
{
	if (que->head.next!=&(que->tail))
	{
		*psize=que->tail.last->psize;
		return que->tail.last->ptr;
	}
	else
	{
		*psize=0;
		return 0;
	}
}

unsigned int QueLen(pQueue * que)
{
	unsigned int i=0;
	QItem * tmp=que->head.next;
	while (tmp!=&(que->tail))
	{
		i++;
		tmp=tmp->next;
	}
	return i;

}
