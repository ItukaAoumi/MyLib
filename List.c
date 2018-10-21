/*
This is a library of liner data structures,including single-dimension list,double-dimension list,stack and queue.
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
	list->FirstItem=0;
	list->Length=list->MaxIndex=0;
	return 1;
}

//Seeking the address of an item by its index.
L1DI_p List1D_Seek(List1D_p list,unsigned int index)
{
	if (!list) return 0;
	for (L1DI_p ptr=list->FirstItem;ptr;ptr=ptr->NextItem)
		if (ptr->Index==index) return ptr;
	return 0;
}

//Add an item to the head and return its ptr.
L1DI_p List1D_Add(List1D_p list,unsigned int index)
{
	if (!list) return 0;
	//check if the item exists
	L1DI_p nitem=List1D_Seek(list,index);
	if (nitem) return nitem;
	//create a new item
	nitem=(L1DI_p)malloc(L1DIsize);
	if (!nitem) return 0;
	//initializing
	nitem->Index=index;
	nitem->Data=0;
	nitem->DataSize=0;
	nitem->TypeName=0;
	nitem->NextItem=list->FirstItem;
	list->FirstItem=nitem;
	list->Length++;
	return nitem;
}

//Edit data of an item.Return 1 if succeed.
char List1D_Edit(L1DI_p item,void * data,unsigned char datasize,char * type_name)
{
	if (!(item&&data&&datasize)) return 0;
	//clear and copy data
	free(item->Data);
	item->Data=malloc(datasize);
	if (item->Data) memcpy(item->Data,data,datasize);
	else return 0;
	//copy size
	item->DataSize=datasize;
	//clear and copy type name
	free(item->TypeName);
	if (type_name)//type name exists
	{
		item->TypeName=(char *)malloc(strlen(type_name)+1);
		if (item->TypeName) strcpy(item->TypeName,type_name);
		else return 0;
	}
	else
		item->TypeName=0;
	return 1;
}

//Delete an item.
char List1D_Del(List1D_p list,L1DI_p item)
{
	if (!(list&&item)) return 0;
	if (!list->FirstItem) return 0;
	if (list->FirstItem!=item)//is not the first
	{
		L1DI_p last;//behind item
		for (last=list->FirstItem;last;last=last->NextItem)//scan the list
			if (last->NextItem==item)//find the item
			{
				last->NextItem=item->NextItem;
				break;
			}
		if (!last) return 0;
	}
	else//delete the first item
		list->FirstItem=item->NextItem;
	free(item->Data);
	free(item->TypeName);
	free(item);
	list->Length--;
	return 1;
}

//Clear the list.Use once at last.
char List1D_Clr(List1D_p list)
{
	if (!list) return 0;
	L1DI_p ptr;
	while (list->FirstItem)
	{
		ptr=list->FirstItem;
		list->FirstItem=list->FirstItem->NextItem;
		free(ptr->Data);
		free(ptr->TypeName);
		free(ptr);
	}
	list->Length=0;
	list->MaxIndex=0;
	return 1;
}

//Get the max index.
unsigned int List1D_MaxIndex(List1D_p list)
{
	if (!list) return 0;
	L1DI_p ptr;unsigned int maxi;
	for (ptr=list->FirstItem,maxi=0;ptr;ptr=ptr->NextItem)
		if (ptr->Index>maxi)
			maxi=ptr->Index;
	list->MaxIndex=maxi;
	return maxi;
}

//Get data by ptr
void * List1D_GetData_p(L1DI_p item)
{
	if (!item) return 0;
	return item->Data;
}

//Get data by index.
void * List1D_GetData_i(List1D_p list,unsigned int index)
{
	if (!list) return 0;
	return List1D_GetData_p(List1D_Seek(list,index));
}

//Get data size by ptr.
unsigned char List1D_GetSize_p(L1DI_p item)
{
	if (!item) return 0;
	return item->DataSize;
}

//Get type name by ptr.
char * List1D_GetTypeName_p(L1DI_p item)
{
	if (!item) return 0;
	return item->TypeName;
}


//to be continued


/*
Stack
A kind of First-In-Last Out data structure.
*/

//Functions of Stack

