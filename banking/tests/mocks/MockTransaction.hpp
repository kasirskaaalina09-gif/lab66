#ifndef MOCK_TRANSACTION_HPP
#define MOCK_TRANSACTION_HPP

#include "../../Transaction.h"
#include <gmock/gmock.h>

class MockTransaction : public Transaction {
public:
    MOCK_METHOD3(
        SaveToDataBase,
        void(Account& from, Account& to, int sum)
    );
};

#endif
