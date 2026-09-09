#pragma once

#include "Account.h"

class Transaction
{
public:
    void set_fee(int fee);

    virtual bool Make(Account& from, Account& to, int sum);

    virtual void SaveToDataBase(Account& from, Account& to, int sum);

private:
    int fee_ = 1;
};
