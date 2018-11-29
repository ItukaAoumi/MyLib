//Do not include me twice or more!
#pragma once
#ifndef MATRIXVECTOR_H_INCLUDED
#define MATRIXVECTOR_H_INCLUDED

//Can be used in cpp.
#ifdef __cplusplus
extern "C" {
#endif // __cplusplus


#ifndef UMIVECTOR
#define UMIVECTOR

/*
Vector Data Type
This can be used to store a sequence of data.
X(x[0], x[1], ... , x[n-1]),x[i] is data and n is the dimension.
*/

//data structure
typedef struct umiVector umiVec_t;
typedef struct umiVector * umiVec_p;

/*
Create a new vector:
You can use both
umiVec_t <name> = {0 , 0};
or
umiVec_p <name> = umiVec_New(dimensions);
to create a new vector.
*/

/*
Create a new vector.
params:
dims: dimensions of the vector
Return the pointer.
*/
umiVec_p umiVec_New(unsigned int dims);

/*
Reset the dimensions of a vector.
params:
vec: vector
dims: new dimensions
Return 1 if succeed.
*/
char umiVec_ResetDim(umiVec_p vec, unsigned int dims);

/*
Set the value of a dimension.
vec: vector
dim: selected dimension
val: value
*/
char umiVec_SetVal(umiVec_p vec, unsigned int dim, double val);

/*
Set all values of a vector.
vec: vector
source: pointer of the source data array
*/
char umiVec_SetAllVal(umiVec_p vec, double * source);

/*
Get the value of a dimension.
vec: vector
dim: selected dimension
*/
double umiVec_GetVal(umiVec_p vec, unsigned int dim);

/*
Get all values of a vector. Copy to an array.
vec: vector
dest: pointer of the destination array
*/
char umiVec_GetAllVal(umiVec_p vec, double * dest);

//Clear data and dimensions of a vector.
char umiVec_Clr(umiVec_p vec);

//Delete a vector. Use once at last.
void umiVec_Del(umiVec_p * vec);

//Reverse a vector. x[i]=-x[i]
char umiVec_Rev(umiVec_p vec);

/*
Add two vectors and cover the left one.
params:
vecl: left vector
vecr: right vector
*/
char umiVec_AddSelf(umiVec_p vecl, umiVec_p vecr);

//Add two vectors to a new one.
umiVec_p umiVec_Add(umiVec_p vecl, umiVec_p vecr);

//Substrate two vectors and cover the left one.
char umiVec_SubSelf(umiVec_p vecl, umiVec_p vecr);

//Substrate two vectors to a new one.
umiVec_p umiVec_Sub(umiVec_p vecl, umiVec_p vecr);

//Multiplication of a vector and cover itself.
char umiVec_MulSelf(umiVec_p vec, double num);

//Multiplication of a vector. To a new one.
umiVec_p umiVec_Mul(umiVec_p vec, double num);

//Dot product(inner product) of two vectors.
double umiVec_Dot(umiVec_p vecl, umiVec_p vecr);

//Direct product of two vectors. Cover the left one.
char umiVec_DirSelf(umiVec_p vecl, umiVec_p vecr);

//Direct product of two vectors.
umiVec_p umiVec_Dir(umiVec_p vecl, umiVec_p vecr);

//
umiVec_p umiVec_Conv(umiVec_p vecl, umiVec_p vecr);

//Get the length of a vector.
double umiVec_Len(umiVec_p vec);


//to be continued
#endif // UMIVECTOR


#ifndef UMIMATRIX
#define UMIMATRIX

/*
Matrix Data Type
There are a lot of BUGS
must be made by Ji Qi Yi
QwQ ying ying ying
*/

//data structure
typedef struct umiMatrix umiMat_t;
typedef struct umiMatrix * umiMat_p;

/*
Create a new matrix:
You can use both
umiMat_t <name> = {0 , 0 , 0};
or
umiMat_p <name> = umiMat_New(rows, cols);
to create a new matrix.
*/

/*
Create a new matrix.
params:
rows: rows of the new matrix
cols: columns of the new matrix
Return the pointer.
*/
umiMat_p umiMat_New(unsigned int rows, unsigned int cols);

/*
Create a new identity matrix.The rows and columns are the same.
params:
rows: rows and columns of the new matrix
val: value of the identity matrix
*/
umiMat_p umiMat_NewIdMat(unsigned int rows, double val);

/*
Reset the rows and cols of a matrix.
params:
mat: matrix
rows: new rows
cols: new columns
Return 1 if succeed.
*/
char umiMat_Reset(umiMat_p mat, unsigned int rows, unsigned int cols);

//Return the rows or columns of a matrix.
unsigned int umiMat_Rows(umiMat_p mat);
unsigned int umiMat_Cols(umiMat_p mat);

/*
Set a value of a matrix.
params:
mat: matrix
row: row number
col: column number
val: value
Return 1 if succeed.
*/
char umiMat_SetVal(umiMat_p mat, unsigned int row, unsigned int col, double val);

/*
Set a row of a matrix. Copy from an array.
params:
mat: matrix
row: row number
source: pointer of the data source array
Return 1 if succeed.
*/
char umiMat_SetRow(umiMat_p mat, unsigned int row, double * source);

//Set a column of a matrix. Copy from an array.
char umiMat_SetCol(umiMat_p mat, unsigned int col, double * source);

//Get a value of a matrix.
double umiMat_GetVal(umiMat_p mat, unsigned int row, unsigned int col);

/*
Get a row of a matrix. Copy to an array.
dest: pointer of the destination array
*/
char umiMat_GetRow(umiMat_p mat, unsigned int row, double * dest);

//Get a column. Copy to an array.
char umiMat_GetCol(umiMat_p mat, unsigned int col, double * dest);

//Swap two rows.
char umiMat_SwapRow(umiMat_p mat, const unsigned int row1, const unsigned int row2);

//Swap two columns.
char umiMat_SwapCol(umiMat_p mat, const unsigned int col1, const unsigned int col2);

/*
Sort the matrix by a key row.
order: 0 for ascending, 1 for descending
*/
char umiMat_SortByRow(umiMat_p mat, const unsigned int keyrow, const unsigned char order);

/*
Sort the matrix by a key column.
order: 0 for ascending, 1 for descending
*/
char umiMat_SortByCol(umiMat_p mat, const unsigned int keycol, const unsigned char order);

//Clear data, rows and cols of a matrix.
char umiMat_Clr(umiMat_p mat);

//Delete a matrix. Use once at last.
void umiMat_Del(umiMat_p * mat);

//Reverse a matrix. a[i][j] = -a[i][j]
char umiMat_Rev(umiMat_p mat);

/*
Add two matrix and cover the left one.
matl: left matrix
matr: right matrix
*/
char umiMat_AddSelf(umiMat_p matl, umiMat_p matr);

//Add two matrix to a new one.
umiMat_p umiMat_Add(umiMat_p matl, umiMat_p matr);

//Substrate two matrix and cover the left one.
char umiMat_SubSelf(umiMat_p matl, umiMat_p matr);

//Substrate two matrix to a new one.
umiMat_p umiMat_Sub(umiMat_p matl, umiMat_p matr);

//Multiplication of a matrix and cover itself.
char umiMat_MulSelf(umiMat_p mat, double num);

//Multiplication of a matrix. To a new one.
umiMat_p umiMat_Mul(umiMat_p mat, double num);

//Direct product of two matrix.Cover the left one.
char umiMat_DirSelf(umiMat_p matl, umiMat_p matr);

//Direct product of two matrix.To a new one.
umiMat_p umiMat_Dir(umiMat_p matl, umiMat_p matr);

//Cross product of two matrix.
umiMat_p umiMat_Cross(umiMat_p matl, umiMat_p matr);



//Transpose a matrix and cover itself.
char umiMat_TransSelf(umiMat_p * mat);

//Transpose a matrix to a new one.
umiMat_p umiMat_Trans(umiMat_p mat);

void umiMat_Print(umiMat_p mat);


//to be continued
#endif // UMIMATRIX


#ifdef __cplusplus
}
#endif // __cplusplus

#endif // MATRIX&VECTOR_H_INCLUDED

//Thanks for reading.[bi xin xin]
