/*
This is a library of list type data structures,including single-dimension list,double-dimension list,stack and queue.
Have Fun _( :<L )_ !
CN:Ituka Aoumi,Qiyi Ji,Dragon_t;
Group:Code A Live;
Git:
12,Oct,2018.Build:0.1.1;
*/

//Do not include me twice!
#ifndef LIST_H_INCLUDED
#define LIST_H_INCLUDED

//Can be used in cpp
#ifdef __cplusplus
extern "C" {
#endif // __cplusplus


/*
Single-Dimension List
Can be used to store a sequence of data.
*/

//data structures:

typedef struct List_1D_Item
{
	unsigned int Index;//A unique number for every data item.
	void * Data;//data ptr
	unsigned char DataSize;//the size of data
	char * TypeName;//the name of data type
	struct List_1D_Item * next;
}L1DI_t, * L1DI_p;

typedef struct List_1D
{
	struct List_1D_Item * First;//the first item of the list
	unsigned int Length;
}List1D_t, * List1D_p;

static const unsigned char L1DIsize=sizeof(struct List_1D_Item);
static const unsigned char List1Dsize=sizeof(struct List_1D);

//functions:

/*
Create a new single-dimension list like this : List1D_t <name> = { 0 , 0 }
or List1D_p <name> = ( List1D_p ) malloc( List1Dsize ) ; List1D_Init( name )
You can use the macro definition List1D_New or List1D_New_p(name) .
*/
#define List1D_New { 0 , 0 }
#define List1D_New_p(name) ( List1D_p ) malloc( List1Dsize ) ; List1D_Init( name )

//Initializing a list.Use once at first.Return 1 if succeed.
char List1D_Init(List1D_p list);

//Add an item to the head.Return 1 if succeed.
char List1D_Add(List1D_p list,unsigned int index,void * data,unsigned char datasize,char * type_name);

//Edit data of an item.Return 1 if succeed.
char List1D_Edit(L1DI_p item,void * data,unsigned char datasize,char * type_name);

//Delete an item.
char List1D_Del(List1D_p list,L1DI_p item);

//Clear the list.Use once at last.
char List1D_Clr(List1D_p list);

//Seeking the address of an item by its index.
L1DI_p List1D_Seek(List1D_p list,unsigned int index);

//Get data by ptr
void * List1D_GetData_p(L1DI_p item,unsigned char * datasize,char * type_name);

//Get data by index.
void * List1D_GetData_i(List1D_p list,unsigned int index,unsigned char * datasize,char * type_name);


//to be continued


/*
Stack
A kind of First-In-Last-Out data structure.
*/

//data structures:

typedef struct StackItem
{
	void * Data;//data ptr
	unsigned char DataSize;//the size of data
	char * TypeName;//the name of data type
	struct StackItem * next;
}SI_t, * SI_p;

typedef struct Stack
{
	struct StackItem * Top;
	unsigned int Length;
}Stack_t, * Stack_p;

static const unsigned char SIsize=sizeof(struct StackItem);//the size of a stack item
static const unsigned char Stksize=sizeof(struct Stack);//the size of a stack

//functions:

/*
Create a new stack like this : Stack_t <name> = { 0 , 0 }
or Stack_p <name> = ( Stack_p ) malloc( Stksize ) ; Stk_Init( name )
You can use the macro definition Stk_New or Stk_New_p(name) .
*/
#define Stk_New { 0 , 0 }
#define Stk_New_p(name) ( Stack_p ) malloc( Stksize ) ; Stk_Init( name )

//Initializing a stack(double type).Use once at first.
char Stk_Init(Stack_p stk);

//Add an item to the stack.Return 1 if succeed.
char Stk_Push(Stack_p stk,void * data,unsigned char datasize,char * type_name);

//Peek the top of the stack,but do not remove.
void * Stk_PeekData(Stack_p stk);

unsigned char Stk_PeekSize(Stack_p stk);

char * Stk_PeekTypeName(Stack_p stk);

//Remove an item from the stack and return.
void * Stk_Pop(Stack_p stk,unsigned char * datasize,char * type_name);

//Clear the stack.
char Stk_Clr(Stack_p stk);


//to be continued


/*
Queue
A kind of First-In-First-Out data structure.
*/

//data structures:

typedef struct QueueItem
{
	void * Data;//data ptr
	unsigned char DataSize;//the size of data
	char * TypeName;//the name of data type
	struct QueueItem * next;
}QI_t, * QI_p;

typedef struct Queue
{
	struct QueueItem * Head;
	struct QueueItem * Tail;
	unsigned int Length;
}Queue_t, * Queue_p;

static const unsigned int QIsize=sizeof(struct QueueItem);//the size of a queue item
static const unsigned char Quesize=sizeof(struct Queue);//the size of a queue

//functions:

/*
Create a new queue like this : Queue_t <name> = { 0 , 0 , 0 }
or Queue_p <name> = ( Queue_p ) malloc( Quesize ) ; Que_Init( name )
You can use the macro definition Que_New or Que_New_p(name) .
*/
#define Que_New { 0 , 0 , 0 }
#define Que_New_p(name) ( Queue_p ) malloc( Quesize ) ; Que_Init( name )

//Initializing a queue.Use once at first.Return 1 if succeed.
char Que_Init(struct Queue * que);

//Add an item to the queue.Return 1 if succeed.
char Que_Push(Queue_p que,void * data,unsigned char datasize,char * type_name);

//Peek the head of the queue,but do not remove.
void * Que_PeekHeadData(Queue_p que);

unsigned char Que_PeekHeadSize(Queue_p que);

char * Que_PeekHeadTypeName(Queue_p que);

//Peek the tail of the queue,but do not remove.
void * Que_PeekTailData(Queue_p que);

unsigned char Que_PeekTailSize(Queue_p que);

char * Que_PeekTailTypeName(Queue_p que);

//Remove an item from the queue and return.
void * Que_Pop(Queue_p que,unsigned char * datasize,char * type_name);

//Clear the queue.
char Que_Clr(Queue_p que);


//to be continued

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#endif // LIST_H_INCLUDED

//Thanks for reading.Love you.
