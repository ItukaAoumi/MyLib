#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <math.h>
#include "VectorMatrix.h"

//Can be used in cpp.
#ifdef __cplusplus
extern "C" {
#endif // __cplusplus


//definition of data structure
struct umiVector
{
	double * Val;
	unsigned int Dims;
};

umiVec_p umiVec_New(const unsigned int dims)
{
	if (!dims) return 0;	//check dimensions is 0 or not
	umiVec_p nvec = (umiVec_p) calloc(1, sizeof(struct umiVector));	if (!nvec) return 0;	//create a new vector
	nvec->Val = (double *) calloc(dims, sizeof(double));	//create value
	if (!nvec->Val) {free(nvec); return 0;}	//allocation failure
	nvec->Dims = dims;	//edit dimensions
	return nvec;
}

#define CheckVec if (!vec) return 0; if (!(vec->Val && vec->Dims)) return 0;
#define CheckDim if (dim >= vec->Dims) return 0;

umiVec_p umiVec_Copy(const umiVec_p vec)
{
	CheckVec
	umiVec_p nvec = umiVec_New(vec->Dims);	if (!nvec) return 0;	//create a new vector
	for (unsigned int i = 0; i < vec->Dims; i++) nvec->Val[i] = vec->Val[i];	//copy the value
	return nvec;
}

umiVec_p umiVec_Reset(umiVec_p vec, const unsigned int dims)
{
	if (!(vec && dims)) return 0;
	if (dims == vec->Dims) return vec;
	double * tmp = (double *) realloc(vec->Val, sizeof(double) * dims);	//reset value
	if (tmp) vec->Val = tmp;
	else return 0;
	for (unsigned int i = vec->Dims; i < dims; i++) vec->Val[i] = 0;	//init
	vec->Dims = dims;	//edit dimensions
	return vec;
}

umiVec_p umiVec_Clr(umiVec_p vec)
{
	if (!vec) return 0;
	if (vec->Val) free(vec->Val);
	vec->Val = vec->Dims = 0;
	return vec;
}

char umiVec_Del(umiVec_p * vec)
{
	if (!vec) return 0;
	if (!(*vec)) return 0;
	free(umiVec_Clr(*vec));
	*vec = 0;
	return 1;
}

double * umiVec_Val(const umiVec_p vec)
{
	if (!vec) return 0;
	return vec->Val;
}
unsigned int umiVec_Dims(const umiVec_p vec)
{
	if (!vec) return 0;
	return vec->Dims;
}

umiVec_p umiVec_EditVal(const umiVec_p vec, const unsigned int dim, const double val)
{
	CheckVec	CheckDim
	vec->Val[dim] = val;
	return vec;
}

umiVec_p umiVec_EditValFromA(const umiVec_p vec, const double * source)
{
	CheckVec
	if (!source) return 0;
	memcpy(vec->Val, source, sizeof(double) * vec->Dims);
	return vec;
}

double umiVec_GetVal(const umiVec_p vec, const unsigned int dim)
{
	CheckVec	CheckDim
	return vec->Val[dim];
}

double * umiVec_GetValToA(const umiVec_p vec, double * dest)
{
	CheckVec
	if (!dest) return 0;
	memcpy(dest, vec->Val, sizeof(double) * vec->Dims);
	return dest;
}

//Get the length of a vector.
double umiVec_Len(const umiVec_p vec)
{
	CheckVec
	if (vec->Dims == 1) return *vec->Val;
	double sum = 0;
	for (unsigned int i = 0; i < vec->Dims; i++)
		sum += vec->Val[i] * vec->Val[i];
	return sqrt(sum);
}

umiVec_p umiVec_InsDim(const umiVec_p vec, const unsigned int dim)
{
	if (!vec) return 0;
	if (dim > vec->Dims) return 0;
	//add one at tail
	double * tmp = (double *) realloc(vec->Val, sizeof(double) * (vec->Dims + 1));
	if (tmp) vec->Val = tmp;
	else return 0;
	vec->Dims++;
	for (unsigned int i = vec->Dims - 1; i > dim; i--) vec->Val[i] = vec->Val[i - 1];	//move elements
	vec->Val[dim] = 0;
	return vec;
}

umiVec_p umiVec_DelDim(const umiVec_p vec, const unsigned int dim)
{
	CheckVec	CheckDim
	for (unsigned int i = dim; i < vec->Dims; i++) vec->Val[i - 1] = vec->Val[i];	//move elements
	//delete one at tail
	vec->Val = (double *) realloc(vec->Val, sizeof(double) * (vec->Dims - 1));
	vec->Dims--;
	return vec;
}

//Reverse a vector. x[i]=-x[i]
umiVec_p umiVec_Neg(umiVec_p vec, const unsigned char preserve)
{
	CheckVec
	umiVec_p ans = umiVec_New(vec->Dims);	if (!ans) return 0;	//create a new vector
	for (unsigned int i = 0; i < vec->Dims; i++) ans->Val[i] = -vec->Val[i];
	if (!preserve) umiVec_Del(&vec);
	return ans;
}

#define CheckLRV if (!(vecl && vecr)) return 0; if (!(vecl->Val && vecl->Dims && vecr->Val && vecr->Dims)) return 0;

/*
Add two vectors and put at a new one.
params:
vecl: left vector
vecr: right vector
preserve: preserve (1) or not (0) the old one.
Return the new vector.
*/
umiVec_p umiVec_Add(umiVec_p vecl, umiVec_p vecr, const unsigned char preserve)
{
	CheckLRV
	if (vecl->Dims != vecr->Dims) return 0;
	umiVec_p ans = umiVec_New(vecl->Dims);	if (!ans) return 0;	//create a new vector to store the result
	//add two vectors
	for (unsigned int i = 0; i < vecl->Dims; i++)
		ans->Val[i] = vecl->Val[i] + vecr->Val[i];
	if (!preserve) {umiVec_Del(&vecl); umiVec_Del(&vecr);}	//delete old
	return ans;
}

umiVec_p umiVec_Sub(umiVec_p vecl, umiVec_p vecr, const unsigned char preserve)
{
	CheckLRV
	if (vecl->Dims != vecr->Dims) return 0;
	umiVec_p ans = umiVec_New(vecl->Dims);	if (!ans) return 0;	//create a new vector to store the result
	//substrate two vectors
	for (unsigned int i = 0; i < vecl->Dims; i++)
		ans->Val[i] = vecl->Val[i] - vecr->Val[i];
	if (!preserve) {umiVec_Del(&vecl); umiVec_Del(&vecr);}	//delete old
	return ans;
}

umiVec_p umiVec_Mul(umiVec_p vec, const double num, const unsigned char preserve)
{
	CheckVec
	umiVec_p ans = umiVec_New(vec->Dims);	if (!ans) return 0;	//create a new vector
	for (unsigned int i = 0; i < vec->Dims; i++)
		ans->Val[i] = vec->Val[i] * num;
	if (!preserve) umiVec_Del(&vec);	//delete old
	return ans;
}

double umiVec_DotProd(umiVec_p vecl, umiVec_p vecr, const unsigned char preserve)
{
	CheckLRV
	if (vecl->Dims != vecr->Dims) return 0;
	double sum = 0;
	for (unsigned int i = 0; i < vecl->Dims; i++)
		sum += vecl->Val[i] * vecr->Val[i];
	if (!preserve) {umiVec_Del(&vecl); umiVec_Del(&vecr);}	//delete old
	return sum;
}

umiVec_p umiVec_DirectProd(umiVec_p vecl, umiVec_p vecr, const unsigned char preserve)
{
	CheckLRV
	if (vecl->Dims != vecr->Dims) return 0;
	umiVec_p ans = umiVec_New(vecl->Dims);	if (!ans) return 0;	//create a new vector
	for (unsigned int i = 0; i < vecl->Dims; i++)
		ans->Val[i] = vecl->Val[i] * vecr->Val[i];
	if (!preserve) {umiVec_Del(&vecl); umiVec_Del(&vecr);}	//delete old
	return ans;
}

umiVec_p umiVec_TensorProd(umiVec_p vecl, umiVec_p vecr, const unsigned char preserve)
{
	CheckLRV
	umiVec_p ans = umiVec_New(vecl->Dims * vecr->Dims);	if (!ans) return 0;	//create a new vector
	unsigned int i, j;
	for (i = 0; i < vecl->Dims; i++)
		for (j = 0; j < vecr->Dims; j++)
			ans->Val[i * vecr->Dims + j] = vecl->Val[i] * vecr->Val[j];
	if (!preserve) {umiVec_Del(&vecl); umiVec_Del(&vecr);}	//delete old
	return ans;
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

char umiVec_Print(const umiVec_p vec)
{
	CheckVec
	for (unsigned int i = 0; i < vec->Dims; i++)
	{
		printf_s("%lf", vec->Val[i]);
		if (i < vec->Dims - 1) printf_s("\t");
	}
	printf_s("\n");
	return 1;
}
//to be continued

#undef CheckVec
#undef CheckDim
#undef CheckLR


//definition of data structure
struct umiMatrix
{
	double * * Val;
	unsigned int Rows, Cols;
};

umiMat_p umiMat_New(const unsigned int rows, const unsigned int cols)
{
	if (!(rows && cols)) return 0;	//check if rows or cols is 0
	umiMat_p nmat = (umiMat_p) calloc(1, sizeof(struct umiMatrix));	if (!nmat) return 0;	//create a new matrix
	nmat->Val = (double * *) calloc(rows, sizeof(double *));	//create rows
	if (!nmat->Val) {free(nmat); return 0;}	//allocation failure
	//create columns for each row
	for (unsigned int r = 0; r < rows; r++)
	{
		nmat->Val[r] = (double *) calloc(cols, sizeof(double));
		//allocation failure
		if (!nmat->Val[r])
		{
			for (unsigned int i = 0; i < r; i++) free(nmat->Val[i]);
			free(nmat->Val);
			free(nmat);
			return 0;
		}
	}
	//edit rows and cols
	nmat->Rows = rows;	nmat->Cols = cols;
	return nmat;
}

#define CheckMat if (!mat) return 0; if (!(mat->Val && mat->Rows && mat->Cols)) return 0;
#define CheckR if (row >= mat->Rows) return 0;
#define CheckC if (col >= mat->Cols) return 0;

umiMat_p umiMat_Copy(const umiMat_p mat)
{
	CheckMat
	umiMat_p nmat = umiMat_New(mat->Rows, mat->Cols);	if (!nmat) return 0;	//create a new matrix
	unsigned int r, c;
	//copy the value
	for (r = 0; r < mat->Rows; r++)
		for (c = 0; c < mat->Cols; c++)
			nmat->Val[r][c] = mat->Val[r][c];
	return nmat;
}

umiMat_p umiMat_NewIdMat(const unsigned int rows, const double val)
{
	if (!rows) return 0;	//checking input
	umiMat_p nmat = umiMat_New(rows, rows);	if (!nmat) return 0;	//create a new matrix
	for (unsigned int i = 0; i < rows; i++) nmat->Val[i][i] = val;
	return nmat;
}

umiMat_p umiMat_Reset(umiMat_p * mat, const unsigned int rows, const unsigned int cols)
{
	//checking input
	if (!(mat && rows && cols)) return 0;
	if (!(*mat)) return 0;
	if (!(*mat)->Val) return 0;
	if ((*mat)->Rows == rows && (*mat)->Cols == cols) return 0;
	unsigned int r, c;
	umiMat_p tmp = umiMat_New(rows, cols);	if (!tmp) return 0;	//create a temp.
	//copy
	for (r = 0; r < (*mat)->Rows && r < rows; r++)
		for (c = 0; c < (*mat)->Cols && c < cols; c++)
			tmp->Val[r][c] = (*mat)->Val[r][c];
	//delete old
	umiMat_Del(mat);
	*mat = tmp;
	return *mat;
}

umiMat_p umiMat_Clr(umiMat_p mat)
{
	if (!mat) return 0;
	if (mat->Val)
	{
		for (unsigned int r = 0; r < mat->Rows; r++) free(mat->Val[r]);
		free(mat->Val);
	}
	mat->Val = mat->Rows = mat->Cols = 0;
	return mat;
}

char umiMat_Del(umiMat_p * mat)
{
	if (!mat) return 0;
	if (!(*mat)) return 0;
	free(umiMat_Clr(*mat));
	*mat = 0;
	return 1;
}

double * * umiMat_Val(const umiMat_p mat)
{
	if (!mat) return 0;
	return mat->Val;
}
unsigned int umiMat_Rows(const umiMat_p mat)
{
	if (!mat) return 0;
	return mat->Rows;
}
unsigned int umiMat_Cols(const umiMat_p mat)
{
	if (!mat) return 0;
	return mat->Cols;
}

umiMat_p umiMat_EditVal(const umiMat_p mat, const unsigned int row, const unsigned int col, const double val)
{
	CheckMat CheckR CheckC
	mat->Val[row][col] = val;	//*(*(mat->Val + row) + col) = val;
	return mat;
}

umiMat_p umiMat_EditRowFromA(const umiMat_p mat, const unsigned int row, const double * source)
{
	CheckMat CheckR
	for (unsigned int c = 0; c < mat->Cols; c++) mat->Val[row][c] = source[c];
	return mat;
}

umiMat_p umiMat_EditColFromA(const umiMat_p mat, const unsigned int col, const double * source)
{
	CheckMat CheckC
	for (unsigned int r = 0; r < mat->Rows; r++) mat->Val[r][col] = source[r];
	return mat;
}

umiMat_p umiMat_EditRowFromV(const umiMat_p mat, const unsigned int row, const umiVec_p rowvec)
{
	CheckMat CheckR
	for (unsigned int c = 0; c < mat->Cols && c < rowvec->Dims; c++) mat->Val[row][c] = rowvec->Val[c];
	return mat;
}

umiMat_p umiMat_EditColFromV(const umiMat_p mat, const unsigned int col, const umiVec_p colvec)
{
	CheckMat CheckC
	for (unsigned int r = 0; r < mat->Rows && r < colvec->Dims; r++) mat->Val[r][col] = colvec->Val[r];
	return mat;
}

double umiMat_GetVal(const umiMat_p mat, const unsigned int row, const unsigned int col)
{
	CheckMat CheckR CheckC
	return mat->Val[row][col];	//return *(*(mat->Val + row) + col);
}

double * umiMat_GetRowToA(const umiMat_p mat, const unsigned int row, double * dest)
{
	CheckMat CheckR
	if (!dest) return 0;
	for (unsigned int c = 0; c < mat->Cols; c++) dest[c] = mat->Val[row][c];
	return dest;
}

double * umiMat_GetColToA(const umiMat_p mat, const unsigned int col, double * dest)
{
	CheckMat CheckC
	if (!dest) return 0;
	for (unsigned int r = 0; r < mat->Rows; r++) dest[r] = mat->Val[r][col];
	return dest;
}

umiVec_p umiMat_GetRowToV(const umiMat_p mat, const unsigned int row)
{
	CheckMat CheckR
	umiVec_p rowvec = umiVec_New(mat->Cols);	if (!rowvec) return 0;
	for (unsigned int c = 0; c < mat->Cols; c++) rowvec->Val[c] = mat->Val[row][c];
	return rowvec;
}

umiVec_p umiMat_GetColToV(const umiMat_p mat, const unsigned int col)
{
	CheckMat CheckC
	umiVec_p colvec = umiVec_New(mat->Rows);	if (!colvec) return 0;
	for (unsigned int r = 0; r < mat->Rows; r++) colvec->Val[r] = mat->Val[r][col];
	return colvec;
}

/*Matrix Operations*/

umiMat_p umiMat_MulRow(const umiMat_p mat, const unsigned int row, const double mul)
{
	CheckMat CheckR
	for (unsigned int c = 0; c < mat->Cols; c++) mat->Val[row][c] *= mul;
	return mat;
}

umiMat_p umiMat_MulCol(const umiMat_p mat, const unsigned int col, const double mul)
{
	CheckMat CheckC
	for (unsigned int r = 0; r < mat->Rows; r++) mat->Val[r][col] *= mul;
	return mat;
}

void swapdbl(double * num1, double * num2)
{
	if (!(num1 && num2)) return;
	if (num1 == num2) return;
	double temp = *num1;
	*num1 = *num2;
	*num2 = temp;
	return;
}

umiMat_p umiMat_SwapRow(const umiMat_p mat, const unsigned int row1, const unsigned int row2)
{
	CheckMat
	if (row1 >= mat->Rows || row2 >= mat->Rows) return 0;
	if (row1 == row2) return mat;
	for (unsigned int c = 0; c < mat->Cols; c++) swapdbl(mat->Val[row1] + c, mat->Val[row2] + c);
	return mat;
}

umiMat_p umiMat_SwapCol(const umiMat_p mat, const unsigned int col1, const unsigned int col2)
{
	CheckMat
	if (col1 >= mat->Cols || col2 >= mat->Cols) return 0;
	if (col1 == col2) return mat;
	for (unsigned int r = 0; r < mat->Rows; r++) swapdbl(mat->Val[r] + col1, mat->Val[r] + col2);
	return mat;
}

umiMat_p umiMat_AddRow(const umiMat_p mat, const unsigned int row1, const unsigned int row2, const double mul)
{
	CheckMat
	if (row1 >= mat->Rows || row2 >= mat->Rows) return 0;
	if (row1 == row2) return mat;
	for (unsigned int c = 0; c < mat->Cols; c++) mat->Val[row1][c] += mat->Val[row2][c] * mul;
	return mat;
}

umiMat_p umiMat_AddCol(const umiMat_p mat, const unsigned int col1, const unsigned int col2, const double mul)
{
	CheckMat
	if (col1 >= mat->Cols || col2 >= mat->Cols) return 0;
	if (col1 == col2) return mat;
	for (unsigned int r = 0; r < mat->Rows; r++) mat->Val[r][col1] += mat->Val[r][col2] * mul;
	return mat;
}

umiMat_p umiMat_SortByRow(umiMat_p mat, const unsigned int keyrow, const unsigned char order)
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
	return mat;
}

umiMat_p umiMat_SortByCol(umiMat_p mat, const unsigned int keycol, const unsigned char order)
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
	return mat;
}

