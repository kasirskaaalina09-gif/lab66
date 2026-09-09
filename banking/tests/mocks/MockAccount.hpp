#ifndef MOCK_ACCOUNT_HPP
#define MOCK_ACCOUNT_HPP

#include "../../Account.h"
#include <gmock/gmock.h>

class MockAccount : public Account {
public:
    MockAccount(int id, int balance)
        : Account(id, balance) {}

    MOCK_CONST_METHOD0(GetBalance, int());

    MOCK_METHOD1(ChangeBalance, void(int));

    MOCK_METHOD0(Lock, void());

    MOCK_METHOD0(Unlock, void());
};

#endif
