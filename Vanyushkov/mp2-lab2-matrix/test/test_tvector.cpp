#include "utmatrix.h"

#include <gtest.h>

TEST(TVector, can_create_vector_with_positive_length)
{
  ASSERT_NO_THROW(TVector<int> v(5));
}

TEST(TVector, cant_create_too_large_vector)
{
  ASSERT_ANY_THROW(TVector<int> v(MAX_VECTOR_SIZE + 1));
}

TEST(TVector, throws_when_create_vector_with_negative_length)
{
  ASSERT_ANY_THROW(TVector<int> v(-5));
}

TEST(TVector, throws_when_create_vector_with_negative_startindex)
{
  ASSERT_ANY_THROW(TVector<int> v(5, -2));
}

TEST(TVector, can_create_copied_vector)
{
  TVector<int> v(10);

  ASSERT_NO_THROW(TVector<int> v1(v));
}

TEST(TVector, copied_vector_is_equal_to_source_one)
{
    TVector<int> v(10);
    for (int i = 0; i < 10; i++) v[i] = i;
    TVector<int> v1(v);

    EXPECT_EQ(v, v1);
  //ADD_FAILURE();
}

TEST(TVector, copied_vector_has_its_own_memory)
{
    TVector<int> v(10);
    for (int i = 0; i < 10; i++) v[i] = i;
    TVector<int> v1(v);
    v1[0] = 10;

    EXPECT_NE(v, v1);
  //ADD_FAILURE();
}

TEST(TVector, can_get_size)
{
  TVector<int> v(4);

  EXPECT_EQ(4, v.GetSize());
}

TEST(TVector, can_get_start_index)
{
  TVector<int> v(4, 2);

  EXPECT_EQ(2, v.GetStartIndex());
}

TEST(TVector, can_set_and_get_element)
{
  TVector<int> v(4);
  v[0] = 4;

  EXPECT_EQ(4, v[0]);
}

TEST(TVector, throws_when_set_element_with_negative_index)
{
    TVector<int> v(4);

    ASSERT_ANY_THROW(v[-1]);
  //ADD_FAILURE();
}

TEST(TVector, throws_when_set_element_with_too_large_index)
{
    TVector<int> v(4);

    ASSERT_ANY_THROW(v[4]);
  //ADD_FAILURE();
}

TEST(TVector, can_assign_vector_to_itself)
{
    TVector<int> v(10), v1;
    for (int i = 0; i < 10; i++) v[i] = i;

    ASSERT_NO_THROW(v1 = v);
    //v1 = v;
    EXPECT_EQ(v1, v);
  //ADD_FAILURE();
}

TEST(TVector, can_assign_vectors_of_equal_size)
{
    TVector<int> v(5);
    TVector<int> v1(5, 3);
    ASSERT_NO_THROW(v = v1);
    EXPECT_EQ(v, v1);
  //ADD_FAILURE();
}

TEST(TVector, assign_operator_change_vector_size)
{
    TVector<int> v(5);
    TVector<int> v1(3);
    ASSERT_NO_THROW(v = v1);
    EXPECT_EQ(3, v1.GetSize());
  //ADD_FAILURE();
}

TEST(TVector, can_assign_vectors_of_different_size)
{
    TVector<int> v1(10);
    TVector<int> v2(4);
    ASSERT_NO_THROW(v2 = v1);
    EXPECT_EQ(10, v2.GetSize());
  //ADD_FAILURE();
}

TEST(TVector, compare_equal_vectors_return_true)
{
    TVector<int> v(10), v1(10);
    for (int i = 0; i < 10; i++)
        v[i] = v1[i] = i;

    ASSERT_TRUE(v == v1);
  //ADD_FAILURE();
}

TEST(TVector, compare_vector_with_itself_return_true)
{
    TVector<int> v(4);

    ASSERT_TRUE(v == v);
  //ADD_FAILURE();
}

TEST(TVector, vectors_with_different_size_are_not_equal)
{
    TVector<int> v(4), v1(5);

    EXPECT_NE(v, v1);
  //ADD_FAILURE();
}

TEST(TVector, can_add_scalar_to_vector)
{
    TVector<int> v(10), v1(10);
    for (int i = 0; i < 10; i++)
    {
        v[i] = 1; v1[i] = 4;
    }
    v = v + 3;

    EXPECT_EQ(v, v1);
  //ADD_FAILURE();
}

TEST(TVector, can_subtract_scalar_from_vector)
{
    TVector<int> v(10), v1(10);
    for (int i = 0; i < 10; i++)
    {
        v[i] = 4; v1[i] = 1;
    }
    v = v - 3;

    EXPECT_EQ(v, v1);
  //ADD_FAILURE();
}

TEST(TVector, can_multiply_scalar_by_vector)
{
    TVector<int> v(10), v1(10);
    for (int i = 0; i < 10; i++)
    {
        v[i] = 2; v1[i] = 6;
    }
    v = v * 3;

    EXPECT_EQ(v, v1);
  //ADD_FAILURE();
}

TEST(TVector, can_add_vectors_with_equal_size)
{
    TVector<int> v(10), v1(10), v2(10), vs(10);
    for (int i = 0; i < 10; i++)
    {
        v[i] = 3; v1[i] = 1; vs[i] = 4;
    }

    ASSERT_NO_THROW(v2 = v + v1);
    EXPECT_EQ(vs, v2);
  //ADD_FAILURE();
}

TEST(TVector, cant_add_vectors_with_not_equal_size)
{
    TVector<int> v(10), v1(9), v2(10);

    ASSERT_ANY_THROW(v2 = v + v1);
  //ADD_FAILURE();
}

TEST(TVector, can_subtract_vectors_with_equal_size)
{
    TVector<int> v(10), v1(10), v2(10), vs(10);
    for (int i = 0; i < 10; i++)
    {
        v[i] = 4; v1[i] = 1; vs[i] = 3;
    }

    ASSERT_NO_THROW(v2 = v - v1);
    EXPECT_EQ(vs, v2);
  //ADD_FAILURE();
}

TEST(TVector, cant_subtract_vectors_with_not_equal_size)
{
    TVector<int> v(10), v1(9), v2(10);

    ASSERT_ANY_THROW(v2 = v - v1);
  //ADD_FAILURE();
}

TEST(TVector, can_multiply_vectors_with_equal_size)
{
    TVector<int> v(3), v1(3);
    int x;
    for (int i = 0; i < 3; i++)
    {
        v[i] = i; v1[i] = i + 1;
    }

    ASSERT_NO_THROW(x = v * v1);
    EXPECT_EQ(8, x);
  //ADD_FAILURE();
}

TEST(TVector, cant_multiply_vectors_with_not_equal_size)
{
    TVector<int> v(10), v1(9);
    int x;

    ASSERT_ANY_THROW(x = v * v1);
  //ADD_FAILURE();
}

