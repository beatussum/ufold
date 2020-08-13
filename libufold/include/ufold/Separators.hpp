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
 * @file ufold/Separators.hpp
 * @author Mattéo Rossillol‑‑Laruelle <beatussum@protonmail.com>
 * @date 2020-08-13
 * @copyright GPL-3+
 */


#ifndef UFOLD_SEPARATORS_HPP
#define UFOLD_SEPARATORS_HPP

#include <cstdint>
#include <map>

/// Namespace of libufold
namespace ufold
{

    using spos_t = uint16_t; ///< The type representing line column
    using separator_t = uint8_t; ///< The underlying type of #SeparatorType

    /// `enum` of different type of separators
    enum class SeparatorType : separator_t {
        Capital,
        Punctuation,
        Space
    };

    /// `std::map` of separators with their position and type
    using Separators = std::map<spos_t, SeparatorType>;
}

#endif // UFOLD_SEPARATORS_HPP
