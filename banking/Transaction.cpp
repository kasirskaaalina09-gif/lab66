#include "Transaction.h"

#include <stdexcept>

void Transaction::set_fee(int fee)
{
    fee_ = fee;
}

bool Transaction::Make(Account& from, Account& to, int sum)
{
    if(&from == &to)
    {
        throw std::logic_error("same account");
    }

    if(sum <= 0)
    {
        throw std::invalid_argument("negative sum");
    }

    if(sum < 100)
    {
        throw std::logic_error("too small");
    }

    if(sum <= fee_ * 2)
    {
        return false;
    }

    from.Lock();
    to.Lock();

    if(from.GetBalance() < sum + fee_)
    {
        from.Unlock();
        to.Unlock();
        return false;
    }

    from.ChangeBalance(-(sum + fee_));
    to.ChangeBalance(sum);

    SaveToDataBase(from, to, sum);

    from.Unlock();
    to.Unlock();

    return true;
}

void Transaction::SaveToDataBase(Account&, Account&, int)
{
}
