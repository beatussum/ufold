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

#include "ufold/Formats.hpp"
#include "ufold/Separators.hpp"

/// Namespace of libufold
namespace ufold
{
    /**
     * @brief Cut a ufold::string to a specific column
     *
     * @param[in] str   the input ufold::string
     * @param[in] width to which column to cut
     *
     * @return the \p str string if its size is lower than \p width
     * @return otherwise, an edited string
     * @throw std::runtime_error if std::find_if, ufold::string::replace,
     *        or ufold::string::insert fail
     */
    [[gnu::const]] LIBUFOLD_EXPORT
    string fold(string str, const string::size_type width);

    /**
     * @brief Scan all separators of a ufold::string
     *
     * @param in the input ufold::string_view
     * @return a #Separators
     */
    [[gnu::const]] LIBUFOLD_EXPORT
    Separators scanSeparators(const string_view in);

    /**
     * @brief Split a ufold::string separated by '\n' of a vector
     *        of ufold::string_view
     *
     * @param in the input ufold::string
     * @return a ufold::stringv_vec
     */
    [[gnu::const]] LIBUFOLD_EXPORT
    stringv_vec split(const string& in);

    /**
     * @brief Clean the repetitive character at the ufold::string_view
     *        extremities
     *
     * @param in the input ufold::string_view
     * @return \p in edited less a prefix and suffix
     */
    [[gnu::const]] LIBUFOLD_EXPORT
    string_view cleanOut(string_view in);
}

#endif // UFOLD_UFOLD_HPP
