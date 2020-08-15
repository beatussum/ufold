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
 * @file ufold/string.hpp
 * @author Mattéo Rossillol‑‑Laruelle <beatussum@protonmail.com>
 * @date 2020-08-13
 * @copyright GPL-3+
 */


#ifndef UFOLD_STRING_HPP
#define UFOLD_STRING_HPP

#include <vector>

/// Namespace of libufold
namespace ufold
{
    /// std::basic_string used by libufold
    using string = std::wstring;

    /// Type of character used by ufold::string
    using char_t = string::value_type;

    /// const_iterator used by ufold::string
    using const_iterator = string::const_iterator;

    /// The type representing line column
    using size_t = string::size_type;

    /// std::string_view of type ufold::char_t
    using string_view = std::basic_string_view<char_t>;

    /// std::vector of ufold::string_view
    using stringv_vec = std::vector<string_view>;
}

#endif // UFOLD_STRING_HPP
