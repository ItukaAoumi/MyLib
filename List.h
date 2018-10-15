/*
This is a library of liner data structures,including single-dimension list,double-dimension list,stack and queue.
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
	struct List_1D_Item * NextItem;
}L1DI_t, * L1DI_p;

typedef struct List_1D
{
	struct List_1D_Item * FirstItem;//the first item of the list
	unsigned int Length;
	unsigned int MaxIndex;
}List1D_t, * List1D_p;

static const unsigned char L1DIsize=sizeof(struct List_1D_Item);//the size of an item
static const unsigned char List1Dsize=sizeof(struct List_1D);//the size of a list

//functions:

/*
Create a new single-dimension list like this : List1D_t <name> = { 0 , 0 , 0 }
or List1D_p <name> = ( List1D_p ) malloc( List1Dsize ) ; List1D_Init( name )
You can use the macro definition List1D_New or List1D_New_p(name) .
*/
#define List1D_New { 0 , 0 , 0 }
#define List1D_New_p(name) ( List1D_p ) malloc( List1Dsize ) ; List1D_Init( name )

//Initializing a list.Use once at first.Return 1 if succeed.
char List1D_Init(List1D_p list);

//Seeking the address of an item by its index.
L1DI_p List1D_Seek(List1D_p list,unsigned int index);

//Add an item to the head.Return 1 if succeed.
L1DI_p List1D_Add(List1D_p list,unsigned int index);

//Edit data of an item.Return 1 if succeed.
char List1D_Edit(L1DI_p item,void * data,unsigned char datasize,char * type_name);

//Delete an item.
void * List1D_Del(List1D_p list,L1DI_p item);

//Clear the list.Use once at last.
char List1D_Clr(List1D_p list);

//Get data by ptr
void * List1D_GetData_p(L1DI_p item);

//Get data by index.
void * List1D_GetData_i(List1D_p list,unsigned int index);

//Get data size by ptr.
unsigned char List1D_GetSize_p(L1DI_p item);

//Get type name by ptr.
char * List1D_GetTypeName_p(L1DI_p item);



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

static const unsigned char QIsize=sizeof(struct QueueItem);//the size of a queue item
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


/*
Double-Dimension List
Can be used to store a matrix.
*/

//data structures:

typedef struct List_2D_ColItem
{
	unsigned int Col;//column number
	void * Data;//data ptr
	unsigned char DataSize;//size of data ptr
	char * TypeName;//name of data type
	struct List_2D_ColItem * NextCol;
}L2DCI_t, * L2DCI_p;

typedef struct List_2D_RowItem
{
	unsigned int Row;//row number
	struct List_2D_ColItem * FirstCol;
	unsigned int ColLength;//number of col items
	struct List_2D_RowItem * NextRow;
}L2DRI_t, * L2DRI_p;

typedef struct List_2D
{
	struct List_2D_RowItem * FirstRow;
	unsigned int RowLength;//number of row items
	unsigned int MaxRow;//the max row number
	unsigned int MaxCol;//the max col number
}List2D_t, * List2D_p;

static const unsigned char L2DCIsize=sizeof(struct List_2D_ColItem);//the size of a col item
static const unsigned char L2DRIsize=sizeof(struct List_2D_RowItem);//the size of a row item
static const unsigned char List2Dsize=sizeof(struct List_2D);//the size of a 2D list

//functions:

/*
Create a new double-dimension list like this : List2D_t <name> = { 0 , 0 , 0 , 0 }
or List2D_p <name> = ( List2D_p ) malloc( List2Dsize ) ; List2D_Init( name )
You can use the macro definition List2D_New or List2D_New_p(name) .
*/
#define List2D_New { 0 , 0 , 0 , 0 }
#define List2D_New_p(name) ( List2D_p ) malloc( List2Dsize ) ; List2D_Init( name )

//Initialize a 2D list.Use once at first.Return 1 if succeed.
char List2D_Init(List2D_p list);

//Seek a row item
L2DRI_p List2D_SeekRow(List2D_p list,unsigned int rownum);

//Seek a col item
L2DCI_p List2D_SeekCol(L2DRI_p rowitem,unsigned int colnum);

//Seek an item by row and col number
L2DCI_p List2D_SeekItem(List2D_p list,unsigned int rownum,unsigned int colnum);

//Add a row item and return its ptr.
L2DRI_p List2D_AddRow(List2D_p list,unsigned int rownum);

//Add a col item and return its ptr.
L2DCI_p List2D_AddCol(L2DRI_p rowitem,unsigned int colnum);

//Edit an item.Return 1 if succeed.
char List2D_Edit(L2DCI_p item,void * data,unsigned char datasize,char * type_name);

//Delete a row item and all of its col items.
char List2D_DelRow(List2D_p list,L2DRI_p rowitem);

//Delete a col item.
void * List2D_DelCol(L2DRI_p rowitem,L2DCI_p colitem);

//Clear a row.
char List2D_ClrRow(L2DRI_p rowitem);

//Clear the 2D list.Use once at last.
char List2D_Clr(List2D_p list);

//Get data by ptr
void * List2D_GetData(L2DCI_p item);

//Get data size by ptr
unsigned char List2D_GetSize(L2DCI_p item);


//to be continued


#ifdef __cplusplus
}
#endif // __cplusplus

#endif // LIST_H_INCLUDED

//Thanks for reading.Love you.