/*
Create a new stack like this : Stack_t <name> = { 0 , 0 }
or Stack_p <name> = ( Stack_p ) malloc( Stksize ) ; Stk_Init( name )
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
	//create a new item
	SI_p nitem=(SI_p)malloc(SIsize);
	if (!nitem) return 0;
	//create a new data area
	nitem->Data=malloc(datasize);
	if (!nitem->Data) return 0;
	//copy data and size
	memcpy(nitem->Data,data,datasize);
	nitem->DataSize=datasize;
	//create type name
	if (type_name)//type name exists
	{
		nitem->TypeName=(char *)malloc(strlen(type_name)+1);
		if (nitem->TypeName) strcpy(nitem->TypeName,type_name);
	}
	else//not exist
		nitem->TypeName=0;
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
	//create a new data area to return
	void * data=malloc(stk->Top->DataSize);
	if (!data) return 0;
	//copy data,size and type name
	memcpy(data,stk->Top->Data,stk->Top->DataSize);
	* datasize=stk->Top->DataSize;
	if (type_name) strcpy(type_name,stk->Top->TypeName);
	//move to the next item and delete
	SI_p ptr=stk->Top;
	stk->Top=stk->Top->next;
	free(ptr->Data);
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
		free(ptr->Data);
		free(ptr->TypeName);
		free(ptr);
	}
	stk->Length=0;
	return 1;
}


//to be continued


/*
Queue
A kind of First-In-First-Out data structure.
*/

//Functions of Queue

/*
Create a new queue like this : Queue_t <name> = { 0 , 0 , 0 }
or Queue_p <name> = ( Queue_p ) malloc( Quesize ) ; Que_Init( name )
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
	//create a new item
	QI_p nitem=(QI_p)malloc(QIsize);
	if (!nitem) return 0;
	//create a new data area
	nitem->Data=malloc(datasize);
	if (!nitem->Data) return 0;
	//copy data and size
	memcpy(nitem->Data,data,datasize);
	nitem->DataSize=datasize;
	//create type name
	if (type_name)//type name exists
	{
		nitem->TypeName=(char *)malloc(strlen(type_name)+1);
		if (nitem->TypeName) strcpy(nitem->TypeName,type_name);
	}
	else//not exist
		nitem->TypeName=0;
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
	//create a new data area to return
	void * data=malloc(que->Head->DataSize);
	if (!data) return 0;
	//copy data,size and type name
	memcpy(data,que->Head->Data,que->Head->DataSize);
	* datasize=que->Head->DataSize;
	if (type_name) strcpy(type_name,que->Head->TypeName);
	//move to next item and delete
	QI_p ptr=que->Head;
	que->Head=que->Head->next;
	if (!que->Head) que->Tail=0;
	free(ptr->Data);
	free(ptr->TypeName);
	free(ptr);
	que->Length--;
	return data;
}

//Clear the queue.
char Que_Clr(Queue_p que)
{
	if (!que) return 0;
	QI_p ptr;
	while (que->Head)
	{
		ptr=que->Head;
		que->Head=que->Head->next;
		free(ptr->Data);
		free(ptr->TypeName);
		free(ptr);
	}
	que->Tail=0;
	que->Length=0;
	return 1;
}


//to be continued


/*
Double-Dimension List
Can be used to store a matrix.
*/

//Functions of List2D:

/*
Create a new double-dimension list like this : List2D_t <name> = { 0 , 0 , 0 , 0 }
or List2D_p <name> = ( List2D_p ) malloc( List2Dsize ) ; List2D_Init( name )
You can use the macro definition List2D_New or List2D_New_p(name) .
*/

//Initialize a 2D list.Use once at first.Return 1 if succeed.
char List2D_Init(List2D_p list)
{
	if (!list) return 0;
	list->FirstRow=0;
	list->RowLength=list->MaxRow=list->MaxCol=0;
	return 1;
}

//Seek a row item
L2DRI_p List2D_SeekRow(List2D_p list,unsigned int rownum)
{
	if (!list) return 0;
	for (L2DRI_p ptr=list->FirstRow;ptr;ptr=ptr->NextRow)
		if (ptr->Row==rownum) return ptr;
	return 0;
}

//Seek a col item
L2DCI_p List2D_SeekCol(L2DRI_p rowitem,unsigned int colnum)
{
	if (!rowitem) return 0;
	for (L2DCI_p ptr=rowitem->FirstCol;ptr;ptr=ptr->NextCol)
		if (ptr->Col==colnum) return ptr;
	return 0;
}

//Seek an item by row and col number
L2DCI_p List2D_SeekItem(List2D_p list,unsigned int rownum,unsigned int colnum)
{
	if (!list) return 0;
	return List2D_SeekCol(List2D_SeekRow(list,rownum),colnum);
}

//Add a row item and return its ptr.
L2DRI_p List2D_AddRow(List2D_p list,unsigned int rownum)
{
	if (!list) return 0;
	//check if the item exists
	L2DRI_p nrow=List2D_SeekRow(list,rownum);
	if (nrow) return nrow;
	//create a new item
	nrow=(L2DRI_p)malloc(L2DRIsize);
	if (!nrow) return 0;
	//initializing
	nrow->Row=rownum;
	nrow->FirstCol=0;
	nrow->ColLength=0;
	nrow->NextRow=list->FirstRow;
	list->FirstRow=nrow;
	list->RowLength++;
	return nrow;
}

