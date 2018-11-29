#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <math.h>
#include "Matrix&Vector.h"

//Can be used in cpp.
#ifdef __cplusplus
extern "C" {
#endif // __cplusplus


/*
Vector Data Type
This can be used to store a sequence of data.
X(x[0], x[1], ... , x[n-1]),x[i] is data and n is the dimension.
*/

//definition of data structure
struct umiVector
{
	double * Val;//the pointer of data
	unsigned int Dims;//dimensions
};

//the size of a vector
const static unsigned char umiVecsize = sizeof(struct umiVector);

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
umiVec_p umiVec_New(unsigned int dims)
{
	if (!dims) return 0;
	//create a new vector
	umiVec_p nvec = (umiVec_p) malloc(umiVecsize);	if (!nvec) return 0;
	//create value
	nvec->Val = (double *) malloc(dims * 8);	if (!nvec->Val) {free(nvec); return 0;}
	//init.
	for (unsigned int i = 0; i < dims; i++) nvec->Val[i] = 0;
	nvec->Dims = dims;
	return nvec;
}

/*
Reset the dimensions of a vector.
params:
vec: vector
dims: new dimensions
Return 1 if succeed.
*/
char umiVec_ResetDim(umiVec_p vec, unsigned int dims)
{
	if (!(vec && dims)) return 0;
	if (dims == vec->Dims) return 0;
	//reset value
	free(vec->Val);
	vec->Val = (double *) malloc(dims * 8);	if (!vec->Val) {vec->Dims = 0; return 0;}
	//init.
	for (unsigned int i = 0; i < dims; i++) vec->Val[i] = 0;
	vec->Dims = dims;
	return 1;
}

#define CheckVec if (!vec) return 0; if (!(vec->Val && vec->Dims)) return 0;
#define CheckDim if (dim >= vec->Dims) return 0;

/*
Set the value of a dimension.
vec: vector
dim: selected dimension
val: value
*/
char umiVec_SetVal(umiVec_p vec, unsigned int dim, double val)
{
	CheckVec
	CheckDim
	vec->Val[dim] = val;
	return 1;
}

/*
Set all values of a vector.
vec: vector
source: pointer of the source data array
*/
char umiVec_SetAllVal(umiVec_p vec, double * source)
{
	CheckVec
	if (!source) return 0;
	memcpy(vec->Val, source, vec->Dims * 8);
	return 1;
}

/*
Get the value of a dimension.
vec: vector
dim: selected dimension
*/
double umiVec_GetVal(umiVec_p vec, unsigned int dim)
{
	CheckVec
	CheckDim
	return vec->Val[dim];
}

/*
Get all values of a vector. Copy to an array.
vec: vector
dest: pointer of the destination array
*/
char umiVec_GetAllVal(umiVec_p vec, double * dest)
{
	CheckVec
	if (!dest) return 0;
	memcpy(dest, vec->Val, vec->Dims * 8);
	return 1;
}

//Clear data and dimensions of a vector.
char umiVec_Clr(umiVec_p vec)
{
	if (!vec) return 0;
	if (!(vec->Val || vec->Dims)) return 0;
	free(vec->Val);
	vec->Val = vec->Dims = 0;
	return 1;
}

//Delete a vector. Use once at last.
void umiVec_Del(umiVec_p * vec)
{
	if (!vec) return;
	umiVec_Clr(*vec);
	*vec = 0;
	return;
}

//Reverse a vector. x[i]=-x[i]
char umiVec_Rev(umiVec_p vec)
{
	CheckVec
	for (unsigned int i = 0; i < vec->Dims; i++) vec->Val[i] = -vec->Val[i];
	return 1;
}

#define CheckLR if (!(vecl && vecr)) return 0; if (!(vecl->Val && vecl->Dims && vecr->Val && vecr->Dims && vecl->Dims == vecr->Dims)) return 0;

/*
Add two vectors and cover the left one.
params:
vecl: left vector
vecr: right vector
*/
char umiVec_AddSelf(umiVec_p vecl, umiVec_p vecr)
{
	CheckLR
	//add two vectors
	for (unsigned int i = 0; i < vecl->Dims; i++)
		vecl->Val[i] = vecl->Val[i] + vecr->Val[i];
	return 1;
}

//Add two vectors to a new one.
umiVec_p umiVec_Add(umiVec_p vecl, umiVec_p vecr)
{
	CheckLR
	//create a new vector to store the result
	umiVec_p nvec = umiVec_New(vecl->Dims);	if (!nvec) return 0;
	//add two vectors
	for (unsigned int i = 0; i < vecl->Dims; i++)
		nvec->Val[i] = vecl->Val[i] + vecr->Val[i];
	return nvec;
}

//Substrate two vectors and cover the left one.
char umiVec_SubSelf(umiVec_p vecl, umiVec_p vecr)
{
	CheckLR
	//sub
	for (unsigned int i = 0; i < vecl->Dims; i++)
		vecl->Val[i] = vecl->Val[i] - vecr->Val[i];
	return 1;
}

//Substrate two vectors to a new one.
umiVec_p umiVec_Sub(umiVec_p vecl, umiVec_p vecr)
{
	CheckLR
	//create a new vector to store the result
	umiVec_p nvec = umiVec_New(vecl->Dims);	if (!nvec) return 0;
	//substrate two vectors
	for (unsigned int i = 0; i < vecl->Dims; i++)
		nvec->Val[i] = vecl->Val[i] - vecr->Val[i];
	return nvec;
}

//Multiplication of a vector and cover itself.
char umiVec_MulSelf(umiVec_p vec, double num)
{
	CheckVec
	for (unsigned int i = 0; i < vec->Dims; i++)
		vec->Val[i] = vec->Val[i] * num;
	return 1;
}

//Multiplication of a vector. To a new one.
umiVec_p umiVec_Mul(umiVec_p vec, double num)
{
	CheckVec
	//create a new vector
	umiVec_p nvec = umiVec_New(vec->Dims);	if (!nvec) return 0;
	for (unsigned int i = 0; i < vec->Dims; i++)
		nvec->Val[i] = vec->Val[i] * num;
	return nvec;
}

//Dot product(inner product) of two vectors.
double umiVec_Dot(umiVec_p vecl, umiVec_p vecr)
{
	CheckLR
	double sum = 0;
	for (unsigned int i = 0; i < vecl->Dims; i++)
		sum = sum + vecl->Val[i] * vecr->Val[i];
	return sum;
}

//Direct product of two vectors. Cover the left one.
char umiVec_DirSelf(umiVec_p vecl, umiVec_p vecr)
{
	CheckLR
	//product
	for (unsigned int i = 0; i < vecl->Dims; i++)
		vecl->Val[i] = vecl->Val[i] * vecr->Val[i];
	return 1;
}

//Direct product of two vectors.
umiVec_p umiVec_Dir(umiVec_p vecl, umiVec_p vecr)
{
	CheckLR
	//create a new vector
	umiVec_p nvec = umiVec_New(vecl->Dims);	if (!nvec) return 0;
	//substrate two vectors
	for (unsigned int i = 0; i < vecl->Dims; i++)
		nvec->Val[i] = vecl->Val[i] * vecr->Val[i];
	return nvec;
}

//
umiVec_p umiVec_Conv(umiVec_p vecl, umiVec_p vecr)
{
	if (!(vecl && vecr)) return 0;
	if (!(vecl->Val && vecl->Dims && vecr->Val && vecr->Dims)) return 0;
	//create a new vector
	umiVec_p nvec = umiVec_New(vecl->Dims + vecr->Dims - 1);	if (!nvec) return 0;
	unsigned int i,j;
	for (i = 0; i < vecl->Dims; i++)
		for (j = 0; j < vecr->Dims; j++)
			nvec->Val[i + j] = nvec->Val[i + j] + vecl->Val[i] * vecr->Val[j];
	return nvec;
}

//Get the length of a vector.
double umiVec_Len(umiVec_p vec)
{
	CheckVec
	if (vec->Dims == 1) return *vec->Val;
	double sum = 0;
	for (unsigned int i = 0; i < vec->Dims; i++)
		sum = sum + vec->Val[i] * vec->Val[i];
	return sqrt(sum);
}


#undef CheckVec
#undef CheckDim
#undef CheckLR
//to be continued


/*
Matrix Data Type
There are a lot of BUGS
must be made by Ji Qi Yi
QwQ ying ying ying
*/

//definition of data structure
struct umiMatrix
{
	double * * Val;
	unsigned int Rows;
	unsigned int Cols;
};

//The size of a matrix.
const static unsigned char umiMatsize = sizeof(struct umiMatrix);

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
umiMat_p umiMat_New(unsigned int rows, unsigned int cols)
{
	if (!(rows && cols)) return 0;
	//create a new matrix
	umiMat_p nmat = (umiMat_p) malloc(umiMatsize);	if (!nmat) return 0;
	//create rows
	//QwQ sizeof(double *) is 8 Bytes on 64bit system,change it if running on others.
	nmat->Val = (double * *) malloc(rows * 8);	if (!nmat->Val) return nmat;
	//create columns
	unsigned int r, c;
	for (r = 0; r < rows; r++)
	{
		*(nmat->Val + r) = (double *) malloc(cols * 8);	if (!*(nmat->Val + r)) return nmat;
		for (c = 0; c < cols; c++) *(*(nmat->Val + r) + c) = 0;
	}
	nmat->Rows = rows;
	nmat->Cols = cols;
	return nmat;
}

/*
Create a new identity matrix.The rows and columns are the same.
params:
rows: rows and columns of the new matrix
val: value of the identity matrix
*/
umiMat_p umiMat_NewIdMat(unsigned int rows, double val)
{
	if (!rows) return 0;
	umiMat_p nmat = umiMat_New(rows, rows);
	for (unsigned int i = 0; i < rows; i++) *(*(nmat->Val + i) + i) = val;
	return nmat;
}

/*
Reset the rows and cols of a matrix.
params:
mat: matrix
rows: new rows
cols: new columns
Return 1 if succeed.
*/
char umiMat_Reset(umiMat_p mat, unsigned int rows, unsigned int cols)
{
	if (!(mat && rows && cols)) return 0;
	if (!mat->Val) return 0;
	if (mat->Rows == rows && mat->Cols == cols) return 0;
	//clear columns
	unsigned int r, c;
	for (r = 0; r < mat->Rows; r++) free(*(mat->Val + r));
	//clear and reset rows
	if (mat->Rows != rows)
	{
		free(mat->Val);
		mat->Val = (double * *) malloc(rows * 8);	if(!mat->Val) return 0;
		mat->Rows = rows;
	}
	//reset columns
	for (r = 0; r < rows; r++)
	{
		*(mat->Val + r) = (double *) malloc(cols * 8);	if (!*(mat->Val + r)) return 0;
		for (c = 0; c < cols; c++) *(*(mat->Val + r) + c) = 0;
	}
	mat->Cols = cols;
	return 1;
}

#define CheckMat if (!mat) return 0; if (!(mat->Val && mat->Rows && mat->Cols)) return 0;
#define CheckR if (row >= mat->Rows) return 0;
#define CheckC if (col >= mat->Cols) return 0;

//Return the rows or columns of a matrix.
unsigned int umiMat_Rows(umiMat_p mat)
{
	CheckMat
	return mat->Rows;
}
unsigned int umiMat_Cols(umiMat_p mat)
{
	CheckMat
	return mat->Cols;
}

/*
Set a value of a matrix.
params:
mat: matrix
row: row number
col: column number
val: value
Return 1 if succeed.
*/
char umiMat_SetVal(umiMat_p mat, unsigned int row, unsigned int col, double val)
{
	CheckMat
	CheckR
	CheckC
	mat->Val[row][col] = val;
//	*(*(mat->Val + row) + col) = val;
}

/*
Set a row of a matrix. Copy from an array.
params:
mat: matrix
row: row number
source: pointer of the data source array
Return 1 if succeed.
*/
char umiMat_SetRow(umiMat_p mat, unsigned int row, double * source)
{
	CheckMat
	CheckR
	for (unsigned int c = 0; c < mat->Cols; c++) mat->Val[row][c] = source[c];
	return 1;
}

//Set a column of a matrix. Copy from an array.
char umiMat_SetCol(umiMat_p mat, unsigned int col, double * source)
{
	CheckMat
	CheckC
	for (unsigned int r = 0; r < mat->Rows; r++) mat->Val[r][col] = source[r];
	return 1;
}

//Get a value of a matrix.
double umiMat_GetVal(umiMat_p mat, unsigned int row, unsigned int col)
{
	CheckMat
	CheckR
	CheckC
	return mat->Val[row][col];
//	return *(*(mat->Val + row) + col);
}

/*
Get a row of a matrix. Copy to an array.
dest: pointer of the destination array
*/
char umiMat_GetRow(umiMat_p mat, unsigned int row, double * dest)
{
	CheckMat
	CheckR
	if (!dest) return 0;
	memcpy(dest, mat->Val[row], mat->Cols * 8);
	return 1;
}

//Get a column. Copy to an array.
char umiMat_GetCol(umiMat_p mat, unsigned int col, double * dest)
{
	CheckMat
	CheckC
	if (!dest) return 0;
	for (unsigned int r = 0; r < mat->Rows; r++) dest[r] = mat->Val[r][col];
	return 1;
}

char umiMat_SwapRow(umiMat_p mat, const unsigned int row1, const unsigned int row2)
{
	CheckMat
	if (row1 >= mat->Rows || row2 >= mat->Rows || row1 == row2) return 0;
	double temp = 0;
	for (unsigned int c = 0; c < mat->Cols; c++)
	{
		temp = mat->Val[row1][c];
		mat->Val[row1][c] = mat->Val[row2][c];
		mat->Val[row2][c] = temp;
	}
	return 1;
}

char umiMat_SwapCol(umiMat_p mat, const unsigned int col1, const unsigned int col2)
{
	CheckMat
	if (col1 >= mat->Cols || col2 >= mat->Cols || col1 == col2) return 0;
	double temp = 0;
	for (unsigned int r = 0; r < mat->Rows; r++)
	{
		temp = mat->Val[r][col1];
		mat->Val[r][col1] = mat->Val[r][col2];
		mat->Val[r][col2] = temp;
	}
	return 1;
}

char umiMat_SortByRow(umiMat_p mat, const unsigned int keyrow, const unsigned char order)
{
	CheckMat
	if (keyrow >= mat->Rows || order >= 2) return 0;
	unsigned int c, fin, flag;
	for (fin = 0; fin < mat->Cols - 1; fin++)
	{
		for (c = flag = 0; c + 1 < mat->Cols - fin; c++)
			if ((order && mat->Val[keyrow][c] < mat->Val[keyrow][c + 1]) || (!order && mat->Val[keyrow][c] > mat->Val[keyrow][c + 1]))
			{
				umiMat_SwapCol(mat, c, c + 1);
				flag++;
			}
		if (!flag) break;
	}
	return 1;
}

char umiMat_SortByCol(umiMat_p mat, const unsigned int keycol, const unsigned char order)
{
	CheckMat
	if (keycol >= mat->Cols || order >= 2) return 0;
	unsigned int r, fin, flag;
	for (fin = 0; fin < mat->Rows - 1; fin++)
	{
		for (r = flag = 0; r + 1 < mat->Rows - fin; r++)
			if ((order && mat->Val[r][keycol] < mat->Val[r + 1][keycol]) || (!order && mat->Val[r][keycol] > mat->Val[r + 1][keycol]))
			{
				umiMat_SwapRow(mat, r, r + 1);
				flag++;
			}
		if (!flag) break;
	}
	return 1;
}

//Clear data, rows and cols of a matrix.
char umiMat_Clr(umiMat_p mat)
{
	if (!mat) return 0;
	if (!(mat->Val || mat->Rows || mat->Cols)) return 0;
	for (unsigned int r = 0; r < mat->Rows; r++) free(*(mat->Val + r));
	free(mat->Val);
	mat->Val = mat->Rows = mat->Cols = 0;
	return 1;
}

//Delete a matrix. Use once at last.
void umiMat_Del(umiMat_p * mat)
{
	if (!mat) return;
	if (!(*mat)) return;
	umiMat_Clr(*mat);
	free(*mat);
	*mat = 0;
	return;
}

//Reverse a matrix. a[i][j] = -a[i][j]
char umiMat_Rev(umiMat_p mat)
{
	CheckMat
	for (unsigned int r = 0; r < mat->Rows; r++)
		for (unsigned int c = 0; c < mat->Cols; c++)
			mat->Val[r][c] = -mat->Val[r][c];
	return 1;
}

#define CheckLR if (!(matl && matr)) return 0;\
if (!(matl->Val && matl->Rows && matl->Cols)) return 0;\
if (!(matr->Val && matr->Rows && matr->Cols)) return 0;\
if (matl->Rows != matr->Rows || matl->Cols != matr->Cols) return 0;

/*
Add two matrix and cover the left one.
matl: left matrix
matr: right matrix
*/
char umiMat_AddSelf(umiMat_p matl, umiMat_p matr)
{
	CheckLR
	//add
	unsigned int r,c;
	for (r = 0; r < matl->Rows; r++)
		for (c = 0; c < matl->Cols; c++)
			matl->Val[r][c] = matl->Val[r][c] + matr->Val[r][c];
	return 1;
}

//Add two matrix to a new one.
umiMat_p umiMat_Add(umiMat_p matl, umiMat_p matr)
{
	CheckLR
	//create a new matrix to store the result
	umiMat_p nmat = umiMat_New(matl->Rows, matl->Cols);	if (!nmat) return 0;
	//add two matrix
	unsigned int r,c;
	for (r = 0; r < matl->Rows; r++)
		for (c = 0; c < matl->Cols; c++)
			nmat->Val[r][c] = matl->Val[r][c] + matr->Val[r][c];
	return nmat;
}

//Substrate two matrix and cover the left one.
char umiMat_SubSelf(umiMat_p matl, umiMat_p matr)
{
	CheckLR
	//sub
	unsigned int r,c;
	for (r = 0; r < matl->Rows; r++)
		for (c = 0; c < matl->Cols; c++)
			matl->Val[r][c] = matl->Val[r][c] - matr->Val[r][c];
	return 1;
}

//Substrate two matrix to a new one.
umiMat_p umiMat_Sub(umiMat_p matl, umiMat_p matr)
{
	CheckLR
	//create a new matrix to store the result
	umiMat_p nmat = umiMat_New(matl->Rows, matl->Cols);	if (!nmat) return 0;
	//sub
	unsigned int r,c;
	for (r = 0; r < matl->Rows; r++)
		for (c = 0; c < matl->Cols; c++)
			nmat->Val[r][c] = matl->Val[r][c] - matr->Val[r][c];
	return nmat;
}

//Multiplication of a matrix and cover itself.
char umiMat_MulSelf(umiMat_p mat, double num)
{
	CheckMat
	unsigned int r,c;
	for (r = 0; r < mat->Rows; r++)
		for (c = 0; c < mat->Cols; c++)
			mat->Val[r][c] = mat->Val[r][c] * num;
	return 1;
}

//Multiplication of a matrix. To a new one.
umiMat_p umiMat_Mul(umiMat_p mat, double num)
{
	CheckMat
	//create a new matrix
	umiMat_p nmat = umiMat_New(mat->Rows, mat->Cols);	if (!nmat) return 0;
	//multiplication
	unsigned int r,c;
	for (r = 0; r < mat->Rows; r++)
		for (c=0;c<mat->Cols;c++)
			nmat->Val[r][c] = mat->Val[r][c] * num;
	return nmat;
}

//Direct product of two matrix.Cover the left one.
char umiMat_DirSelf(umiMat_p matl, umiMat_p matr)
{
	CheckLR
	unsigned int r, c;
	for (r = 0; r < matl->Rows; r++)
		for (c = 0; c < matl->Cols; c++)
			matl->Val[r][c] = matl->Val[r][c] * matr->Val[r][c];
	return 1;
}

//Direct product of two matrix.To a new one.
umiMat_p umiMat_Dir(umiMat_p matl, umiMat_p matr)
{
	CheckLR
	//create a new matrix
	umiMat_p nmat = umiMat_New(matl->Rows, matl->Cols);	if (!nmat) return 0;
	//direct product
	unsigned int r, c;
	for (r = 0; r < matl->Rows; r++)
		for (c = 0; c < matl->Cols; c++)
			nmat->Val[r][c] = matl->Val[r][c] * matr->Val[r][c];
	return nmat;
}

//Cross product of two matrix.
umiMat_p umiMat_Cross(umiMat_p matl, umiMat_p matr)
{
	if (!(matl && matr)) return 0;
	if (!(matl->Val && matl->Rows && matl->Cols)) return 0;
	if (!(matr->Val && matr->Rows && matr->Cols)) return 0;
	if (matl->Cols != matr->Rows) return 0;
	//create a new matrix
	umiMat_p nmat = umiMat_New(matl->Rows, matr->Cols);	if (!nmat) return 0;
	//calculating cross product
	unsigned int r,c,i;
	for (r = 0; r < matl->Rows; r++)
		for (c = 0; c < matr->Cols; c++)
			for (i = 0; i < matl->Cols; i++)
				nmat->Val[r][c] = nmat->Val[r][c] + matl->Val[r][i] * matr->Val[i][c];
	return nmat;
}






//Transpose a matrix and cover itself.
char umiMat_TransSelf(umiMat_p * mat)
{
	if (!mat) return 0;
	umiMat_p temp = umiMat_Trans(*mat); if (!temp) return 0;
	umiMat_Del(mat);
	*mat = temp;
	return 1;
}

//Transpose a matrix to a new one.
umiMat_p umiMat_Trans(umiMat_p mat)
{
	CheckMat
	//create a new matrix
	umiMat_p nmat = umiMat_New(mat->Cols, mat->Rows);
	//copy to it
	for (unsigned int r = 0; r < mat->Rows; r++)
		for (unsigned int c = 0; c < mat->Cols; c++)
			nmat->Val[c][r] = mat->Val[r][c];
	return nmat;
}

void umiMat_Print(umiMat_p mat)
{
	if (!mat) return;
	if (!(mat->Val && mat->Rows && mat->Cols)) return;
	unsigned int r, c;
	for (r = 0; r < mat->Rows; r++)
	{
		for (c = 0; c < mat->Cols; c++)
		{
			printf("%lf",mat->Val[r][c]);
			if (c < mat->Cols - 1) printf("\t");
		}
		printf("\n");
	}
	return;
}


#undef CheckMat
#undef CheckR
#undef CheckC
//to be continued


#ifdef __cplusplus
}
#endif // __cplusplus

//Thanks for reading.[bi xin xin]
