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

#include "libufold_export.hpp"
#include "ufold/types.hpp"

#include <map>

/// Namespace of libufold
namespace ufold
{
    /// The underlying type of #SeparatorType
    using separator_type_t = int8_t;

    /// `enum` of different type of separators
    enum class SeparatorType : separator_type_t {
        Capital,
        Punctuation,
        Space
    };

    /// `std::map` of separators with their position and type
    using Separators = std::map<string::size_type, SeparatorType>;

    [[gnu::const]]
    constexpr bool isSpace(const char_t) noexcept;

    [[gnu::const]]
    constexpr bool isSeparator(const char_t) noexcept;

    [[gnu::const]]
    constexpr bool isPunctuationMark(const char_t) noexcept;

    [[gnu::const]]
    constexpr SeparatorType getSeparatorTypeOf(const char_t) noexcept;
}

#include "ufold/Separators.ipp"
#endif // UFOLD_SEPARATORS_HPP
