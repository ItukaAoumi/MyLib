#ifndef LIST_H_INCLUDED
#define LIST_H_INCLUDED
#pragma once

/*Single Dimension List
Can be used to store a sequence of data.*/
//data structures
typedef struct ListItem_1D
{
	double dat;//This is the data area of each list-item.Change it to make it suitable in different situations.
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
void List_1D_Init(struct List_1D * list);
unsigned char List_1D_IExt(struct List_1D * list,unsigned int index);
unsigned char List_1D_Add(struct List_1D * list,unsigned int index,double dat);
unsigned char List_1D_Edit(struct List_1D * list,unsigned int index,double dat);
void List_1D_Del(struct List_1D * list,unsigned int index);
void List_1D_Clr(struct List_1D * list);
LI1D * List_1D_Seek(struct List_1D * list,unsigned int index);
double List_1D_Get(struct List_1D * list,unsigned int index);



/*stack
First in and last out.*/
typedef struct StkItem
{
	void * ptr;unsigned char psize;struct StkItem * next;
}StkItem;
static const unsigned int SIsize=sizeof(struct StkItem);

typedef struct pStack
{
	struct StkItem top;
}pStack;

//queue
typedef struct QItem
{
	void * ptr;unsigned char psize;struct QItem * last, * next;
}QItem;
static const unsigned int QIsize=sizeof(struct QItem);

typedef struct pQueue
{
	struct QItem head;struct QItem tail;
}pQueue;

#endif // LIST_H_INCLUDED
