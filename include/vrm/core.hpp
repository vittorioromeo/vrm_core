// Copyright (c) 2015-2016 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0
// http://vittorioromeo.info | vittorio.romeo@outlook.com

#pragma once

// API configuration and name-related macros.
// Compiler/OS/target detection macros/utilities.
#include <vrm/core/config.hpp>

// Macros that do not strongly depend on other vrm_core modules.
#include <vrm/core/utility_macros.hpp>

// Pretty assertions.
#include <vrm/core/assert.hpp>

// Type-traits.
#include <vrm/core/type_traits.hpp>

// Safer and stricter casts.
#include <vrm/core/casts.hpp>

// ForArgs snippet.
#include <vrm/core/for_args.hpp>

#include <vrm/core/args_utils.hpp>
#include <vrm/core/is_valid.hpp>
#include <vrm/core/literals.hpp>
#include <vrm/core/make_array.hpp>
#include <vrm/core/ostream_utils.hpp>
#include <vrm/core/overload.hpp>
#include <vrm/core/static_if.hpp>
#include <vrm/core/strong_typedef.hpp>
#include <vrm/core/tuple_utils.hpp>
#include <vrm/core/type_aliases.hpp>
#include <vrm/core/variadic_min_max.hpp>
#include <vrm/core/y_combinator.hpp>
