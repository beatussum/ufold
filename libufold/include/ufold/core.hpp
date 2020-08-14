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

#include <iostream>

#ifdef __GNUG__
#   define LIBUFOLD_CONST [[gnu::const]]
#else // __GNUG__
#   define LIBUFOLD_CONST
#endif // __GNUG__

/**
 * @tparam _Enum the `enum` type
 * @param  a     the `enum` constant
 * @return the `enum` constant \p a as its underlying type
 */
template<typename _Enum>
LIBUFOLD_CONST LIBUFOLD_EXPORT
constexpr auto underlying_cast(const _Enum a) noexcept;

/**
 * @brief Add some operator overloads to use an `enum` as a flag
 * @param T the `enum` to which the operators are added
 */
#define UFOLD_ADD_FLAGS_OP(T)                                       \
LIBUFOLD_CONST LIBUFOLD_EXPORT                                      \
constexpr T operator|(const T a, const T b) noexcept                \
{                                                                   \
    return static_cast<T>(underlying_cast(a) | underlying_cast(b)); \
}                                                                   \
                                                                    \
LIBUFOLD_CONST LIBUFOLD_EXPORT                                      \
constexpr T operator|=(T a, const T b) noexcept                     \
{                                                                   \
    a = a | b;                                                      \
                                                                    \
    return a;                                                       \
}                                                                   \
                                                                    \
LIBUFOLD_CONST LIBUFOLD_EXPORT                                      \
constexpr T operator&(const T a, const T b) noexcept                \
{                                                                   \
    return static_cast<T>(underlying_cast(a) & underlying_cast(b)); \
}
// ADD_FLAGS_OPERATORS(T)

/**
 * @brief Print an error message
 * @param level the level of the error
 */
#define ufold_err_level(level)                           \
std::cerr << std::string(level * 2, ' ')                 \
          << "* ERROR (" << __PRETTY_FUNCTION__ << "): "

/// Print an error message with a level of zero
#define ufold_err ufold_err_level(0)

/// Call `std::throw_with_nested` with a `std::runtime_error`
#define ufold_rethrow                                   \
std::throw_with_nested(                                 \
    std::runtime_error(std::string(__PRETTY_FUNCTION__) \
                      + " failed")                      \
)

#include "ufold/core.ipp"
#endif // UFOLD_CORE_HPP
