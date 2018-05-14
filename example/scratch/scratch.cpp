// DynaMix
// Copyright (c) 2013-2018 Borislav Stanimirov, Zahary Karadjov
//
// Distributed under the MIT Software License
// See accompanying file LICENSE.txt or copy at
// https://opensource.org/licenses/MIT
//
#include <dynamix/dynamix.hpp>

#include <iostream>
#include <vector>
#include <memory>

using namespace std;

DYNAMIX_DECLARE_MIXIN(incopy);

class incopy
{
public:
    incopy() = default;
    ~incopy() = default;
    incopy(const incopy&) = delete;
    incopy& operator=(const incopy&) = delete;
    incopy(incopy&&) = default;
    void boo() {}
private:
    vector<unique_ptr<int>> test;
};

DYNAMIX_MESSAGE_0(void, boo);

DYNAMIX_DEFINE_MESSAGE(boo);

DYNAMIX_DEFINE_MIXIN(incopy, boo_msg);

dynamix::object getobj()
{
    dynamix::object o;
    dynamix::mutate(o).add<incopy>();
    return o;
}

int main()
{
    auto obj = getobj();
    return 0;
}
