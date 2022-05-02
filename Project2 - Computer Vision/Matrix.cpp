// Project UID af1f95f547e44ca8ea88730dfb185559ds
#include <cassert>
#include "Matrix.h"

using namespace std;

// REQUIRES: mat points to a Matrix
//           0 < width && width <= MAX_MATRIX_WIDTH
//           0 < height && height <= MAX_MATRIX_HEIGHT
// MODIFIES: *mat
// EFFECTS:  Initializes *mat as a Matrix with the given width and height.
// NOTE:     Do NOT use new or delete here.
void Matrix_init(Matrix* mat, int width, int height) 
{
	//assert(0 <= width && width < MAX_MATRIX_WIDTH);
	//assert(0 <= height && height < MAX_MATRIX_HEIGHT);

	mat->height = height;
	mat->width = width;
}

// REQUIRES: mat points to a valid Matrix
// MODIFIES: os
// EFFECTS:  First, prints the width and height for the Matrix to os:
//             WIDTH [space] HEIGHT [newline]
//           Then prints the rows of the Matrix to os with one row per line.
//           Each element is followed by a space and each row is followed
//           by a newline. This means there will be an "extra" space at
//           the end of each line.
void Matrix_print(const Matrix* mat, std::ostream& os)
{
	os << mat->height << " " << mat->width << endl;

	for (int i = 0; i < Matrix_height(mat); i++)
	{
		for (int j = 0; j < Matrix_width(mat); j++)
		{
			os << *Matrix_at(mat, i, j) << " ";
		}
		os << "\n";
	}
}

// REQUIRES: mat points to an valid Matrix
// EFFECTS:  Returns the width of the Matrix.
int Matrix_width(const Matrix* mat) 
{
	return mat->width;
}

// REQUIRES: mat points to a valid Matrix
// EFFECTS:  Returns the height of the Matrix.
int Matrix_height(const Matrix* mat) 
{
	return mat->height;
}

// REQUIRES: mat points to a valid Matrix
//           ptr points to an element in the Matrix
// EFFECTS:  Returns the row of the element pointed to by ptr.
int Matrix_row(const Matrix* mat, const int* ptr)
{
	int numRows = ptr - mat->data;

	return(numRows / mat->width);
}

// REQUIRES: mat points to a valid Matrix
//           ptr point to an element in the Matrix
// EFFECTS:  Returns the column of the element pointed to by ptr.
int Matrix_column(const Matrix* mat, const int* ptr) 
{
	int numCols = ptr - mat->data;
	
	return(numCols % mat->width);
}

// REQUIRES: mat points to a valid Matrix
//           0 <= row && row < Matrix_height(mat)
//           0 <= column && column < Matrix_width(mat)
//
// MODIFIES: (The returned pointer may be used to modify an
//            element in the Matrix.)
// EFFECTS:  Returns a pointer to the element in the Matrix
//           at the given row and column.
	//return mat->data + (row * mat->width) + column;
int* Matrix_at(Matrix* mat, int row, int column) 
{
	//assert(0 <= row && row < mat->height);
	//assert(0 <= column && column < mat->width);

	return mat->data + (row * mat->width) + column;
}

// REQUIRES: mat points to a valid Matrix
//           0 <= row && row < Matrix_height(mat)
//           0 <= column && column < Matrix_width(mat)
//
// EFFECTS:  Returns a pointer-to-const to the element in
//           the Matrix at the given row and column.
const int* Matrix_at(const Matrix* mat, int row, int column) 
{
	//assert(0 <= row && row < mat->height);
	//assert(0 <= column && column < mat->width);

	const int *ptrLocation = &(mat->data[(row * mat->width) + column]);

	return ptrLocation;
}

// REQUIRES: mat points to a valid Matrix
// MODIFIES: *mat
// EFFECTS:  Sets each element of the Matrix to the given value.
void Matrix_fill(Matrix* mat, int value)
{
	for (int i = 0; i < Matrix_height(mat); i++)
	{
		for (int j = 0; j < Matrix_width(mat); j++)
		{
			*Matrix_at(mat, i, j) = value;
		}
	}
}

// REQUIRES: mat points to a valid Matrix
// MODIFIES: *mat
// EFFECTS:  Sets each element on the border of the Matrix to
//           the given value. These are all elements in the first/last
//           row or the first/last column.
void Matrix_fill_border(Matrix* mat, int value)
{
	for (int i = 0; i < Matrix_width(mat); i++)
	{
		*Matrix_at(mat, 0, i) = value;

		*Matrix_at(mat, Matrix_height(mat)-1, i) = value;
	}

	for (int j = 0; j < Matrix_height(mat); j++)
	{
		*Matrix_at(mat, j, 0) = value;

		*Matrix_at(mat, j, Matrix_width(mat) - 1) = value;
	}
}

// REQUIRES: mat points to a valid Matrix
// EFFECTS:  Returns the value of the maximum element in the Matrix
int Matrix_max(const Matrix* mat)
{
	int maxVal = mat->data[0];
	int width = mat->width;
	int height = mat->height;

	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < height; j++)
		{
			if (*Matrix_at(mat, i, j) > maxVal)
			{
				maxVal = *Matrix_at(mat, i, j);
			}
		}
	}
	return maxVal;
}

// REQUIRES: mat points to a valid Matrix
//           0 <= row && row < Matrix_height(mat)
//           0 <= column_start && column_end <= Matrix_width(mat)
//           column_start < column_end
// EFFECTS:  Returns the column of the element with the minimal value
//           in a particular region. The region is defined as elements
//           in the given row and between column_start (inclusive) and
//           column_end (exclusive).
//           If multiple elements are minimal, returns the column of
//           the leftmost one.
int Matrix_column_of_min_value_in_row(const Matrix* mat, int row, 
										int column_start, int column_end) 
{
	//assert(0 <= row && row < Matrix_height(mat));
	//assert(0 <= column_start && column_end < Matrix_width(mat));
	//assert(column_start < column_end);

	int minColVal = column_start;

	for (int i = column_start; i < column_end; i++)
	{
		if (*Matrix_at(mat, row, i) < *Matrix_at(mat, row, minColVal))
		{
			minColVal = i;
		}
	}
	return minColVal;
}

// REQUIRES: mat points to a valid Matrix
//           0 <= row && row < Matrix_height(mat)
//           0 <= column_start && column_end <= Matrix_width(mat)
//           column_start < column_end
// EFFECTS:  Returns the minimal value in a particular region. The region
//           is defined as elements in the given row and between
//           column_start (inclusive) and column_end (exclusive).
int Matrix_min_value_in_row(const Matrix* mat, int row, int column_start, int column_end) 
{
	assert(0 <= row && row < Matrix_height(mat));
	assert(0 <= column_start && column_end <= Matrix_width(mat));
	assert(column_start < column_end);

	int minVal = *Matrix_at(mat, row, column_start);

	for (int i = column_start; i < column_end; i++) 
	{
		if (*Matrix_at(mat, row, i) < minVal)
		{
			minVal = *Matrix_at(mat, row, i);
		}
	}
	return minVal;
}
