#include <gtest/gtest.h>

#include "Account.h"

TEST(AccountTest, Constructor)
{
    Account acc(1, 100);

    EXPECT_EQ(acc.id(), 1);
    EXPECT_EQ(acc.GetBalance(), 100);
}

TEST(AccountTest, LockAndChangeBalance)
{
    Account acc(1, 100);

    acc.Lock();

    acc.ChangeBalance(50);

    EXPECT_EQ(acc.GetBalance(), 150);

    acc.Unlock();
}

TEST(AccountTest, ChangeBalanceWithoutLockThrows)
{
    Account acc(1, 100);

    EXPECT_THROW(acc.ChangeBalance(50), std::runtime_error);
}

TEST(AccountTest, LockTwiceThrows)
{
    Account acc(1, 100);

    acc.Lock();

    EXPECT_THROW(acc.Lock(), std::runtime_error);
}

TEST(AccountTest, UnlockWithoutLock)
{
    Account acc(1, 100);

    EXPECT_NO_THROW(acc.Unlock());
}
