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

namespace ufold::core
{
    template<class _UnaryPredicate>
    strit_future async_find_if(const string::reverse_iterator& rfirst, const string::reverse_iterator& rlast, _UnaryPredicate p)
    {
        return std::async(
            [&] () -> const string::iterator {
                return std::find_if(rfirst, rlast, p).base();
            }
        );
    }

    template<typename _Enum>
    constexpr _Enum enum_cast(const std::underlying_type_t<_Enum> value) noexcept
    {
        return static_cast<_Enum>(value);
    }

    template<class T>
    std::vector<T> make_vector(const typename std::vector<T>::size_type size)
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
