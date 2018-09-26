/*
This is made by Ituka Aoumi,from Code A Live
Have fun!hhh2333666
*/
#include <stdlib.h>//Necessary.Please do not change.
#include "List.h"//List.h must be included,but please change the path if it is not the same as mine.

//Functions of List_1D

//Initializing a list(double type).Use once at first.
void List_1D_Init(struct List_1D * list)
{
	if (list==0) return;
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

//Add an item to the head.Return 1 if succeed,or return 0 if failed.Change the data type if it is not double type.
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
		if (dat==0) return 1;//dat==0,do not add
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

//Edit data of an item.Return 1 if succeed.
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

//Delete an item by its index.
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

//Clear the list.Use once at last.
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

//Seeking the address of an item by its index.
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
double List_1D_GetDat(struct List_1D * list,unsigned int index)
{
	if (list==0) return 0;
	LI1D * pos;
	for (pos=list->FirstItem;pos!=0;pos=pos->next)
		if (pos->index==index)
			return pos->dat;
	return 0;
}




//Functions of Stack

//Initializing a stack(double type).Use once at first.
void Stk_Init(struct Stack * stk)
{
	if (stk==0) return;
	stk->Top=0;
	stk->Length=0;
	return;
}

//Add an item to the stack.Return 1 if succeed.
unsigned char Stk_Push(struct Stack * stk,double dat)
{
	if (stk==0) return 0;
	SItem * nitem=malloc(SIsize);
	if (nitem==0) return 0;
	nitem->dat=dat;
	nitem->next=stk->Top;
	stk->Top=nitem;
	stk->Length++;
	return 1;
}

//Peek the top of the stack,but do not remove.
double Stk_Peek(struct Stack * stk)
{
	if (stk==0||stk->Top==0) return 0;
	return stk->Top->dat;
}

//Remove an item from the stack and return.
double Stk_Pop(struct Stack * stk)
{
	if (stk==0||stk->Top==0) return 0;
	SItem * ptr=stk->Top;//record the item on the top
	double dat=stk->Top->dat;
	stk->Top=stk->Top->next;//move to the next item
	free(ptr);
	stk->Length--;
	return dat;
}



//Functions of Queue

//Initializing a queue(double type).Use once at first.
void Que_Init(struct Queue * que)
{
	if (que==0) return;
	que->Head=que->Tail=0;
	que->Length=0;
	return;
}

//Add an item to the queue.Return 1 if succeed.
unsigned char Que_Push(struct Queue * que,double dat)
{
	if (que==0) return 0;
	QItem * nitem=malloc(QIsize);
	if (nitem==0) return 0;
	nitem->dat=dat;
	nitem->next=0;
	if (que->Tail!=0)//not empty
	{
		que->Tail->next=nitem;
		que->Tail=nitem;
	}
	else//empty queue
		que->Head=que->Tail=nitem;
	que->Length++;
	return 1;
}

//Peek the head of the queue,but do not remove.
double Que_PeekHead(struct Queue * que)
{
	if (que==0||que->Head==0) return 0;
	return que->Head->dat;
}

//Peek the tail of the queue,but do not remove.
double Que_PeekTail(struct Queue * que)
{
	if (que==0||que->Tail==0) return 0;
	return que->Tail->dat;
}

//Remove an item from the queue and return.
double Que_Pop(struct Queue * que)
{
	if (que==0||que->Head==0) return 0;
	QItem * ptr=que->Head;//record the head item
	double dat=que->Head->dat;
	que->Head=que->Head->next;//move to next item
	free(ptr);
	que->Length--;
	return dat;
}



//Thanks for reading.Love you.[bi xin]
