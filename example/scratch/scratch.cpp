// DynaMix
// Copyright (c) 2013-2019 Borislav Stanimirov, Zahary Karadjov
//
// Distributed under the MIT Software License
// See accompanying file LICENSE.txt or copy at
// https://opensource.org/licenses/MIT
//
#define DYNAMIX_USE_LEGACY_MESSAGE_MACROS
#include <dynamix/dynamix.hpp>

#include <iostream>

using namespace std;

DYNAMIX_MULTICAST_MESSAGE_1(void, testv, vector<int>, data);
DYNAMIX_MESSAGE_2(int, yyy, int, a, float, b);

class a
{
public:
    void testv(vector<int> data)
    {
        cout << "a: " << data.size() << endl;
    }

    int zyyy(int a, float b) { return short(b) + a; }
};

DYNAMIX_DEFINE_MIXIN(a, testv_msg & bind(yyy_msg, &a::zyyy));

class b
{
public:
};

void b_testv(void*, vector<int> data)
{
    cout << "b: " << data.size() << endl;
}

class xxx : public b {};

DYNAMIX_DEFINE_MIXIN(b, bind(testv_msg, b_testv));

struct script_mixin
{
    int n = 10;
};

void script_testv(void* m, vector<int> data)
{
    auto sm = reinterpret_cast<script_mixin*>(m);
    cout << "script(" << sm->n << "): " << data.size() << endl;
}

namespace is_mixin_ns
{

template <typename T>
static int _dynamix_get_mixin_type_info(const T*); // better mach than global func for implicit casts

template <typename T>
struct is_mixin
{
    static constexpr bool value = !std::is_same<int, decltype(_dynamix_get_mixin_type_info(std::declval<T*>()))>::value;
};

}

using is_mixin_ns::is_mixin;

//template <typename T>
//using is_mixin = std::is_same<T, decltype(extract_arg((::dynamix::mixin_type_info&(*)(const T*))_dynamix_get_mixin_type_info))>;

int main()
{
    cout << is_mixin<a>::value << endl;
    cout << is_mixin<b>::value << endl;
    cout << is_mixin<xxx>::value << endl;

    auto& dom = dynamix::internal::domain::safe_instance();
    dynamix::mixin_type_info info0;

    info0.name = "bagavag";
    dynamix::internal::set_missing_traits_to_info<script_mixin>(info0);
    dom.register_mixin_type(info0);

    info0.message_infos.emplace_back();
    auto& msg = info0.message_infos.back();
    msg.bid = msg.priority = 0;
    msg.caller = reinterpret_cast<dynamix::internal::func_ptr>(script_testv);
    msg.message = static_cast<dynamix::internal::message_t*>(&_dynamix_get_mixin_feature_safe(testv_msg));

    auto hero = new dynamix::object;
    dynamix::mutate(hero)
        .add<a>()
        .add<b>()
        .add("bagavag");

    vector<int> foo = {1, 2, 3};
    testv(hero, foo);

    cout << yyy(hero, 3, 5.2f) << endl;

    return 0;
}

DYNAMIX_DEFINE_MESSAGE(testv);
DYNAMIX_DEFINE_MESSAGE(yyy);
