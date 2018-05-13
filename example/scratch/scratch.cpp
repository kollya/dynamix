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
    incopy(const incopy&) = delete;
    incopy& operator=(const incopy&) = delete;
private:
    vector<unique_ptr<int>> test;
};

DYNAMIX_DEFINE_MIXIN(incopy, dynamix::none);

int main()
{
    return 0;
}