umiMat_p umiMat_InsRow(umiMat_p mat, const unsigned int row)
{
	if (!mat) return mat;
	if (row > mat->Rows) return mat;
	//add a row at tail
	double * * tmp = (double * *) realloc(mat->Val, sizeof(double *) * (mat->Rows + 1));
	if (tmp) mat->Val = tmp;
	else return mat;
	mat->Rows++;
	for (unsigned int r = mat->Rows - 1; r > row; r--) mat->Val[r] = mat->Val[r - 1];	//move row elements
	mat->Val[row] = (double *) calloc(mat->Cols, sizeof(double));
	return mat;
}

umiMat_p umiMat_InsCol(umiMat_p mat, const unsigned int col)
{
	if (!mat) return mat;
	if (col > mat->Cols) return mat;
	//add a column at tail
	unsigned int r, c;	double * tmp;
	for (r = 0; r < mat->Rows; r++)
	{
		tmp = (double *) realloc(mat->Val[r], sizeof(double) * (mat->Cols + 1));
		if (tmp) mat->Val[r] = tmp;
		else return mat;
	}
	mat->Cols++;
	//move column elements
	for (r = 0; r < mat->Rows; r++)
	{
		for (c = mat->Cols - 1; c > col; c--)
			mat->Val[r][c] = mat->Val[r][c - 1];
		mat->Val[r][col] = 0;
	}
	return mat;
}

