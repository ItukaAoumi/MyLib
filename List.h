#ifndef LIST_H_INCLUDED
#define LIST_H_INCLUDED
#pragma once

/*Single Dimension List
Can be used to store a sequence of data.
This is an example that uses double(64bit floating-point number) type,and you can change it in other situations.
Value 0 will not be stored to reduce the space occupation.*/

//data structures
typedef struct ListItem_1D
{
	double dat;//This is the data area.Change it in different situations.
	unsigned int index;
	struct ListItem_1D * next;
}LI1D;

static const unsigned int LI1Dsize=sizeof(struct ListItem_1D);

typedef struct List_1D
{
	struct ListItem_1D * FirstItem;
	unsigned int Length;
}List1D;

//functions
void List_1D_Init(struct List_1D * list);//Initializing a list(double type).Use once at first.
unsigned char List_1D_IExt(struct List_1D * list,unsigned int index);//Check the item is exist or not.
unsigned char List_1D_Add(struct List_1D * list,unsigned int index,double dat);//Add an item to the head.Return 1 if succeed,or return 0 if failed.Change the data type if it is not double type.
unsigned char List_1D_Edit(struct List_1D * list,unsigned int index,double dat);//Edit data of an item.Return 1 if succeed.
void List_1D_Del(struct List_1D * list,unsigned int index);//Delete an item by its index.
void List_1D_Clr(struct List_1D * list);//Clear the list.Use once at last.
LI1D * List_1D_Seek(struct List_1D * list,unsigned int index);//Seeking the address of an item by its index.
double List_1D_GetDat(struct List_1D * list,unsigned int index);//Get data by index.



/*Stack
First in and last out.
This is an example that uses double(64bit floating-point number) type,and you can change it in other situations.*/

//data structures
typedef struct StackItem
{
	double dat;//This is the data area.Change it in different situations.
	struct StackItem * next;
}SItem;

static const unsigned int SIsize=sizeof(struct StackItem);

typedef struct Stack
{
	struct StackItem * Top;
	unsigned int Length;
}Stack;

//functions
void Stk_Init(struct Stack * stk);//Initializing a stack(double type).Use once at first.
unsigned char Stk_Push(struct Stack * stk,double dat);//Add an item to the stack.Return 1 if succeed.
double Stk_Peek(struct Stack * stk);//Peek the top of the stack,but do not remove.
double Stk_Pop(struct Stack * stk);//Remove an item from the stack and return.






/*Queue
First in and first out.
This is an example that uses double(64bit floating-point number) type,and you can change it in other situations.*/

//data structures
typedef struct QueueItem
{
	double dat;//This is the data area.Change it in different situations.
	struct QueueItem * next;
}QItem;

static const unsigned int QIsize=sizeof(struct QueueItem);

typedef struct Queue
{
	struct QueueItem * Head;
	struct QueueItem * Tail;
	unsigned int Length;
}Queue;

//functions
void Que_Init(struct Queue * que);//Initializing a queue(double type).Use once at first.
unsigned char Que_Push(struct Queue * que,double dat);//Add an item to the queue.Return 1 if succeed.
double Que_PeekHead(struct Queue * que);//Peek the head of the queue,but do not remove.
double Que_PeekTail(struct Queue * que);//Peek the tail of the queue,but do not remove.
double Que_Pop(struct Queue * que);//Remove an item from the queue and return.


#endif // LIST_H_INCLUDED
