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
 * @file ufold/ufold.hpp
 * @author Mattéo Rossillol‑‑Laruelle <beatussum@protonmail.com>
 * @date 2020-08-13
 * @copyright GPL-3+
 */


#ifndef UFOLD_UFOLD_HPP
#define UFOLD_UFOLD_HPP

#include "libufold_export.hpp"

#include "ufold/Formats.hpp"
#include "ufold/Separators.hpp"

namespace ufold
{
    using string = std::wstring; ///< std::basic_string used by libufold

    /// type of character used by ufold::string
    using char_t = string::value_type;

    /**
     * @brief Cut a ufold::string to a specific column
     *
     * @param[in] in    the input ufold::string
     * @param[in] width to which column to cut
     *
     * @return the \p in string if its size is lower than \p width
     * @return otherwise, an edited string
     * @throw std::runtime_error if std::find_if, ufold::string::replace,
     *        or ufold::string::insert fail
     */
    LIBUFOLD_CONST LIBUFOLD_EXPORT
    string fold(const string& in, const spos_t width);

    /**
     * @brief Scan all separators of a ufold::string
     *
     * @param in the input ufold::string
     * @return a #Separators
     */
    LIBUFOLD_CONST LIBUFOLD_EXPORT
    Separators scanSeparators(const string& in);
}

#endif // UFOLD_UFOLD_HPP
