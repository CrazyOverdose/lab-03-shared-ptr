// Copyright 2018 Your Name <your_email>

#include <gtest/gtest.h>

#include "header.hpp"
#include <string>


TEST(shared_ptr, equality1)
{
    SharedPtr a(new double{56.4});

    SharedPtr b = std::move(a);

    EXPECT_EQ(*(b.get()),56.4);
}

TEST(shared_ptr, reset)
{
    SharedPtr a{new int{5}};

    a.reset();
    EXPECT_EQ(bool(a),false);

    a.reset(new int{5});
    EXPECT_EQ(*(a.get()),5);
    EXPECT_EQ(bool(a),true);
    EXPECT_EQ(a.use_count(),1);
}

TEST(shared_ptr, swap)
{
    SharedPtr a{new bool{true}};
    SharedPtr b{new bool{false}};

    a.swap(b);

    EXPECT_EQ(*(b.get()),true);
    EXPECT_EQ(bool(b),true);
    EXPECT_EQ(b.use_count(),1);

    EXPECT_EQ(*(a.get()),false);
    EXPECT_EQ(bool(a),true);
    EXPECT_EQ(a.use_count(),1);
}

TEST(shared_ptr, use_count)
{
    SharedPtr a{new double {32.4}};
    EXPECT_EQ(a.use_count(),1);
}

TEST(SharedPtr, pointer)
{
    auto a = new string{"Taehyung"};
    auto b = SharedPtr<string>{a};

    EXPECT_EQ(b.use_count(), 1);
    EXPECT_EQ(b.get(), a);
    EXPECT_EQ(*b, "Taehyung");
}
