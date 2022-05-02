// Project UID af1f95f547e44c8ea88730dfb185559d

#include "Matrix.h"
#include "Matrix_test_helpers.h"
#include "unit_test_framework.h"
#include <sstream>

using std::ostringstream;
using namespace std;


// Here's a free test for you! Model yours after this one.
// Test functions have no interface and thus no RMEs, but
// add a comment like the one here to say what it is testing.
// -----
// Fills a 3x5 Matrix with a value and checks
// that Matrix_at returns that value for each element.
TEST(test_fill_basic) {
  Matrix *mat = new Matrix; // create a Matrix in dynamic memory

  const int width = 3;
  const int height = 5;
  const int value = 42;
  Matrix_init(mat, 3, 5);
  Matrix_fill(mat, value);

  for(int r = 0; r < height; ++r){
    for(int c = 0; c < width; ++c){
      ASSERT_EQUAL(*Matrix_at(mat, r, c), value);
    }
  }

  delete mat; // delete the Matrix
}

// ADD YOUR TESTS HERE
// You are encouraged to use any functions from Matrix_test_helpers.h as needed.
TEST(testMatixHeightWidth)
{
	//Test 1
	Matrix* mat = new Matrix;
	const int width = 5;
	const int height = 5;
	Matrix_init(mat, 5, 5);
	
	ASSERT_EQUAL(width, 5);
	ASSERT_EQUAL(height, 5);

	delete mat;

	//Test 2
	Matrix* mat1 = new Matrix;
	Matrix_init(mat1, 0, 0);
}
TEST(testMatrixRowCol)
{
	//TEST 1
	Matrix* mat = new Matrix;
	Matrix_init(mat, 3, 5);
	Matrix_fill(mat, 0);

	int expectedRow = 2;
	int* testPtr;
	for (int i = 0; i < Matrix_height(mat); i++)
	{
		for (int j = 0; j < Matrix_width(mat); j++)
		{
			testPtr = Matrix_at(mat, 2, 2);
			int actualRow = Matrix_row(mat, testPtr);
			ASSERT_EQUAL(expectedRow, actualRow);
		}
	}
	delete mat;

	//TEST 2
	Matrix* mat1 = new Matrix;
	Matrix_init(mat1, 10, 10);
	Matrix_fill(mat1, 1);

	int expectedCol = 7;
	int* testPtr1;
	for (int i = 0; i < Matrix_height(mat1); i++)
	{
		for (int j = 0; j < Matrix_width(mat1); j++)
		{
			testPtr1 = Matrix_at(mat1, 1, 7);
			int actualCol = Matrix_column(mat1, testPtr1);
			ASSERT_EQUAL(expectedCol, actualCol);
		}
	}
	delete mat1;

	//TEST 3
	Matrix* mat3 = new Matrix;
	Matrix_init(mat3, 1, 1);
	Matrix_fill(mat3, 255);

	int expectedCol3 = 0;
	int* testPtr3;
	
	for (int i = 0; i < Matrix_height(mat3); i++)
	{
		for (int j = 0; j < Matrix_width(mat3); j++)
		{
			testPtr3 = Matrix_at(mat3, 0, 0);
			int actualCol3 = Matrix_column(mat3, testPtr3);
			ASSERT_EQUAL(expectedCol3, actualCol3);
		}
	}
	delete mat3;


}
TEST(testMatrixPrint)
{
	//NEED TO FIX
	Matrix* mat = new Matrix;
	ostringstream expectedOutput;

	Matrix_init(mat, 5, 5);
	for (int row = 0; row < Matrix_height(mat); row++)
	{
		for (int col = 0; col < Matrix_width(mat); col++)
		{
			*Matrix_at(mat, row, col) = 10;
		}
	}
	expectedOutput << "5 5\n"
		<< "10 10 10 10 10 \n"
		<< "10 10 10 10 10 \n"
		<< "10 10 10 10 10 \n"
		<< "10 10 10 10 10 \n"
		<< "10 10 10 10 10 \n";

	ostringstream actualOutput;
	Matrix_print(mat, actualOutput);

	ASSERT_EQUAL(expectedOutput.str(), actualOutput.str());

}

TEST(testMatrixMax)
{
	//TEST 1
	Matrix* mat1 = new Matrix;
	Matrix_init(mat1, 10, 10);
	Matrix_fill(mat1, 0);

	int maxVal = 45;
	for (int row = 0; row < Matrix_height(mat1); row++)
	{
		for (int col = 0; col < Matrix_width(mat1); col++)
		{
			*Matrix_at(mat1, 9, 9) = maxVal;
		}
	}
	ASSERT_EQUAL(45, Matrix_max(mat1));

	delete mat1;

	//TEST 2
	Matrix* mat2 = new Matrix;
	Matrix_init(mat2, 1, 1);
	Matrix_fill(mat2, 100);
	
	ASSERT_EQUAL(100, Matrix_max(mat2));

	delete mat2;

	//TEST 3
	Matrix* mat3 = new Matrix;
	Matrix_init(mat3, 5, 3);
	Matrix_fill(mat3, 0);
	int maxVal1 = 255;

	for (int row = 0; row < Matrix_height(mat1); row++)
	{
		for (int col = 0; col < Matrix_width(mat1); col++)
		{
			*Matrix_at(mat1, 0, 0) = maxVal1;
		}
	}
	ASSERT_EQUAL(0, Matrix_max(mat3));

	delete mat3;
}