umiMat_p umiMat_DelRow(umiMat_p mat, const unsigned int row)
{
	CheckMat CheckR
	unsigned int r, c;
	for (r = row + 1; r < mat->Rows; r++)
		for (c = 0; c < mat->Cols; c++)
			mat->Val[r - 1][c] = mat->Val[r][c];
	free(mat->Val[mat->Rows - 1]);
	mat->Val = (double * *) realloc(mat->Val, sizeof(double *) * (mat->Rows - 1));
	mat->Rows--;
	return mat;
}

umiMat_p umiMat_DelCol(umiMat_p mat, const unsigned int col)
{
	CheckMat CheckC
	unsigned int r, c;
	for (r = 0; r < mat->Rows; r++)
	{
		for (c = col + 1; c < mat->Cols; c++)
			mat->Val[r][c - 1] = mat->Val[r][c];
		mat->Val[r] = (double *) realloc(mat->Val[r], sizeof(double) * (mat->Cols - 1));
	}
	mat->Cols--;
	return mat;
}

umiMat_p umiMat_Neg(umiMat_p mat, const unsigned char preserve)
{
	CheckMat
	umiMat_p ans = umiMat_New(mat->Rows, mat->Cols);	if (!ans) return 0;	//create a new matrix
	unsigned int r, c;
	for (r = 0; r < mat->Rows; r++)
		for (c = 0; c < mat->Cols; c++)
			ans->Val[r][c] = -mat->Val[r][c];
	if (!preserve) umiMat_Del(&mat);
	return ans;
}

