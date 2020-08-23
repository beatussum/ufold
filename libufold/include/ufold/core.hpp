/*
 * Copyright (C) 2020 Mattéo Rossillol‑‑Laruelle <beatussum@protonmail.com>
 *
 * This program is free software:  you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published  by
 * the Free Software Foundation, either version 3 of the License, or (at
 * your option) any later version.
 *
 * This program is distributed in the hope that it will be  useful,
 * but WITHOUT ANY WARRANTY;   without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <https://www.gnu.org/licenses/>.
 */

/**
 * @file ufold/core.hpp
 * @brief Some core utilities used by the library
 * @author Mattéo Rossillol‑‑Laruelle <beatussum@protonmail.com>
 * @date 2020-08-13
 * @copyright GPL-3+
 */


#ifndef UFOLD_CORE_HPP
#define UFOLD_CORE_HPP

#include "libufold_export.hpp"

#include <iterator>
#include <future>
#include <vector>

/**
 * @brief Namespace of some core libufold-specific utilities
 * @note This namespace should not be used outside of libufold
 */
namespace ufold::core
{
    using std::distance;

    template<class _ExecutionPolicy, class _InputIt, class _UnaryPredicate>
    [[gnu::const]]
    std::future<_InputIt> async_find_if( _ExecutionPolicy&& policy
                                       , const _InputIt first
                                       , const _InputIt last
                                       , const _UnaryPredicate p
                                       );

    template<typename _Enum>
    [[gnu::const]]
    constexpr auto bad_enum() noexcept;

    template<class _Container>
    [[gnu::const]]
    typename _Container::difference_type distance( const _Container& first
                                                 , const typename _Container::const_iterator last
                                                 );

    template<class _Container>
    [[gnu::const]]
    typename _Container::difference_type distance( const _Container& rfirst
                                                 , const typename _Container::const_reverse_iterator rlast
                                                 );

    template<typename _Enum>
    [[gnu::const]]
    constexpr auto enum_cast(const std::underlying_type_t<_Enum> value) noexcept;

    template<class _ExecutionPolicy, class _InputIt, class T>
    [[gnu::const]]
    _InputIt find_first_not_of( _ExecutionPolicy&& policy
                              , const _InputIt first
                              , const _InputIt last
                              , const T& value
                              );

    template<class T>
    [[gnu::const]]
    auto make_vector(const typename std::vector<T>::size_type size);

    template<typename _Enum>
    [[gnu::const]]
    constexpr auto underlying_cast(const _Enum constant) noexcept;
}

/**
 * @brief Add some operator overloads to use an `enum` as a flag
 * @param T the `enum` to which the operators are added
 */
#define UFOLD_ADD_FLAGS_OP(T)                                          \
[[gnu::const]]                                                         \
constexpr T operator|(const T a, const T b) noexcept                   \
{                                                                      \
    using ::ufold::core::underlying_cast;                              \
                                                                       \
    return static_cast<T>(underlying_cast(a) | underlying_cast(b));    \
}                                                                      \
                                                                       \
[[gnu::const]]                                                         \
constexpr T operator|=(T a, const T b) noexcept                        \
{                                                                      \
    a = a | b;                                                         \
                                                                       \
    return a;                                                          \
}                                                                      \
                                                                       \
[[gnu::const]]                                                         \
constexpr bool operator&(const T a, const T b) noexcept                \
{                                                                      \
    using ::ufold::core::underlying_cast;                              \
                                                                       \
    return static_cast<bool>(underlying_cast(a) & underlying_cast(b)); \
}
// ADD_FLAGS_OPERATORS(T)

#define ufold_rethrow                                       \
::std::throw_with_nested(                                   \
    ::std::runtime_error(::std::string(__PRETTY_FUNCTION__) \
                         + " failed")                       \
)

#include "ufold/core.ipp"
#endif // UFOLD_CORE_HPP
