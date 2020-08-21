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


#ifndef UFOLD_CORE_IPP
#define UFOLD_CORE_IPP

#include <algorithm>
#include <execution>

namespace ufold::core
{
    template<class _InputIt, class _UnaryPredicate>
    std::future<_InputIt> async_find_if(const _InputIt first, const _InputIt last, const _UnaryPredicate p)
    {
        return std::async(
            [=] () -> _InputIt {
                return std::find_if(first, last, p);
            }
        );
    }

    template<typename _Enum>
    constexpr auto bad_enum() noexcept
    {
        return enum_cast<_Enum>(-1);
    }

    template<class _Container>
    typename _Container::difference_type distance(const _Container& first, const typename _Container::const_iterator last)
    {
        return distance(first.cbegin(), last);
    }

    template<class _Container>
    typename _Container::difference_type distance(const _Container& rfirst, const typename _Container::const_reverse_iterator rlast)
    {
        return distance(rfirst.crbegin(), rlast);
    }

    template<typename _Enum>
    constexpr auto enum_cast(const std::underlying_type_t<_Enum> value) noexcept
    {
        return static_cast<_Enum>(value);
    }

    template<class _InputIt, class T>
    _InputIt find_first_not_of(const _InputIt first, const _InputIt last, const T& value)
    {
        return std::adjacent_find(std::execution::par, first, last,
            [&] (const T& a, const T& b) {
                return (a != b) && (a == value);
            }
        ) + 1;
    }

    template<class T>
    auto make_vector(const typename std::vector<T>::size_type size)
    {
        std::vector<T> vec;
        vec.reserve(size);

        return vec;
    }

    template<typename _Enum>
    constexpr auto underlying_cast(const _Enum constant) noexcept
    {
        return static_cast<std::underlying_type_t<_Enum>>(constant);
    }
}

#endif // UFOLD_CORE_IPP
