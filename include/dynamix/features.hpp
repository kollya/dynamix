// DynaMix
// Copyright (c) 2013-2019 Borislav Stanimirov, Zahary Karadjov
//
// Distributed under the MIT Software License
// See accompanying file LICENSE.txt or copy at
// https://opensource.org/licenses/MIT
//
#pragma once

/**
* \file
* Non-message feature of mixins.
*/

#include "config.hpp"

namespace dynamix
{

/// The type of the `empty` feature.
struct DYNAMIX_API noop_feature_t {};

/// A mixin feature which indicates that the mixin implements no features.
extern DYNAMIX_API noop_feature_t* none;

/// A mixin feature function which indicates that the mixin implements no features.
/// It ignores all of its arguments so it's useful for metaprogramming and macros.
inline noop_feature_t* noop_feature(...) { return nullptr; }

namespace internal
{
struct mixin_name_feature
{
    const char* name;
};
}

/// Allows the mixin name to be set manually (instead of obtained by the class name)
inline internal::mixin_name_feature mixin_name(const char* name)
{
    return {name};
}

} // namespace dynamix
