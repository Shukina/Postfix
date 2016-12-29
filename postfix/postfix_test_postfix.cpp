#include "TPostfix.h"
#include "gtest.h"

TEST(TPostfix, can_create_postfix)
{
	string str = "3+5";
	 TPostfix postfix(str);
	 ASSERT_NO_THROW(TPostfix postfix(str));
}


TEST(TPostfix, infix_can_be_correct)
{
	string str = "3+5";
	TPostfix postfix(str);
	EXPECT_EQ(1, postfix.IsCorrect(str));
}

TEST(TPostfix, infix_can_be_not_correct)
{
	string str = ")3+5";
	TPostfix postfix(str);
	EXPECT_EQ(0, postfix.IsCorrect(str));
}

TEST(TPostfix, postfix_is_equal_to_my_postfix)
{
	string str = "3+5";
	TPostfix postfix(str);
	postfix.ToPostfix();
	EXPECT_EQ("3 5 +", postfix.GetPostfix());
}

TEST(TPostfix, simple_multiplication_test)
{
	string expression = "2*2";
	string result = "2 2 *";
	TPostfix postfix(expression);
	postfix.ToPostfix();
	EXPECT_EQ(result, postfix.GetPostfix());
}

TEST(TPostfix, simple_addition_test)
{
	string expression = "2+2";
	string result = "2 2 +";
	TPostfix postfix(expression);
	postfix.ToPostfix();
	EXPECT_EQ(result, postfix.GetPostfix());
}

TEST(TPostfix, simple_division_test)
{
	string expression = "2/2";
	string result = "2 2 /";
	TPostfix postfix(expression);
	postfix.ToPostfix();
	EXPECT_EQ(result, postfix.GetPostfix());
}

TEST(TPostfix, simple_subtraction_test)
{
	string expression = "2-2";
	string result = "2 2 -";
	TPostfix postfix(expression);
	postfix.ToPostfix();
	EXPECT_EQ(result, postfix.GetPostfix());
}

TEST(TPostfix, mixed_test_number_one)
{
	string expression = "a+b*c";
	string result = "a b c *+";
	TPostfix postfix(expression);
	postfix.ToPostfix();
	EXPECT_EQ(result, postfix.GetPostfix());
}

TEST(TPostfix, mixed_test_number_two)
{
	string expression = "a+b-c*d";
	string result = "a b +c d *-";
	TPostfix postfix(expression);
	postfix.ToPostfix();
	EXPECT_EQ(result, postfix.GetPostfix());
}

TEST(TPostfix, mixed_test_number_three_cos_sin)
{
	string expression = "(1+sin(1+cos(2+2*2))/3)*1";
	string result = "1 1 2 2 2 *+cos+sin3 /+1 *";
	TPostfix postfix(expression);
	postfix.ToPostfix();
	EXPECT_EQ(result, postfix.GetPostfix());
}

TEST(TPostfix, test_with_sin_and_minus)
{
	string expression = "sin(sin(-2+2))";
	string result = "2 -2 +sinsin";
	TPostfix postfix(expression);
	postfix.ToPostfix();
	EXPECT_EQ(result, postfix.GetPostfix());
}

TEST(TPostfix, calculate_with__minus_one)
{
	string expression = "-2-3";
	double result = -5;
	TPostfix postfix(expression);
	postfix.ToPostfix();
	EXPECT_EQ(result, postfix.Calculate());
}

TEST(TPostfix, calculate_with__minus_two)
{
	string expression = "-2-sin(-3+3)";
	double result = -2;
	TPostfix postfix(expression);
	postfix.ToPostfix();
	EXPECT_EQ(result, postfix.Calculate());
}

TEST(TPostfix, calculate_with_sin_and_minus)
{
	string expression = "sin(sin(-2+2))";
	double result = 0;
	TPostfix postfix(expression);
	postfix.ToPostfix();
	EXPECT_EQ(result, postfix.Calculate());
}

TEST(TPostfix, mixed_calculate)
{
	string expression = "(1+sin(1+cos(2+2*2))/3)*1";
	double result = 1.0116;
	TPostfix postfix(expression);
	postfix.ToPostfix();
	double res = postfix.Calculate();
	EXPECT_EQ(result, res);
}