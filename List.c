/*
This is a library of list type data structures,including single-dimension list,double-dimension list,stack and queue.
Have Fun _( :<L )_ !
CN:Ituka Aoumi,Qiyi Ji,Dragon_t;
Group:Code A Live;
Git:
12,Oct,2018.Build:0.1.1;
*/

#include <stdlib.h>//Necessary.Please do not change.
#include <string.h>
#include "List.h"//List.h must be included,but please change the path if it is not the same as mine.

//Can be used in cpp
#ifdef __cplusplus
extern "C" {
#endif // __cplusplus


/*
Single-Dimension List
Can be used to store a sequence of data.
*/

//Functions of List1D

/*
Create a new single-dimension list like this : List1D_t <name> = { 0 , 0 }
or List1D_p <name> = ( List1D_p ) malloc( List1Dsize ) ; List1D_Init( name )
You can use the macro definition List1D_New or List1D_New_p(name) .
*/

//Initializing a list.Use once at first.Return 1 if succeed.
char List1D_Init(List1D_p list)
{
	if (!list) return 0;
	list->First=0;
	list->Length=0;
	return 1;
}

//Add an item to the head.Return 1 if succeed.
char List1D_Add(List1D_p list,unsigned int index,void * data,unsigned char datasize,char * type_name)
{
	if (!(list&&data&&datasize)) return 0;
	L1DI_p item=List1D_Seek(list,index);
	if (item)//item exist
		if (List1D_Edit(item,data,datasize,type_name))
			return 1;
		else
			return 0;
	else//index not exist
	{
		item=(L1DI_p)malloc(L1DIsize);
		if (!item) return 0;
		item->Index=index;
		item->Data=data;
		item->DataSize=datasize;
		item->TypeName=(char *)malloc(strlen(type_name)+1);
		if (item->TypeName) strcpy(item->TypeName,type_name);
		item->next=list->First;
		list->First=item;
		list->Length++;
		return 1;
	}
}

//Edit data of an item.Return 1 if succeed.
char List1D_Edit(L1DI_p item,void * data,unsigned char datasize,char * type_name)
{
	if (!(item&&data&&datasize)) return 0;
	item->Data=data;
	item->DataSize=datasize;
	if (* type_name) strcpy(item->TypeName,type_name);
	return 1;
}

//Delete an item.
char List1D_Del(List1D_p list,L1DI_p item)
{
	if (!(list&&item)) return 0;
	if (!list->First) return 0;
	if (list->First!=item)//is not the first
	{
		L1DI_p last;//behind item
		for (last=list->First;last;last=last->next)//scan the list
		{
			if (last->next==item)//find the item
			{
				last->next=item->next;
				free(item->TypeName);
				free(item);
				list->Length--;
				return 1;
			}
		}
		return 0;
	}
	else//delete the first item
	{
		list->First=item->next;
		free(item->TypeName);
		free(item);
		list->Length--;
		return 1;
	}
}

//Clear the list.Use once at last.
char List1D_Clr(List1D_p list)
{
	if (!list) return 0;
	L1DI_p ptr;
	while (list->First)
	{
		ptr=list->First;
		list->First=list->First->next;
		free(ptr->TypeName);
		free(ptr);
	}
	list->Length=0;
	return 1;
}

//Seeking the address of an item by its index.
L1DI_p List1D_Seek(List1D_p list,unsigned int index)
{
	if (!list) return 0;
	for (L1DI_p ptr=list->First;ptr;ptr=ptr->next)
		if (ptr->Index==index)
			return ptr;
	return 0;
}

//Get data by ptr
void * List1D_GetData_p(L1DI_p item,unsigned char * datasize,char * type_name)
{
	if (!(item&&datasize)) return 0;
	* datasize=item->DataSize;
	if (type_name) strcpy(type_name,item->TypeName);
	return item->Data;
}

//Get data by index.
void * List1D_GetData_i(List1D_p list,unsigned int index,unsigned char * datasize,char * type_name)
{
	if (!(list&&datasize)) return 0;
	return List1D_GetData_p(List1D_Seek(list,index),datasize,type_name);
}


//to be continued


/*
Stack
A kind of First-In-Last Out data structure.
*/

//Functions of Stack

/*
Create a new stack like this : Stack_t <name> = { 0 , 0 }
or Stack_p <name> = ( Stack_p ) malloc( Stksize ) ; Stk_Init(name)
You can use the macro definition Stk_New or Stk_New_p(name) .
*/

//Initializing a stack(double type).Use once at first.Return 1 if succeed.
char Stk_Init(Stack_p stk)
{
	if (!stk) return 0;
	stk->Top=0;
	stk->Length=0;
	return 1;
}

//Add an item to the stack.Return 1 if succeed.
char Stk_Push(Stack_p stk,void * data,unsigned char datasize,char * type_name)
{
	if (!(stk&&data&&datasize)) return 0;
	SI_p nitem=(SI_p)malloc(SIsize);
	if (!nitem) return 0;
	nitem->Data=data;
	nitem->DataSize=datasize;
	nitem->TypeName=(char *)malloc(strlen(type_name)+1);
	if (nitem->TypeName) strcpy(nitem->TypeName,type_name);
	nitem->next=stk->Top;
	stk->Top=nitem;
	stk->Length++;
	return 1;
}

//Peek the top of the stack,but do not remove.
void * Stk_PeekData(Stack_p stk)
{
	if (!stk) return 0;
	if (!stk->Top) return 0;
	return stk->Top->Data;
}

unsigned char Stk_PeekSize(Stack_p stk)
{
	if (!stk) return 0;
	if (!stk->Top) return 0;
	return stk->Top->DataSize;
}

char * Stk_PeekTypeName(Stack_p stk)
{
	if (!stk) return 0;
	if (!stk->Top) return 0;
	return stk->Top->TypeName;
}

//Remove an item from the stack and return.
void * Stk_Pop(Stack_p stk,unsigned char * datasize,char * type_name)
{
	if (!(stk&&datasize)) return 0;
	if (!stk->Top) return 0;
	//record the item on the top
	SI_p ptr=stk->Top;
	void * data=stk->Top->Data;
	* datasize=stk->Top->DataSize;
	if (type_name) strcpy(type_name,stk->Top->TypeName);
	//move to the next item and delete
	stk->Top=stk->Top->next;
	free(ptr->TypeName);
	free(ptr);
	stk->Length--;
	return data;
}

//Clear the stack.
char Stk_Clr(Stack_p stk)
{
	if (!stk) return 0;
	SI_p ptr=0;
	while (stk->Top)
	{
		ptr=stk->Top;
		stk->Top=stk->Top->next;
		free(ptr->TypeName);
		free(ptr);
	}
	stk->Length=0;
	return 1;
}


//to be continued


//Functions of Queue

/*
Create a new queue like this : Queue_t <name> = { 0 , 0 , 0 }
or Queue_p <name> = ( Queue_p ) malloc( Quesize )
You can use the macro definition Que_New or Que_New_p(name) .
*/

//Initializing a queue.Use once at first.Return 1 if succeed.
char Que_Init(Queue_p que)
{
	if (!que) return 0;
	que->Head=que->Tail=0;
	que->Length=0;
	return 1;
}

//Add an item to the queue.Return 1 if succeed.
char Que_Push(Queue_p que,void * data,unsigned char datasize,char * type_name)
{
	if (!(que&&data&&datasize)) return 0;
	QI_p nitem=(QI_p)malloc(QIsize);
	if (!nitem) return 0;
	nitem->Data=data;
	nitem->DataSize=datasize;
	nitem->TypeName=(char *)malloc(strlen(type_name));
	if (nitem->TypeName) strcpy(nitem->TypeName,type_name);
	nitem->next=0;
	if (que->Tail)//not empty
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
void * Que_PeekHeadData(Queue_p que)
{
	if (!que) return 0;
	if (!que->Head) return 0;
	return que->Head->Data;
}

unsigned char Que_PeekHeadSize(Queue_p que)
{
	if (!que) return 0;
	if (!que->Head) return 0;
	return que->Head->DataSize;
}

char * Que_PeekHeadTypeName(Queue_p que)
{
	if (!que) return 0;
	if (!que->Head) return 0;
	return que->Head->TypeName;
}

//Peek the tail of the queue,but do not remove.
void * Que_PeekTailData(Queue_p que)
{
	if (!que) return 0;
	if (!que->Tail) return 0;
	return que->Tail->Data;
}

unsigned char Que_PeekTailSize(Queue_p que)
{
	if (!que) return 0;
	if (!que->Tail) return 0;
	return que->Tail->DataSize;
}

char * Que_PeekTailTypeName(Queue_p que)
{
	if (!que) return 0;
	if (!que->Tail) return 0;
	return que->Tail->TypeName;
}

//Remove an item from the queue and return.
void * Que_Pop(Queue_p que,unsigned char * datasize,char * type_name)
{
	if (!(que&&datasize)) return 0;
	if (!que->Head) return 0;
	//record the head item
	QI_p ptr=que->Head;
	void * data=que->Head->Data;
	* datasize=que->Head->DataSize;
	if (type_name) strcpy(type_name,que->Head->TypeName);
	//move to next item and delete
	que->Head=que->Head->next;
	free(ptr->TypeName);
	free(ptr);
	que->Length--;
	return data;
}

//Clear the queue.
char Que_Clr(Queue_p que)
{
	if (!que) return 0;
	QI_p ptr=0;
	while (que->Head)
	{
		ptr=que->Head;
		que->Head=que->Head->next;
		free(ptr->TypeName);
		free(ptr);
	}
	que->Tail=0;
	que->Length=0;
	return 1;
}


//to be continued

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

//Thanks for reading.Love you.[bi xin]