umiMat_p umiMat_Trans(umiMat_p mat, const unsigned char preserve)
{
	CheckMat
	umiMat_p ans = umiMat_New(mat->Cols, mat->Rows);	if (!ans) return 0;	//create a new matrix
	//copy to it
	for (unsigned int r = 0; r < mat->Rows; r++)
		for (unsigned int c = 0; c < mat->Cols; c++)
			ans->Val[c][r] = mat->Val[r][c];
	if (!preserve) umiMat_Del(&mat);	//delete old
	return ans;
}

#define CheckLRM if (!(matl && matr)) return 0;\
if (!(matl->Val && matl->Rows && matl->Cols)) return 0;\
if (!(matr->Val && matr->Rows && matr->Cols)) return 0;

umiMat_p umiMat_Add(umiMat_p matl, umiMat_p matr, const unsigned char preserve)
{
	CheckLRM
	if (matl->Rows != matr->Rows || matl->Cols != matr->Cols) return 0;
	umiMat_p ans = umiMat_New(matl->Rows, matl->Cols);	if (!ans) return 0;	//create a new matrix to store the result
	//add two matrix
	unsigned int r,c;
	for (r = 0; r < matl->Rows; r++)
		for (c = 0; c < matl->Cols; c++)
			ans->Val[r][c] = matl->Val[r][c] + matr->Val[r][c];
	if (!preserve) {umiMat_Del(&matl); umiMat_Del(&matr);}	//delete old
	return ans;
}

