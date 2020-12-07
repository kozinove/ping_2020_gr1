#include "Calculator.h"
#include <gtest.h>

TEST(Calculator, can_create_arithmetic)
{
    ASSERT_NO_THROW(Calculator c);
}

TEST(Calculator, can_accept_int_value)
{
    ASSERT_NO_THROW(Calculator c("4"));
}

TEST(Calculator, can_accept_int_value_and_return_it)
{
    Calculator c;
    ASSERT_EQ(4, c.doCalculator("4"));
}

TEST(Calculator, can_accept_double_value)
{
    ASSERT_NO_THROW(Calculator c("4.5"));
}

TEST(Calculator, can_accept_double_value_and_return_it)
{
    Calculator c;
    ASSERT_EQ(4.5, c.doCalculator("4.5"));
}

TEST(Calculator, cant_accept_worng_value)
{
    Calculator c;
    ASSERT_ANY_THROW(c.doCalculator("4.5.1"));
}

TEST(Calculator, can_accept_negative_value_and_return_it)
{
    Calculator c;
    ASSERT_EQ(-4.5, c.doCalculator("-4.5"));
}

TEST(Calculator, returns_zero_when_empty_example)
{
    Calculator c;
    ASSERT_EQ(0, c.doCalculator(""));
}

TEST(Calculator, can_accept_two_values_and_operation)
{
    Calculator c("2+2");
    ASSERT_NO_THROW(c.doCalculator());
}

TEST(Calculator, can_handle_spaces)
{
    Calculator c("2 + 2");
    ASSERT_NO_THROW(c.doCalculator());
}

TEST(Calculator, currect_result_with_two_values_and_operation_sum)
{
    Calculator c("2+ 2");
    ASSERT_EQ(4, c.doCalculator());
}

TEST(Calculator, currect_result_with_two_values_and_operation_min)
{
    Calculator c("2- 2");
    ASSERT_EQ(0, c.doCalculator());
}

TEST(Calculator, currect_result_with_two_values_and_operation_sub)
{
    Calculator c("2* 3");
    ASSERT_EQ(6, c.doCalculator());
}

TEST(Calculator, currect_result_with_two_values_and_operation_div)
{
    Calculator c("3/ 2");
    ASSERT_EQ(1.5, c.doCalculator());
}

TEST(Calculator, cant_divided_by_zero)
{
    Calculator c("4/0");
    ASSERT_ANY_THROW(c.doCalculator());
}

TEST(Calculator, currect_result_with_two_values_and_operation_pos)
{
    Calculator c("3^ 2");
    ASSERT_EQ(9, c.doCalculator());
}

TEST(Calculator, cant_pow_zero_to_zero)
{
    Calculator c("0^0");
    ASSERT_ANY_THROW(c.doCalculator());
}

TEST(Calculator, cant_pow_negative_value_to_inverse_to_even_number)
{
    Calculator c("(-4)^0.5");
    ASSERT_ANY_THROW(c.doCalculator());
}

TEST(Calculator, currect_result_with_two_values_and_operation_int_div)
{
    Calculator c("5 div 3");
    ASSERT_EQ(1, c.doCalculator());
}

TEST(Calculator, cant_int_divided_by_zero)
{
    Calculator c("4 div 0");
    ASSERT_ANY_THROW(c.doCalculator());
}

TEST(Calculator, currect_result_with_two_values_and_operation_mod)
{
    Calculator c("5 mod 3");
    ASSERT_EQ(2, c.doCalculator());
}

TEST(Calculator, cant_mod_by_zero)
{
    Calculator c("4 mod 0");
    ASSERT_ANY_THROW(c.doCalculator());
}

TEST(Calculator, cant_use_several_operations_in_row)
{
    Calculator c("2+-2");
    ASSERT_ANY_THROW(c.doCalculator());
}

TEST(Calculator, currect_result_with_more_currect_values_and_operations)
{
    Calculator c("2 + 3 - 4");
    ASSERT_EQ(1, c.doCalculator());
}

TEST(Calculator, can_accept_example_with_brackets)
{
    Calculator c("2 - (1+4)");
    ASSERT_NO_THROW(c.doCalculator());
}

TEST(Calculator, currect_result_with_brackets)
{
    Calculator c("2 - (1+4)");
    ASSERT_EQ(-3, c.doCalculator());
}

TEST(Calculator, cant_do_arithmetic_without_open_bracket)
{
    Calculator c("2 - 4)");
    ASSERT_ANY_THROW(c.doCalculator());
}

TEST(Calculator, cant_do_arithmetic_without_close_bracket)
{
    Calculator c("(2 - 4");
    ASSERT_ANY_THROW(c.doCalculator());
}

TEST(Calculator, cant_do_arithmetic_without_values_in_brackets)
{
    Calculator c("()");
    ASSERT_ANY_THROW(c.doCalculator());
}

TEST(Calculator, can_not_use_sub_front_open_bracket)
{
    Calculator c("-2(-2)");
    ASSERT_NO_THROW(c.doCalculator());
}

TEST(Calculator, currect_result_without_sub_front_bracket)
{
    Calculator c("-2(-2)");
    ASSERT_EQ(4, c.doCalculator());
}

TEST(Calculator, can_not_use_pow_behind_close_bracket)
{
    Calculator c("(-2)2");
    ASSERT_NO_THROW(c.doCalculator());
}

TEST(Calculator, currect_result_without_pow_behind_bracket)
{
    Calculator c("(-2)2");
    ASSERT_EQ(4, c.doCalculator());
}

TEST(Calculator, can_not_use_sub_between_close_and_open_brackets)
{
    Calculator c("(-2)(-2)");
    ASSERT_NO_THROW(c.doCalculator());
}

