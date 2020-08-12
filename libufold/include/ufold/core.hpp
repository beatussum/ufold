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


#ifndef UFOLD_CORE_HPP
#define UFOLD_CORE_HPP

template<typename _Enum>
constexpr auto underlying_cast(const _Enum a) noexcept;

#define UFOLD_ADD_FLAGS_OP(T)                                        \
constexpr T operator|(const T a, const T b) noexcept                 \
{                                                                    \
    return static_cast<T>(underlying_cast(a) | underlying_cast(b));  \
}                                                                    \
                                                                     \
constexpr T operator|=(T a, const T b) noexcept                      \
{                                                                    \
    a = a | b;                                                       \
                                                                     \
    return a;                                                        \
}                                                                    \
                                                                     \
constexpr T operator&(const T a, const T b) noexcept                 \
{                                                                    \
    return static_cast<T>(underlying_cast(a) & underlying_cast(b));  \
}
// ADD_FLAGS_OPERATORS(T)

#include "ufold/core.ipp"
#endif // UFOLD_CORE_HPP