//Add a col item and return its ptr.
L2DCI_p List2D_AddCol(L2DRI_p rowitem,unsigned int colnum)
{
	if (!rowitem) return 0;
	//check if the item exists
	L2DCI_p ncol=List2D_SeekCol(rowitem,colnum);
	if (ncol) return ncol;
	//create a new item
	ncol=(L2DCI_p)malloc(L2DCIsize);
	if (!ncol) return 0;
	//initializing
	ncol->Col=colnum;
	ncol->Data=0;
	ncol->DataSize=0;
	ncol->TypeName=0;
	ncol->NextCol=rowitem->FirstCol;
	rowitem->FirstCol=ncol;
	rowitem->ColLength++;
	return ncol;
}

//Edit an item.Return 1 if succeed.
char List2D_Edit(L2DCI_p item,void * data,unsigned char datasize,char * type_name)
{
	if (!(item&&data&&datasize)) return 0;
	//clear and copy data
	free(item->Data);
	item->Data=malloc(datasize);
	if (item->Data) memcpy(item->Data,data,datasize);
	else return 0;
	//copy size
	item->DataSize=datasize;
	//clear and copy type name
	free(item->TypeName);
	if (type_name)//type name exists
	{
		item->TypeName=(char *)malloc(strlen(type_name)+1);
		if (item->TypeName) strcpy(item->TypeName,type_name);
		else return 0;
	}
	else
		item->TypeName=0;
	return 1;
}

//Delete a row item and all of its col items
char List2D_DelRow(List2D_p list,L2DRI_p rowitem)
{
	if (!(list&&rowitem)) return 0;
	if (rowitem!=list->FirstRow)//is not the first row
	{
		L2DRI_p last;//behind rowitem
		for (last=list->FirstRow;last;last=last->NextRow)
			if (last->NextRow==rowitem) break;
		if (!last) return 0;
		last->NextRow=rowitem->NextRow;
	}
	else//delete the first row
		list->FirstRow=rowitem->NextRow;
	List2D_ClrRow(rowitem);
	free(rowitem);
	list->RowLength--;
	return 1;
}

//Delete a col item
char List2D_DelCol(L2DRI_p rowitem,L2DCI_p colitem)
{
	if (!(rowitem&&colitem)) return 0;
	if (colitem!=rowitem->FirstCol)//is not the first col
	{
		L2DCI_p last;//behind colitem
		for (last=rowitem->FirstCol;last;last=last->NextCol)
			if (last->NextCol==colitem) break;
		if (!last) return 0;
		last->NextCol=colitem->NextCol;
	}
	else//delete the first col
		rowitem->FirstCol=colitem->NextCol;
	free(colitem->Data);
	free(colitem->TypeName);
	free(colitem);
	rowitem->ColLength--;
	return 1;
}

//Clear a row.
char List2D_ClrRow(L2DRI_p rowitem)
{
	if (!rowitem) return 0;
	L2DCI_p ptr;
	while (rowitem->FirstCol)
	{
		ptr=rowitem->FirstCol;
		rowitem->FirstCol=rowitem->FirstCol->NextCol;
		free(ptr->Data);
		free(ptr->TypeName);
		free(ptr);
	}
	rowitem->ColLength=0;
	return 1;
}

//Clear the 2D list.Use once at last.
char List2D_Clr(List2D_p list)
{
	if (!list) return 0;
	L2DRI_p ptr;
	while (list->FirstRow)
	{
		if (!List2D_ClrRow(list->FirstRow)) return 0;
		ptr=list->FirstRow;
		list->FirstRow=list->FirstRow->NextRow;
		free(ptr);
	}
	list->RowLength=0;
	return 1;
}

//Get data by ptr
void * List2D_GetData_p(L2DCI_p item)
{
	if (!item) return 0;
	return item->Data;
}

//Get data by row and col number.
void * List2D_GetData_i(List2D_p list,unsigned int rownum,unsigned int colnum)
{
	if (!list) return 0;
	return List2D_GetData_p(List2D_SeekItem(list,rownum,colnum));
}

//Get data size by ptr
unsigned char List2D_GetSize_p(L2DCI_p item)
{
	if (!item) return 0;
	return item->DataSize;
}

//Get type name by ptr
char * List2D_GetTypeName_p(L2DCI_p item)
{
	if (!item) return 0;
	return item->TypeName;
}


//to be continued


#ifdef __cplusplus
}
#endif // __cplusplus

//Thanks for reading.Love you.[bi xin]
