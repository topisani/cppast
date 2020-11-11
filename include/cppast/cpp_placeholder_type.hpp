// Copyright (C) 2017-2019 Tobias Pisani <topisani@hamsterpoison.com>
// This file is subject to the license terms in the LICENSE file
// found in the top-level directory of this distribution.

#ifndef CPPAST_CPP_PLACEHOLDER_TYPE_HPP_INCLUDED
#define CPPAST_CPP_PLACEHOLDER_TYPE_HPP_INCLUDED

#include <cppast/cpp_expression.hpp>
#include <cppast/cpp_type.hpp>

namespace cppast
{
/// A [cppast::cpp_type]() that is given as `[constraint] [cv] auto [cv]`.
class cpp_placeholder_type final : public cpp_type
{
public:
    /// \returns A newly created `placeholder` type.
    static std::unique_ptr<cpp_placeholder_type> build(std::string constraint)
    {
        return std::unique_ptr<cpp_placeholder_type>(
            new cpp_placeholder_type(std::move(constraint)));
    }

    /// \returns A reference to the constraint given.
    /// \note for now, this is only represented as the spelling of said constraint.
    const std::string& constraint() const noexcept
    {
        return constraint_;
    }

private:
    cpp_placeholder_type(std::string constraint) : constraint_(std::move(constraint)) {}

    cpp_type_kind do_get_kind() const noexcept override
    {
        return cpp_type_kind::placeholder_t;
    }

    std::string constraint_;
};

} // namespace cppast

#endif // CPPAST_CPP_PLACEHOLDER_TYPE_HPP_INCLUDED
