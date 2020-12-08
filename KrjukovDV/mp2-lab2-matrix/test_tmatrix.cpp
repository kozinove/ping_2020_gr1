#include "utmatrix.h"

#include <gtest.h>

TEST(TMatrix, can_create_matrix_with_positive_length)
{
  ASSERT_NO_THROW(TMatrix<int> m(5));
}

TEST(TMatrix, cant_create_too_large_matrix)
{
  ASSERT_ANY_THROW(TMatrix<int> m(MAX_MATRIX_SIZE + 1));
}

TEST(TMatrix, throws_when_create_matrix_with_negative_length)
{
  ASSERT_ANY_THROW(TMatrix<int> m(-5));
}

TEST(TMatrix, can_create_copied_matrix)
{
  TMatrix<int> m(5);

  ASSERT_NO_THROW(TMatrix<int> m1(m));
}

TEST(TMatrix, copied_matrix_is_equal_to_source_one)
{
	TMatrix<int> m(10), m1(m);
	EXPECT_EQ(m, m1);
}

TEST(TMatrix, copied_matrix_has_its_own_memory)
{
	TMatrix<int> m(10), m1(m);
	EXPECT_NE(&m, &m1);
}

TEST(TMatrix, can_get_size)
{
	TMatrix<int> m(5);
	EXPECT_EQ(5, m.GetSize());
}

TEST(TMatrix, can_set_and_get_element)
{
	TMatrix<int> m(4);
	m[0][0] = 4;

	EXPECT_EQ(4, m[0][0]);
}

TEST(TMatrix, throws_when_set_element_with_negative_index)
{
	TMatrix<int> m(4);
	ASSERT_ANY_THROW(m[-2][3] = 5);
}

TEST(TMatrix, throws_when_set_element_with_too_large_index)
{
	TMatrix<int> m(4);
	ASSERT_ANY_THROW(m[2][7] = 5);
}

TEST(TMatrix, can_assign_matrix_to_itself)
{
	TMatrix<int> m(5);
	ASSERT_NO_THROW(m = m);
}

TEST(TMatrix, can_assign_matrices_of_equal_size)
{
	const int size = 4;
	TMatrix<int> m1(size), m2(size);
	ASSERT_NO_THROW(m2 = m1);
}

TEST(TMatrix, assign_operator_change_matrix_size)
{
	TMatrix<int> m1(4), m2(2);
	m2 = m1;
	EXPECT_EQ(4, m2.GetSize());
}

TEST(TMatrix, can_assign_matrices_of_different_size)
{
	TMatrix<int> m1(4), m2(2);
	ASSERT_NO_THROW(m2 = m1);
}

TEST(TMatrix, compare_equal_matrices_return_true)
{
	const int size = 5;
	TMatrix<int> m1(size), m2(size);
	for (int i = 0; i < size; i++)
		for (int j = i; j < size; j++)
			m1[i][j] = m2[i][j] = i + j;
	EXPECT_EQ(m1, m2);
}

TEST(TMatrix, compare_matrix_with_itself_return_true)
{
	TMatrix<int> m(3);
	EXPECT_EQ(m, m);
}

TEST(TMatrix, matrices_with_different_size_are_not_equal)
{
	const int size1 = 3, size2 = 2;
	TMatrix<int> m1(size1), m2(size2);
	EXPECT_NE(m1, m2);
}

TEST(TMatrix, can_add_matrices_with_equal_size)
{
	const int size = 5;
	TMatrix<int> m1(size), m2(size), m3(size);
	for (int i = 0; i < size; i++)
		for (int j = i; j < size; j++)
		{
			m2[i][j] = (i + 2) * j;
			m3[i][j] = i * 3 + j;
			m1[i][j] = m2[i][j] + m3[i][j];

		}
	EXPECT_EQ(m1, m2 + m3);
}

TEST(TMatrix, cant_add_matrices_with_not_equal_size)
{
	TMatrix<int> m1(4), m2(2);
	ASSERT_ANY_THROW(m1 + m2);
}

TEST(TMatrix, can_subtract_matrices_with_equal_size)
{
	const int size = 5;
	TMatrix<int> m1(size), m2(size), m3(size);
	for (int i = 0; i < size; i++)
		for (int j = i; j < size; j++)
		{
			m2[i][j] = (i + 2) * j;
			m3[i][j] = i * 3 + j;
			m1[i][j] = m2[i][j] - m3[i][j];

		}
	EXPECT_EQ(m1, m2 - m3);
}

TEST(TMatrix, cant_subtract_matrixes_with_not_equal_size)
{
	TMatrix<int> m1(4), m2(2);
	ASSERT_ANY_THROW(m1 - m2);
}

