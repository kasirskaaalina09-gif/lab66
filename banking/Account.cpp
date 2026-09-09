#include "Account.h"

Account::Account(int id, int balance)
    : id_(id), balance_(balance), locked_(false)
{
}

int Account::id() const
{
    return id_;
}

int Account::GetBalance() const
{
    return balance_;
}

void Account::ChangeBalance(int diff)
{
    if(!locked_)
    {
        throw std::runtime_error("Account is not locked");
    }

    balance_ += diff;
}

void Account::Lock()
{
    if(locked_)
    {
        throw std::runtime_error("Account already locked");
    }

    locked_ = true;
}

void Account::Unlock()
{
    locked_ = false;
}
