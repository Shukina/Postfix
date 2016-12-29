#include "tstack.h"
#include "gtest.h"

TEST(TStack, can_create_stack_with_positive_length)
{
	ASSERT_NO_THROW(TStack<int> s(5));
}

TEST(TStack, cant_create_too_large_stack)
{
	ASSERT_ANY_THROW(TStack<int> s(102401));
}

TEST(TStack, cant_create_stack_with_negative_length)
{
	ASSERT_ANY_THROW(TStack<int> s(-1));
}

TEST(TStack, can_check_is_full_false)
{
	TStack<int> s(5);
	EXPECT_EQ(false, s.IsFull());
}

TEST(TStack, can_add_element)
{
	TStack<int> s(5);
	ASSERT_NO_THROW(s.Push(1));
}

TEST(TStack, can_check_is_full_true)
{
	TStack<int> s(5);
	s.Push(1);
	s.Push(1);
	s.Push(1);
	s.Push(1);
	s.Push(1);
	EXPECT_EQ(true, s.IsFull());
}

TEST(TStack, can_check_is_empty_true)
{
	TStack<int> s(5);
	EXPECT_EQ(true, s.IsEmpty());
}

TEST(TStack, can_check_is_empty_false)
{
	TStack<int> s(5);
	s.Push(1);
	EXPECT_EQ(false, s.IsEmpty());
}

TEST(TStack, can_get_element)
{
	TStack<int> s(5);
	s.Push(1);
	ASSERT_NO_THROW(s.Pop());
}

TEST(TStack, after_get_all_element_stack_is_empty)
{
	TStack<int> s(5);
	s.Push(1);
	s.Pop();
	EXPECT_EQ(true, s.IsEmpty());
}

TEST(TStack, stack_isfull_cant_add_element)
{
	TStack<int> s(5);
	s.Push(1);
	s.Push(1);
	s.Push(1);
	s.Push(1);
	s.Push(1);
	ASSERT_ANY_THROW(s.Push(5));
}

TEST(TStack, get_element_equal_to_add)
{
	TStack<int> s(5);
	int temp = 7;
	s.Push(temp);
	EXPECT_EQ(temp, s.Pop());
}