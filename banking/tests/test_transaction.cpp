#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "Transaction.h"
#include "Account.h"
#include "mocks/MockAccount.hpp"
#include "mocks/MockTransaction.hpp"

using ::testing::_;
using ::testing::Return;
using ::testing::AtLeast;

// 1. Перевод на тот же аккаунт
TEST(TransactionTest, SameAccountThrows)
{
    MockAccount acc(1, 1000);

    Transaction tx;

    EXPECT_THROW(tx.Make(acc, acc, 200), std::logic_error);
}

// 2. Отрицательная сумма
TEST(TransactionTest, NegativeSumThrows)
{
    MockAccount from(1, 1000);
    MockAccount to(2, 500);

    Transaction tx;

    EXPECT_THROW(tx.Make(from, to, -100), std::invalid_argument);
}

// 3. Слишком маленькая сумма
TEST(TransactionTest, TooSmallSumThrows)
{
    MockAccount from(1, 1000);
    MockAccount to(2, 500);

    Transaction tx;

    EXPECT_THROW(tx.Make(from, to, 50), std::logic_error);
}

// 4. Комиссия слишком большая
TEST(TransactionTest, FeeTooLargeReturnsFalse)
{
    MockAccount from(1, 1000);
    MockAccount to(2, 500);

    Transaction tx;
    tx.set_fee(100);

    EXPECT_FALSE(tx.Make(from, to, 150));
}

// 5. Успешный перевод
TEST(TransactionTest, SuccessfulTransfer)
{
    MockAccount from(1, 1000);
    MockAccount to(2, 500);

    Transaction tx;
    tx.set_fee(1);

    EXPECT_CALL(from, Lock()).Times(1);
    EXPECT_CALL(to, Lock()).Times(1);

    EXPECT_CALL(to, ChangeBalance(200)).Times(1);

    EXPECT_CALL(from, GetBalance())
        .WillOnce(Return(1000));

    EXPECT_CALL(from, ChangeBalance(-201)).Times(1);

    EXPECT_CALL(from, Unlock()).Times(1);
    EXPECT_CALL(to, Unlock()).Times(1);

    EXPECT_TRUE(tx.Make(from, to, 200));
}

// 6. Недостаточно денег
TEST(TransactionTest, InsufficientFunds)
{
    MockAccount from(1, 100);
    MockAccount to(2, 500);

    Transaction tx;
    tx.set_fee(1);

    EXPECT_CALL(from, Lock()).Times(1);
    EXPECT_CALL(to, Lock()).Times(1);

    EXPECT_CALL(from, GetBalance())
        .WillOnce(Return(100));

    EXPECT_CALL(from, Unlock()).Times(1);
    EXPECT_CALL(to, Unlock()).Times(1);

    EXPECT_FALSE(tx.Make(from, to, 150));
}

// 7. SaveToDataBase вызывается
TEST(TransactionTest, SaveToDataBaseIsCalled)
{
    MockAccount from(1, 1000);
    MockAccount to(2, 500);
    MockTransaction tx; // mock transaction

    tx.set_fee(1);

    EXPECT_CALL(from, Lock()).Times(1);
    EXPECT_CALL(to, Lock()).Times(1);

    EXPECT_CALL(to, ChangeBalance(200)).Times(1);

    EXPECT_CALL(from, GetBalance())
        .WillOnce(Return(1000));

    EXPECT_CALL(from, ChangeBalance(-201)).Times(1);

    EXPECT_CALL(tx, SaveToDataBase(_, _, 200)).Times(1);

    EXPECT_CALL(from, Unlock()).Times(1);
    EXPECT_CALL(to, Unlock()).Times(1);

    EXPECT_TRUE(tx.Make(from, to, 200));
}

TEST(TransactionTest, RealTransactionCoverage)
{
    Account from(1, 1000);
    Account to(2, 500);

    Transaction tx;
    tx.set_fee(1);

    EXPECT_TRUE(tx.Make(from, to, 200));

    EXPECT_EQ(from.GetBalance(), 799);
    EXPECT_EQ(to.GetBalance(), 700);
}
