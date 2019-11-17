// Copyright 2018 Your Name <your_email>

#include <gtest/gtest.h>

#include "header.hpp"

TEST(shared_ptr, ItemInsideCostructor)
{
    SharedPtr ptr(new int{5});

    EXPECT_EQ(*(ptr.get()),5);
    EXPECT_EQ(bool(ptr),true);
    EXPECT_EQ(ptr.use_count(),1);
}

TEST(shared_ptr, OperatorPrisvaivania2)
{
    SharedPtr ptr(new int{5});

    SharedPtr ptr2 = std::move(ptr);

    EXPECT_EQ(*(ptr2.get()),5);
    EXPECT_EQ(bool(ptr2),true);
    EXPECT_EQ(ptr2.use_count(),1);
}


TEST(shared_ptr, SWAP)
{
    SharedPtr ptr{new int{5}};
    SharedPtr ptr2{new int{105}};

    ptr.swap(ptr2);

    EXPECT_EQ(*(ptr2.get()),5);
    EXPECT_EQ(bool(ptr2),true);
    EXPECT_EQ(ptr2.use_count(),1);

    EXPECT_EQ(*(ptr.get()),105);
    EXPECT_EQ(bool(ptr),true);
    EXPECT_EQ(ptr.use_count(),1);
}

TEST(shared_ptr, Count)
{
    int a = rand();
    SharedPtr ptr{new int {a}};
    EXPECT_EQ(ptr.use_count(),1);
}

TEST(SharedPtr, FromPointer)
{
    auto sourcePtr = new int{789};
    auto ptr = SharedPtr<int>{sourcePtr};

    EXPECT_EQ(static_cast<bool>(ptr), true);
    EXPECT_EQ(ptr.use_count(), 1);
    EXPECT_EQ(ptr.get(), sourcePtr);
    EXPECT_EQ(*ptr, 789);
}
