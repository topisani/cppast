// Copyright (C) 2017-2019 Tobias Pisani <topisani@hamsterpoison.com>
// This file is subject to the license terms in the LICENSE file
// found in the top-level directory of this distribution.

#include <cppast/cpp_template_parameter.hpp>

#include <cppast/cpp_alias_template.hpp>
#include <cppast/cpp_function_template.hpp>

#include "test_parser.hpp"

using namespace cppast;

// TODO: Properly parse requires clause instead of just ignoring it
TEST_CASE("cpp_template_requires_clause")
{
    auto code = R"(

template <typename A>
requires (sizeof(A) == 4)
using a = void;

)";

    cpp_entity_index idx;
    auto             file  = parse(idx, "cpp_template_requires_clause.cpp", code);
    auto             count = test_visit<cpp_alias_template>(
        *file,
        [&](const cpp_alias_template& alias) {
            REQUIRE(equal_types(idx, alias.type_alias().underlying_type(),
                                *cpp_builtin_type::build(cpp_void)));

            if (alias.name() == "a")
            {}
            else
                REQUIRE(false);
        },
        false); // can't check synopsis with comments
    REQUIRE(count == 1u);
}

TEST_CASE("cpp_function_requires_clause")
{
    auto code = R"(

template <typename A>
requires (sizeof(A) == 4)
void a() {}

template <typename A>
void b()
requires (sizeof(A) == 4)
{}

)";

    cpp_entity_index idx;
    auto             file  = parse(idx, "cpp_function_requires_clause.cpp", code);
    auto             count = test_visit<cpp_function_template>(
        *file,
        [&](const cpp_function_template& fun) {
            if (fun.name() == "a")
            {}
            if (fun.name() == "b")
            {}
            else
                REQUIRE(false);
        },
        false); // can't check synopsis with comments
    REQUIRE(count == 1u);
}