umiMat_p umiMat_Sub(umiMat_p matl, umiMat_p matr, const unsigned char preserve)
{
	CheckLRM
	if (matl->Rows != matr->Rows || matl->Cols != matr->Cols) return 0;
	umiMat_p ans = umiMat_New(matl->Rows, matl->Cols);	if (!ans) return 0;	//create a new matrix to store the result
	//sub
	unsigned int r,c;
	for (r = 0; r < matl->Rows; r++)
		for (c = 0; c < matl->Cols; c++)
			ans->Val[r][c] = matl->Val[r][c] - matr->Val[r][c];
	if (!preserve) {umiMat_Del(&matl); umiMat_Del(&matr);}	//delete old
	return ans;
}

umiMat_p umiMat_Mul(umiMat_p mat, const double num, const unsigned char preserve)
{
	CheckMat
	umiMat_p ans = umiMat_New(mat->Rows, mat->Cols);	if (!ans) return 0;	//create a new matrix
	//multiply
	unsigned int r,c;
	for (r = 0; r < mat->Rows; r++)
		for (c = 0; c < mat->Cols; c++)
			ans->Val[r][c] = mat->Val[r][c] * num;
	if (!preserve) umiMat_Del(&mat);	//delete old
	return ans;
}

umiMat_p umiMat_CrossProd(umiMat_p matl, umiMat_p matr, const unsigned char preserve)
{
	CheckLRM
	if (matl->Cols != matr->Rows) return 0;
	umiMat_p ans = umiMat_New(matl->Rows, matr->Cols);	if (!ans) return 0;	//create a new matrix
	//cross product
	unsigned int r, c, i;
	for (r = 0; r < matl->Rows; r++)
		for (c = 0; c < matr->Cols; c++)
			for (i = 0; i < matl->Cols; i++)
				ans->Val[r][c] += matl->Val[r][i] * matr->Val[i][c];
	if (!preserve) {umiMat_Del(&matl); umiMat_Del(&matr);}	//delete old
	return ans;
}