TEST(testMatrixFillBorder)
{
	//TEST 1
	Matrix* mat1 = new Matrix;
	Matrix_init(mat1, 1, 1);
	Matrix_fill_border(mat1, 5);

	ASSERT_EQUAL(*Matrix_at(mat1, 0, 0), 5);

	delete mat1;

	//TEST 2
	Matrix* mat2 = new Matrix;
	Matrix_init(mat2, 2, 4);
	Matrix_fill_border(mat2, 10);

	for (int i = 0; i < Matrix_height(mat2); i++)
	{
		for (int j = 0; j < Matrix_width(mat2); j++)
		{
			ASSERT_EQUAL(*Matrix_at(mat2, i, j), 10);
		}
	}

	delete mat2;

	//TEST 3
	Matrix* mat3 = new Matrix;
	Matrix_init(mat3, 5, 5);
	Matrix_fill_border(mat3, 255);

	ASSERT_EQUAL(*Matrix_at(mat3, 0, 0), 255);
	ASSERT_EQUAL(*Matrix_at(mat3, 4, 0), 255);
	ASSERT_EQUAL(*Matrix_at(mat3, 0, 4), 255);
	ASSERT_EQUAL(*Matrix_at(mat3, 4, 4), 255);

	delete mat3;
}

TEST(testMatrix_column_of_min_value_in_row)
{
	//TEST 1
	Matrix* mat1 = new Matrix;
	Matrix_init(mat1, 1, 1);
	*Matrix_at(mat1, 0, 0) = 3;

	int expectedVal = 0;
	int actualMinVal = Matrix_column_of_min_value_in_row(mat1, 0, 0, 0);
	//NEED TO FIX
	ASSERT_EQUAL(expectedVal, actualMinVal);

	delete mat1;

	//TEST 2
	Matrix* mat2 = new Matrix;
	Matrix_init(mat2, 5, 5);
	int expectedVal1 = 0;
	int actualMinVal1;

	for (int i = 0; i < Matrix_height(mat2); i++)
	{
		for (int j = 0; j < Matrix_width(mat2); j++)
		{
			*Matrix_at(mat2, i, j) = 255;
			actualMinVal1 = Matrix_column_of_min_value_in_row(mat2, i,0, 4);

		}
	}
	ASSERT_EQUAL(expectedVal1, actualMinVal1);

	delete mat2;

	//TEST 3
	Matrix* mat3 = new Matrix;
	Matrix_init(mat3, 10, 10);
	int expectedVal2 = 9;
	int actualMinVal2;

	for (int i = 0; i < Matrix_height(mat2); i++)
	{
		for (int j = 0; j < Matrix_width(mat2); j++)
		{
			*Matrix_at(mat2, i, j) = 255;
		}
	}

	*Matrix_at(mat3, 9, 9) = 0;
	
	for (int i = 0; i < Matrix_height(mat2); i++)
	{
		for (int j = 0; j < Matrix_width(mat2); j++)
		{
			actualMinVal2 = Matrix_column_of_min_value_in_row(mat3, i, 9, 9);
		}
	}
	ASSERT_EQUAL(expectedVal2, actualMinVal2);

	delete mat3;

}

TEST(testMatrix_min_val_in_row)
{
	//TEST 1
	Matrix *mat1 = new Matrix;
	Matrix_init(mat1, 1, 1);
	*Matrix_at(mat1, 0, 0) = 5;

	int expectedVal = 5;
	int actualVal = Matrix_min_value_in_row(mat1, 0, 0, 0);
	ASSERT_EQUAL(expectedVal, actualVal);
	
	delete mat1;

	//TEST 2
	Matrix* mat2 = new Matrix;
	Matrix_init(mat2, 3, 4);
	int expectedMinVal1 = 100;
	int actualMinVal1;

	for (int row = 0; row < Matrix_height(mat2); row++)
	{
		for (int col = 0; col < Matrix_width(mat2); col++)
		{
			*Matrix_at(mat2, row, col) = 100;
		}
	}
	*Matrix_at(mat2, 1, 1) = 0;

	for (int row = 0; row < Matrix_height(mat2); row++)
	{
		for (int col = 0; col < Matrix_width(mat2); col++)
		{
			actualMinVal1 = Matrix_min_value_in_row(mat2, row, 0, 3);
		}
	}

	ASSERT_EQUAL(expectedMinVal1, actualMinVal1);

	delete mat2;
}

TEST_MAIN() // Do NOT put a semicolon here
