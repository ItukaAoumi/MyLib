//Do not include me more!
#pragma once
#ifndef UMIVECTORMATRIX
#define UMIVECTORMATRIX

//Can be used in cpp.
#ifdef __cplusplus
extern "C" {
#endif // __cplusplus


/*
Vector Data Type
This can be used to store a sequence of data.
X(x[0], x[1], ... , x[n-1]),x[i] is data and n is the dimension.
*/

//data structure
struct umiVector;
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
Return the vector.
*/
umiVec_p umiVec_New(const unsigned int dims);

//Copy a vector.
umiVec_p umiVec_Copy(const umiVec_p vec);

/*
Reset the dimensions of a vector.
params:
vec: vector
dims: new dimensions
Return 1 if succeed.
*/
umiVec_p umiVec_Reset(umiVec_p vec, const unsigned int dims);

//Clear data and dimensions of a vector.
umiVec_p umiVec_Clr(umiVec_p vec);

//Delete a vector. Use once at last.
char umiVec_Del(umiVec_p * vec);

//Return the pointer or dimensions
double * umiVec_Val(const umiVec_p vec);
unsigned int umiVec_Dims(const umiVec_p vec);

/*
Edit the value of a dimension.
vec: vector
dim: selected dimension
val: value
Return the vector
*/
umiVec_p umiVec_EditVal(const umiVec_p vec, const unsigned int dim, const double val);

/*
Set all values of a vector.
vec: vector
source: pointer of the source data array
*/
umiVec_p umiVec_EditValFromA(const umiVec_p vec, const double * source);

/*
Get the value of a dimension.
vec: vector
dim: selected dimension
Return the value
*/
double umiVec_GetVal(const umiVec_p vec, const unsigned int dim);

/*
Get all values of a vector. Copy to an array.
vec: vector
dest: pointer of the destination array
Return the destination array.
*/
double * umiVec_GetValToA(const umiVec_p vec, double * dest);

//Get the length of a vector.
double umiVec_Len(const umiVec_p vec);

//Insert a dimension.
umiVec_p umiVec_InsDim(const umiVec_p vec, const unsigned int dim);

//Delete a dimension.
umiVec_p umiVec_DelDim(const umiVec_p vec, const unsigned int dim);

//Reverse a vector. x[i]=-x[i]
umiVec_p umiVec_Neg(umiVec_p vec, const unsigned char preserve);

/*
Add two vectors and put at a new one.
params:
vecl: left vector
vecr: right vector
preserve: preserve (1) or not (0) the old one.
Return the new vector.
*/
umiVec_p umiVec_Add(umiVec_p vecl, umiVec_p vecr, const unsigned char preserve);

//Substrate two vectors and put at a new one.
umiVec_p umiVec_Sub(umiVec_p vecl, umiVec_p vecr, const unsigned char preserve);

//Multiply a vector and put at a new one.
umiVec_p umiVec_Mul(umiVec_p vec, const double num, const unsigned char preserve);

//Dot (inner) product of two vectors.
double umiVec_DotProd(umiVec_p vecl, umiVec_p vecr, const unsigned char preserve);

//Direct (Hadamard) product of two vectors.
umiVec_p umiVec_DirectProd(umiVec_p vecl, umiVec_p vecr, const unsigned char preserve);

//Tensor (Kronecker) product of two vectors.
umiVec_p umiVec_TensorProd(umiVec_p vecl, umiVec_p vecr, const unsigned char preserve);

//
umiVec_p umiVec_Conv(umiVec_p vecl, umiVec_p vecr);

char umiVec_Print(const umiVec_p vec);
//to be continued


/*
Matrix Data Type
There are a lot of BUGS
must be made by Ji Qi Yi
QwQ ying ying ying
*/

//data structure
struct umiMatrix;
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
Create a new matrix, which each element is 0.
params:
rows: rows of the new matrix
cols: columns of the new matrix
Return the pointer.
*/
umiMat_p umiMat_New(const unsigned int rows, const unsigned int cols);

//Copy a matrix.
umiMat_p umiMat_Copy(const umiMat_p mat);

/*
Create a new identity matrix. The rows and columns are the same.
params:
rows: rows and columns of the new matrix
val: value of the identity matrix
Return the identity matrix.
*/
umiMat_p umiMat_NewIdMat(const unsigned int rows, const double val);

/*
Reset the rows and cols of a matrix.
params:
mat: matrix
rows: new rows
cols: new columns
Return the new matrix if succeed.
*/
umiMat_p umiMat_Reset(const umiMat_p mat, const unsigned int rows, const unsigned int cols);

//Clear data, rows and cols of a matrix.
umiMat_p umiMat_Clr(const umiMat_p mat);

//Delete a matrix. Use once at last.
char umiMat_Del(umiMat_p * mat);

//Return the pointer, rows or columns.
double * * umiMat_Val(const umiMat_p mat);
unsigned int umiMat_Rows(const umiMat_p mat);
unsigned int umiMat_Cols(const umiMat_p mat);

/*
Edit a value of a matrix.
params:
mat: matrix
row: row number
col: column number
val: value
Return the matrix if succeed.
*/
umiMat_p umiMat_EditVal(const umiMat_p mat, const unsigned int row, const unsigned int col, const double val);

/*
Edit a row (or column) of a matrix. Copy from an array.
params:
mat: matrix
row: row number (col : column number)
source: pointer of the data source array
Return the matrix if succeed.
*/
umiMat_p umiMat_EditRowFromA(const umiMat_p mat, const unsigned int row, const double * source);
umiMat_p umiMat_EditColFromA(const umiMat_p mat, const unsigned int col, const double * source);

/*
Edit a row (or column) of a matrix. Copy from a vector.
params:
mat: matrix
row: row number (col : column number)
rowvec (colvec): vector
Return the matrix if succeed.
*/
umiMat_p umiMat_EditRowFromV(const umiMat_p mat, const unsigned int row, const umiVec_p rowvec);
umiMat_p umiMat_EditColFromV(const umiMat_p mat, const unsigned int col, const umiVec_p colvec);

/*
Get a value of a matrix.
params:
mat: matrix
row: row number
col: column number
Return the value.
*/
double umiMat_GetVal(const umiMat_p mat, const unsigned int row, const unsigned int col);

/*
Get a row (or column) of a matrix. Copy to an array.
params:
mat: matrix
row: row number (col : column number)
dest: pointer of the destination array
Return the destination array if succeed.
*/
double * umiMat_GetRowToA(const umiMat_p mat, const unsigned int row, double * dest);
double * umiMat_GetColToA(const umiMat_p mat, const unsigned int col, double * dest);

/*
Get a row (or column) of a matrix. Copy to a vector.
params:
mat: matrix
row: row number (col : column number)
Return the vector if succeed.
*/
umiVec_p umiMat_GetRowToV(const umiMat_p mat, const unsigned int row);
umiVec_p umiMat_GetColToV(const umiMat_p mat, const unsigned int col);

/*Matrix Operations*/

//Multiply a row (or column).
umiMat_p umiMat_MulRow(const umiMat_p mat, const unsigned int row, const double mul);
umiMat_p umiMat_MulCol(const umiMat_p mat, const unsigned int col, const double mul);

//Swap two rows (or columns).
umiMat_p umiMat_SwapRow(const umiMat_p mat, const unsigned int row1, const unsigned int row2);
umiMat_p umiMat_SwapCol(const umiMat_p mat, const unsigned int col1, const unsigned int col2);

//Add a row (or columns) to another and cover itself.
umiMat_p umiMat_AddRow(const umiMat_p mat, const unsigned int row1, const unsigned int row2, const double mul);
umiMat_p umiMat_AddCol(const umiMat_p mat, const unsigned int col1, const unsigned int col2, const double mul);

//Sort the matrix by a key row (or column)
//order: 0 for ascending, 1 for descending
umiMat_p umiMat_SortByRow(const umiMat_p mat, const unsigned int keyrow, const unsigned char order);
umiMat_p umiMat_SortByCol(const umiMat_p mat, const unsigned int keycol, const unsigned char order);

//Insert a row (or column).
umiMat_p umiMat_InsRow(const umiMat_p mat, const unsigned int row);
umiMat_p umiMat_InsCol(const umiMat_p mat, const unsigned int col);

//Delete a row (or column).
umiMat_p umiMat_DelRow(const umiMat_p mat, const unsigned int row);
umiMat_p umiMat_DelCol(const umiMat_p mat, const unsigned int col);

//Get the negative of a matrix. a[i][j] = -a[i][j]
umiMat_p umiMat_Neg(const umiMat_p mat, const unsigned char preserve);

/*
Transpose a matrix and put at a new one.
params:
mat: matrix
preserve: preserve (1) or not (0) the old one
Return the new matrix.
*/
umiMat_p umiMat_Trans(const umiMat_p mat, const unsigned char preserve);

/*
Add two matrix and put at a new one.
params:
matl: left matrix
matr: right matrix
preserve: preserve (1) or not (0) the old one
Return the new matrix.
*/
umiMat_p umiMat_Add(const umiMat_p matl, const umiMat_p matr, const unsigned char preserve);

//Substrate two matrix and put at a new one.
umiMat_p umiMat_Sub(const umiMat_p matl, const umiMat_p matr, const unsigned char preserve);

//Multiply a matrix and put at a new one.
umiMat_p umiMat_Mul(const umiMat_p mat, const double num, const unsigned char preserve);

//Cross product of two matrix. AB O(r1*c1*c2)
umiMat_p umiMat_CrossProd(const umiMat_p matl, const umiMat_p matr, const unsigned char preserve);

//Direct (Hadamard) product of two matrix. A*B
umiMat_p umiMat_DirectProd(const umiMat_p matl, const umiMat_p matr, const unsigned char preserve);

//Tensor (Kronecker) product of two matrix.
umiMat_p umiMat_TensorProd(const umiMat_p matl, const umiMat_p matr, const unsigned char preserve);

//Row transforming to identity matrix at left. [A]->[E,B]
umiMat_p umiMat_RowTrans(const umiMat_p mat);

//Column transforming to identity matrix at top.
umiMat_p umiMat_ColTrans(const umiMat_p mat);

char umiMat_Print(const umiMat_p mat);
//to be continued


#ifdef __cplusplus
}
#endif // __cplusplus

#endif // UMIVECTORMATRIX

//Thanks for reading.[bi xin xin]