umiMat_p umiMat_DirectProd(umiMat_p matl, umiMat_p matr, const unsigned char preserve)
{
	CheckLRM
	if (matl->Rows != matr->Rows || matl->Cols != matr->Cols) return 0;
	umiMat_p ans = umiMat_New(matl->Rows, matl->Cols);	if (!ans) return 0;	//create a new matrix
	//direct product
	unsigned int r, c;
	for (r = 0; r < matl->Rows; r++)
		for (c = 0; c < matl->Cols; c++)
			ans->Val[r][c] = matl->Val[r][c] * matr->Val[r][c];
	if (!preserve) {umiMat_Del(&matl); umiMat_Del(&matr);}	//delete old
	return ans;
}

umiMat_p umiMat_TensorProd(umiMat_p matl, umiMat_p matr, const unsigned char preserve)
{
	CheckLRM
	umiMat_p ans = umiMat_New(matl->Rows * matr->Rows, matl->Cols * matr->Cols);	if (!ans) return 0;	//create a new matrix
	//tensor product
	unsigned int lr, lc, rr, rc;
	for (lr = 0; lr < matl->Rows; lr++)
		for (lc = 0; lc < matl->Cols; lc++)
			for (rr = 0; rr < matr->Rows; rr++)
				for (rc = 0; rc < matr->Cols; rc++)
					ans->Val[lr * matr->Rows + rr][lc * matr->Cols + rc] = matl->Val[lr][lc] * matr->Val[rr][rc];
	if (!preserve) {umiMat_Del(&matl); umiMat_Del(&matr);}	//delete old
	return ans;
}
/////START FROM HERE
umiMat_p umiMat_RowTrans(const umiMat_p mat);

umiMat_p umiMat_ColTrans(const umiMat_p mat);

char umiMat_Print(const umiMat_p mat)
{
	CheckMat
	unsigned int r, c;
	for (r = 0; r < mat->Rows; r++)
	{
		for (c = 0; c < mat->Cols; c++)
		{
			printf("%lf",mat->Val[r][c]);
			if (c < mat->Cols - 1) printf(", ");
		}
		printf(";\n");
	}
	return 1;
}
//to be continued

#undef CheckMat
#undef CheckR
#undef CheckC


#ifdef __cplusplus
}
#endif // __cplusplus

//Thanks for reading.[bi xin xin]