TEST(Calculator, currect_result_without_sub_between_close_and_open_brackets)
{
    Calculator c("(-2)(-2)");
    ASSERT_EQ(4, c.doCalculator());
}

TEST(Calculator, can_use_pi_number)
{
    Calculator c("pi");
    ASSERT_NO_THROW(c.doCalculator());
}

TEST(Calculator, can_return_pi_number)
{
    Calculator c("pi");
    ASSERT_EQ(acos(-1), c.doCalculator()); // acos(-1) == pi
}

TEST(Calculator, unary_operation_cant_accept_value_without_brackets) // all unary operation
{
    Calculator c("abs -4");
    ASSERT_ANY_THROW(c.doCalculator());
}

TEST(Calculator, can_accept_abs_and_currect_value_in_brackets)
{
    Calculator c("abs(-4)");
    ASSERT_NO_THROW(c.doCalculator());
}

TEST(Calculator, currect_result_with_abs_and_currect_value)
{
    Calculator c("abs(-4)");
    ASSERT_EQ(4, c.doCalculator());
}

TEST(Calculator, can_use_all_currect_values_and_operation_with_brackets)
{
    Calculator c("abs(1-3)");
    ASSERT_NO_THROW(c.doCalculator());
}

TEST(Calculator, currect_result_with_all_currect_values_and_operation_with_brackets)
{
    Calculator c("abs(1-3)");
    ASSERT_EQ(2, c.doCalculator());
}

TEST(Calculator, can_not_use_sub_front_unary_operation)
{
    Calculator c("2abs(-4)");
    ASSERT_NO_THROW(c.doCalculator());
}

TEST(Calculator, currect_result_without_sub_front_unary_operation)
{
    Calculator c("2abs(-4)");
    ASSERT_EQ(8, c.doCalculator());
}

TEST(Calculator, can_use_sqrt_and_currect_value_in_brackets)
{
    Calculator c("sqrt(4)");
    ASSERT_NO_THROW(c.doCalculator());
}

TEST(Calculator, currect_result_with_sqrt_and_currect_value)
{
    Calculator c("sqrt(4)");
    ASSERT_EQ(2, c.doCalculator());
}

TEST(Calculator, cant_use_sqrt_with_negative_value)
{
    Calculator c("sqrt(-4)");
    ASSERT_ANY_THROW(c.doCalculator());
}

TEST(Calculator, can_use_cos_and_currect_value_in_brackets)
{
    Calculator c("cos(pi/3)");
    ASSERT_NO_THROW(c.doCalculator());
}

TEST(Calculator, currect_result_with_cos_and_currect_value)
{
    Calculator c("cos(pi/3)"); // cos(60`)
    ASSERT_EQ(0.5, c.doCalculator()); // cos(60`) == 0.5
}

TEST(Calculator, can_use_sin_and_currect_value_in_brackets)
{
    Calculator c("sin(pi/3)");
    ASSERT_NO_THROW(c.doCalculator());
}

TEST(Calculator, currect_result_with_sin_and_currect_value)
{
    Calculator c("sin(pi/6)"); // sin(30`)
    ASSERT_EQ(0.5, c.doCalculator()); // sin(30`) == 0.5
}

TEST(Calculator, can_use_tan_and_currect_value_in_brackets)
{
    Calculator c("tg(pi/3)");
    ASSERT_NO_THROW(c.doCalculator());
}

TEST(Calculator, currect_result_with_tan_and_currect_value)
{
    Calculator c("tg(pi/3)"); // tg(60`)
    ASSERT_EQ(1.732053, c.doCalculator()); // tg(60`) == sqrt(3) == 1.732053
}

TEST(Calculator, cant_tan_of_angle_90_degrees)
{
    Calculator c("tan(90*pi/180)");
    ASSERT_ANY_THROW(c.doCalculator());
}

TEST(Calculator, can_use_cot_and_currect_value_in_brackets)
{
    Calculator c("ctg(pi/6)");
    ASSERT_NO_THROW(c.doCalculator());
}

TEST(Calculator, currect_result_with_cot_and_currect_value)
{
    Calculator c("ctg(pi/6)"); // ctg(30`)
    ASSERT_EQ(1.73205, c.doCalculator()); // ctg(60`) == sqrt(3) == 1.73205
}

TEST(Calculator, cant_cot_of_angle_0_degrees)
{
    Calculator c("cot(0)");
    ASSERT_ANY_THROW(c.doCalculator());
}

TEST(Calculator, cant_arithmetic_long_example)
{
    Calculator c; // Max length example is 100 values, operations and brackets together
    std::string example;
    example.reserve(101);
    example = "1";
    for (size_t i = 0; i < 50; i++) example += "+1";
    ASSERT_ANY_THROW(c.doCalculator(example)); // 101 values and operations
}

TEST(Calculator, cant_use_abs_large_values) // Max abs large value when can used is 1.797e+308
{
    Calculator c("-1.798*10^308");
    ASSERT_ANY_THROW(c.doCalculator());
}

TEST(Calculator, return_currect_result_with_all_operations)
{
    Calculator c("abs((sin(55*pi/180)2+cos(55*pi/180)2)(-tg(pi/9))/ctg(11*pi/18)-2((2.2sqrt(4))/2.2)^3mod9div2-8)");
    // a = 55 * pi / 180
    // sin(a)^2 + cos(a)^2 == 1
    // b == pi / 9,   11 * pi / 18 == b + pi / 2
    // -tg(b) / ctg(b + pi / 2) == 1
    // (2.4 + sqrt(4)) / 2 == 2
    // 2 ^ 3 * 2 = 16
    // 16 mod 9 div 2 == 7 div 2 == 3
    // abs(1 * 1 - 3 - 8) == 10
    ASSERT_EQ(10, c.doCalculator());
}